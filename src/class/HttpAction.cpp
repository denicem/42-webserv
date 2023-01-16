/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:15:07 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/16 04:55:02 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpAction.hpp"

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void HttpAction::initVars(const HttpRequest& req, const Server& server) {
	this->httpVer = req.getHttpVer();

	// NOTE: deep copy map
	typedef std::map<std::string, std::string>::const_iterator str_map_iter;
	str_map_iter it = req.getHeaders().begin();
	str_map_iter ite = req.getHeaders().end();
	for (; it != ite; ++it)
		this->headers[(*it).first] = (*it).second;

	this->msgBody = req.getMsgBody();
	this->method = req.getHttpMethod();
	this->setPath(req, server);
}

void HttpAction::setPath(const HttpRequest& req, const Server& server) {
	this->route_index = getRouteIndex(req.getURI(), server);

	if (route_index >= 0) {
		Route tmp(server.getRoute(this->route_index));
		if (req.getURI().find(tmp.getName()) != std::string::npos && req.getURI().find(".") == std::string::npos) { // if URI has no specific destination, route to index file
			std::cout << "index file for route " << tmp.getName() << std::endl;
			this->path = tmp.getRoot() + "/" + tmp.getDefaultFile();
		}
		else {
			std::cout << "Destination file for route " << tmp.getName() << std::endl;
			this->path = tmp.getRoot() + "/" + req.getURI().substr(tmp.getName().size() + 1);
		}
	}
	else {
		std::cout << "File from server." << std::endl;
		this->path = server.getRoot() + "/";
		if (req.getURI() == "/")
			this->path.append(server.getIndexFile());
		else if (req.getURI().find("favicon.ico") != std::string::npos)
			this->path.append("favicon.ico");
		else
			this->path.append(req.getURI().substr(req.getURI().find_first_of('/') + 1));
	}
	this->dest = this->path.substr(this->path.find_last_of('/') + 1);
}

bool HttpAction::isMethodAllowed(const int method, const Route& route) const {
	for (unsigned long i = 0; i < route.getHttpMethods().size(); ++i) {
		if (route.getHttpMethods().at(i) == method)
			return (true);
	}
	return (false);
}

int HttpAction::getRouteIndex(const string& uri, const Server& server) const {
	int res;

	for (res = 0; res < server.getRouteCount(); ++res) {
		if (uri.find(server.getRoute(res).getName()) != std::string::npos)
			return (res);
	}
	return (-1);
}

std::string HttpAction::getDefaultErrorPage(int err_code) const {
	switch(err_code) {
		case 400: return (ERROR_PAGE_400);
		case 404: return (ERROR_PAGE_404);
		case 405: return (ERROR_PAGE_405);
		case 501: return (ERROR_PAGE_501);
		default: return ("");
	}
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpAction::HttpAction(const HttpRequest& req, const Server& server) {
	if (req.getHttpMethod() == METHOD_UNDEFINED) {
		this->statusCode = 400;
			try {
				this->file = File(server.getErrorPage(this->statusCode));
			}
			catch (std::out_of_range &e) {
				this->file = File(this->getDefaultErrorPage(this->statusCode));
			}
	}
	this->initVars(req, server);
	// std::cout << "URI: " <<  this->uri << std::endl;
	std::cout << "Path: " << this->path << std::endl;
	std::cout << "Destination: " << this->dest << std::endl;
	std::cout << "METHOD: " << getHttpMethodStr(req.getHttpMethod()) << std::endl;
}

HttpAction::~HttpAction() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

HttpMethod HttpAction::getHttpMethod() const {
	return (this->method);
}

int HttpAction::getStatusCode() const {
	return (this->statusCode);
}

File HttpAction::getFile() const {
	return (this->file);
}

/*
** ----------------------- METHODS -----------------------
*/

void HttpAction::doAction(const Server& server) {

	if (this->route_index >= 0) {
		if (!isMethodAllowed(this->method, server.getRoute(this->route_index))) {
			this->statusCode = 405;
			try {
				this->file = File(server.getErrorPage(this->statusCode));
			}
			catch (std::out_of_range &e) {
				this->file = File(this->getDefaultErrorPage(this->statusCode));
			}
			return ;
		}
	}
	if (this->method == GET)
	{
		try {
			this->file = File(this->path);
			this->statusCode = 200;
		}
		catch (File::FileNotFoundException& e) {
			this->statusCode = 404;
			try {
				this->file = File(server.getErrorPage(this->statusCode));
			}
			catch (std::out_of_range &e) {
				this->file = File(this->getDefaultErrorPage(this->statusCode));
			}
		}
	}
	if (this->method == POST && this->route_index >= 0)
	{
		if ((int) this->msgBody.size() > server.getClientMaxBody()) {
			std::cout << "too big!" << std::endl;
			this->statusCode = 400;
			try {
				this->file = File(server.getErrorPage(this->statusCode));
			}
			catch (std::out_of_range &e) {
				this->file = File(this->getDefaultErrorPage(this->statusCode));
			}
		}
		else {
			std::ofstream outfile((server.getRoute(this->route_index).getUploadDir() + "/file.txt").c_str());
			outfile << this->msgBody;
			this->statusCode = 201;
			outfile.close();
		}
	}
}

/*
** ----------------------- EXCEPTIONS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/