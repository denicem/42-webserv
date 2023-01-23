/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:15:07 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/23 21:53:37 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpAction.hpp"
#include "Utils.hpp"

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpAction::HttpAction(HttpRequest& req, const Server& server): http_method(req.getHttpMethod()) {
	this->request_line = req.getRequestLine();
	this->http_ver = req.getHttpVer();
	this->headers = req.getHeaders();
	this->msg_body = req.getMsgBody();
	
	if (this->http_method == METHOD_UNDEFINED) {
		this->setupErrorPage(400, server);
		return ;
	}
	this->query = req.getQuery();
	this->setPath(req, server);
}

HttpAction::~HttpAction() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

HttpMethod HttpAction::getHttpMethod() const {
	return (this->http_method);
}

int HttpAction::getStatusCode() const {
	return (this->status_code);
}

File HttpAction::getFile() const {
	return (this->file);
}

/*
** ----------------------- METHODS -----------------------
*/

void HttpAction::doAction(const Server& server) {
	if (this->http_method == METHOD_UNDEFINED)
		return ;

	if (this->query == "_method=DELETE")
		this->http_method = DELETE;

	if (this->route_index >= 0) {
		if (!isMethodAllowed(this->http_method, server.getRoute(this->route_index))) {
			this->setupErrorPage(405, server);
			return ;
		}
	}

	if (this->http_method == GET)
		this->actGet(server);
	if (this->http_method == POST)
		this->actPost(server);
	if (this->http_method == DELETE)
		this->actDelete(server);
}

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void HttpAction::setupErrorPage(int status_code, const Server& server) {
	this->status_code = status_code;
	try {
		this->file = File(server.getErrorPage(this->status_code));
	}
	catch (std::out_of_range &e) {
		this->file = File(this->getDefaultErrorPage(this->status_code));
	}
}

std::string HttpAction::getDefaultErrorPage(int err_code) const {
	switch(err_code) {
		case 400: return (DEF_ERROR_PAGE_400);
		case 404: return (DEF_ERROR_PAGE_404);
		case 405: return (DEF_ERROR_PAGE_405);
		case 501: return (DEF_ERROR_PAGE_501);
		case 542: return (DEF_ERROR_PAGE_542);
		default: return ("");
	}
}

void HttpAction::setPath(const HttpRequest& req, const Server& server) { // TODO: optimize & clean code
	this->path_req = req.getPath();
	this->removeExtraSlashes();
	this->route_index = getRouteIndex(this->path_req, server);

	if (this->path_req.find("favicon.ico") != std::string::npos)
		this->path = server.getRoot() + "/favicon.ico";
	else if (route_index >= 0) { 
		this->checkHttpRedirection(server);
		if (this->path_req.find_first_of('/', 1) != std::string::npos) {
			this->path_req = this->path_req.substr(this->path_req.find_first_of('/', 1) + 1);
			this->path = server.getRoute(this->route_index).getRoot() + "/" + this->path_req;
		}
		else
			this->path = server.getRoute(this->route_index).getRoot() + "/" + server.getRoute(this->route_index).getDefaultFile();
	}
	else {
		this->path = server.getRoot() + "/";
		if (this->path_req == "/")
			this->path.append(server.getIndexFile());
		else
			this->path.append(this->path_req.substr(this->path_req.find_first_of('/') + 1));
	}
	this->dest = this->path.substr(this->path.find_last_of('/') + 1);
}

void HttpAction::removeExtraSlashes() {
	if (path_req == "/")
		return ;

	while (this->path_req[this->path_req.size() - 1] == '/')
		this->path_req.erase(this->path_req.find_last_of('/'));	
}

int HttpAction::getRouteIndex(const string& uri, const Server& server) const {
	if (uri == "/")
		return (-1);

	int res;
	std::string uri_route_name = uri.substr(0, uri.find_first_of('/', 1));
	
	for (res = 0; res < server.getRouteCount(); ++res) { 
		if (server.getRoute(res).getName() == uri_route_name)
			return (res);
	}
	std::cout << "NOT FOUND" << std::endl;
	return (-1);
}

void HttpAction::checkHttpRedirection(const Server& server) {
	this->http_redirect = server.getRoute(this->route_index).getHttpRedirect();
	if (!this->http_redirect.empty()) {
		this->route_index = getRouteIndex(this->http_redirect, server);
	}
}

bool HttpAction::isMethodAllowed(const int http_method, const Route& route) const {
	for (unsigned long i = 0; i < route.getHttpMethods().size(); ++i) {
		if (route.getHttpMethods().at(i) == http_method)
			return (true);
	}
	return (false);
}

void HttpAction::actGet(const Server& server) {
	if (this->route_index >= 0) {
		this->is_cgi = CGI::isCGI(this->dest, server.getRoute(this->route_index).getCgiExts(), getHttpMethodStr(this->http_method));
	}
	else if (this->route_index < 0) {
		this->is_cgi = CGI::isCGI(this->dest, g_cgi_extensions, getHttpMethodStr(this->http_method));
	}

	try {
		if (this->is_cgi) {
			this->cgi = CGI(this->headers, server.getPort(0), this->query, this->dest, this->http_ver);
			this->cgi.executeCGI();
			this->file = File("cgi." + cgi.getResponseType(), cgi.getResponseBody());
		}
		else
			this->file = File(this->path);
		this->status_code = 200;
	}
	catch (File::FileNotFoundException& e) {
		if (this->route_index >= 0 && server.getRoute(this->route_index).getDirList()) { // NOTE: if directory_listing is on
			this->status_code = 404;
			std::string tmp = this->dir_list.generateDirOutput(this->route_index, server);
			this->file = File("dir_list.html", tmp);
		}
		else
			this->setupErrorPage(404, server);
	}
	catch (CGI::CGIException &e) {
		this->setupErrorPage(542, server);
	}
}

void HttpAction::actPost(const Server& server) {
	try {
		this->file = File(this->path);
	}
	catch (File::FileNotFoundException &e) {
		this->setupErrorPage(404, server);
	}

	stringstream size_str(this->headers["Content-Length"]);
	int size;

	size_str >> size;
	if (server.getClientMaxBody() >= 0 && size > server.getClientMaxBody()) { // NOTE: Limited bodysize
		this->setupErrorPage(400, server);
		return ;
	}

	std::string upload_dir;
	if (this->route_index < 0 || server.getRoute(this->route_index).getUploadDir().empty())
		upload_dir = DEF_UPLOAD_DIR;
	else
		upload_dir = server.getRoute(this->route_index).getUploadDir();

	extractMsgBody();
	upload_dir.append("/").append(this->upload_filename);

	std::ofstream outfile(upload_dir.c_str());
	outfile << this->upload_body;
	outfile.close();
	this->status_code = 201;
}

void HttpAction::actDelete(const Server& server) {
	try {
		this->file = File(this->path);
		std::remove(this->file.getPath().c_str());
		this->file = File();
		this->status_code = 204;
	}
	catch (File::FileNotFoundException& e) {
		this->setupErrorPage(400, server);
	}
}


void HttpAction::extractMsgBody() {
	std::stringstream sstream (this->msg_body.c_str());
	std::string tmp;
	std::string boundary;

	if (this->msg_body.find("Content-Disposition") == std::string::npos) {
		this->upload_filename = this->randomNameGen();
		this->upload_body = this->msg_body;
		return ;
	}

	this->upload_body = "";

	std::getline(sstream, tmp);
	boundary = tmp;
	boundary.erase(tmp.find('\r'));
	boundary.append("--");

	while (!tmp.empty())
	{
		if (tmp.find('\r') != std::string::npos)
			tmp.erase(tmp.find(('\r')));
		if (tmp.empty())
			break ;
		if (tmp.find("Content-Disposition") != std::string::npos) {
			this->upload_filename = tmp.substr(tmp.find("filename"));
			this->upload_filename = this->upload_filename.substr(this->upload_filename.find('\"') + 1);
			this->upload_filename = this->upload_filename.erase(this->upload_filename.find('\"'));
		}
		std::getline(sstream, tmp);
	}
	while (!sstream.eof()) {
		std::getline(sstream, tmp);
		if (tmp.find('\r') != std::string::npos)
			tmp.erase(tmp.find(('\r')));
		if (boundary == tmp)
			break ;
		this->upload_body.append(tmp).append("\n");
	}
	this->upload_body.erase(this->upload_body.find_last_of('\n'));
}

std::string HttpAction::randomNameGen() const {
	std::stringstream res;
	std::srand(time(NULL));

	for (int i = 0; i < 6; ++i) {
		int rdm = std::rand() % 26;
		int upper_case = (rdm * std::rand()) % 2;
		char c;
		if (upper_case)
			c = rdm + 'A';
		else
			c = rdm + 'a';
		res << c;
	}
	return (res.str());
}

/*
** ----------------------- EXCEPTIONS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/
