/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:15:07 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/20 17:25:26 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpAction.hpp"

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

	if (this->route_index >= 0) {
		if (!isMethodAllowed(this->http_method, server.getRoute(this->route_index))) {
			this->setupErrorPage(405, server);
			return ;
		}
	}

	if (this->http_method == GET)
	{
		if (this->route_index >= 0) {
			this->is_cgi = CGI::isCGI(this->dest, server.getRoute(this->route_index).getCgiExts(), getHttpMethodStr(this->http_method));
		}
		else if (this->route_index < 0) {
			this->is_cgi = CGI::isCGI(this->dest, g_cgi_extensions, getHttpMethodStr(this->http_method));
		}

		try {
			if (this->is_cgi) {
				// this->cgi = CGI(this->headers, this->query, this->dest, this->http_ver);
				// this->cgi_response = this->cgi.executeCGI();
				// this->file = File("cgi." + cgi.getResponseType(), cgi.getResponseBody());
				std::cout << "CGI!!!" << std::endl;
				this->file = File(this->path);
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

	if (this->http_method == POST) {
		if (server.getClientMaxBody() >= 0 && (int) this->msg_body.size() > server.getClientMaxBody()) { // NOTE: Limited bodysize
			this->setupErrorPage(400, server);
			return ;
		}
		std::string upload_dir;

		if (this->route_index < 0 || server.getRoute(this->route_index).getUploadDir().empty())
			upload_dir = DEF_UPLOAD_DIR;
		else
			upload_dir = server.getRoute(this->route_index).getUploadDir();
		upload_dir.append("/file.txt");
		std::ofstream outfile(upload_dir.c_str());
		outfile << this->msg_body;
		this->status_code = 201;
		outfile.close();
	}

	if (this->http_method == DELETE && this->route_index >= 0) { // NOTE: only works if the route is requested
		try {
			this->file = File((server.getRoute(this->route_index).getUploadDir() + "/file.txt").c_str());
			std::remove((server.getRoute(this->route_index).getUploadDir() + "/file.txt").c_str());
			this->status_code = 204;
		}
		catch (File::FileNotFoundException& e) {
			this->setupErrorPage(400, server);
		}
	}
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
	this->route_index = getRouteIndex(this->path_req, server);

	if (route_index >= 0) { // FIXME: if route "/hehe" is configured, requesting "/heheeee" still works 
		this->checkHttpRedirection(server);
		Route tmp(server.getRoute(this->route_index));
		if (this->path_req.find(tmp.getName()) != std::string::npos && this->path_req.find(".") == std::string::npos) { // if URI has no specific destination, route to index file
			std::cout << "index file for route " << tmp.getName() << std::endl;
			this->path = tmp.getRoot() + "/" + tmp.getDefaultFile();
		}
		else {
			std::cout << "Destination file for route " << tmp.getName() << std::endl;
			this->path = tmp.getRoot() + "/" + this->path_req.substr(tmp.getName().size() + 1);
			std::cout << this->path << std::endl;
		}
	}
	else {
		std::cout << "File from server." << std::endl;
		this->path = server.getRoot() + "/";
		if (this->path_req == "/")
			this->path.append(server.getIndexFile());
		else if (this->path_req.find("favicon.ico") != std::string::npos)
			this->path.append("favicon.ico");
		else
			this->path.append(this->path_req.substr(this->path_req.find_first_of('/') + 1));
	}
	this->dest = this->path.substr(this->path.find_last_of('/') + 1);
}

int HttpAction::getRouteIndex(const string& uri, const Server& server) const {
	int res;

	for (res = 0; res < server.getRouteCount(); ++res) {
		if (uri.find(server.getRoute(res).getName()) != std::string::npos)
			return (res);
	}
	return (-1);
}

void HttpAction::checkHttpRedirection(const Server& server) {
	this->http_redirect = server.getRoute(this->route_index).getHttpRedirect();
		if (!this->http_redirect.empty()) {
			this->route_index = getRouteIndex(this->http_redirect, server);
			this->path_req = this->http_redirect;
		}
}

bool HttpAction::isMethodAllowed(const int http_method, const Route& route) const {
	for (unsigned long i = 0; i < route.getHttpMethods().size(); ++i) {
		if (route.getHttpMethods().at(i) == http_method)
			return (true);
	}
	return (false);
}

/*
** ----------------------- EXCEPTIONS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/
