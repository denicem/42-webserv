/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:15:07 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/11 19:25:14 by dmontema         ###   ########.fr       */
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
	int locIndex = getLocationIndex(req.getURI(), server);

	if (locIndex >= 0) {
		Location tmp(server.getLocation(locIndex));

		if (req.getURI().find(tmp.getName()) != std::string::npos && req.getURI().find(".") == std::string::npos) { // if URI has no specific destination, route to index file
			std::cout << "index file for location " << tmp.getName() << std::endl;
			this->path = tmp.getRoot() + "/" + tmp.getIndex();
		}
		else {
			std::cout << "Destination file for location " << tmp.getName() << std::endl;
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

bool HttpAction::isMethodAllowed(const int method, const Location& location) const {
	for (unsigned long i = 0; i < location.getAllowedMethods().size(); ++i) {
		if (location.getAllowedMethods().at(i) == method)
			return (true);
	}
	return (false);
}

int HttpAction::getLocationIndex(const string& uri, const Server& server) const {
	size_t res;

	for (res = 0; res < server.getLocations().size(); ++res) {
		if (uri.find(server.getLocation(res).getName()) != std::string::npos)
			return (res);
	}
	return (-1);
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpAction::HttpAction(const HttpRequest& req, const Server& server) {
	this->initVars(req, server);
	// std::cout << "URI: " <<  this->uri << std::endl;
	std::cout << "Path: " << this->path << std::endl;
	std::cout << "Destination: " << this->dest << std::endl;
	std::cout << "METHOD: " << getHttpMethodStr(req.getHttpMethod()) << std::endl;
	// if (this->method == GET) // TODO: move this to a seperate func called doAction() ???
	// {
	// 	try {
	// 		this->file = File(this->path, this->dest);
	// 		this->statusCode = 200;
	// 	}
	// 	catch (File::FileNotFoundException& e) {
	// 		this->file = File("/404/404.html");
	// 		this->statusCode = 404;
	// 	}
	// }
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
	std::cout << "doAction() called mofo." << std::endl;

	if (this->method == GET)
	{
		try {
			this->file = File(this->path, this->dest);
			this->statusCode = 200;
		}
		catch (File::FileNotFoundException& e) {
			this->statusCode = 404;
			this->file = File(server.getErrorPage(this->statusCode));
		}
	}
	if (this->method == POST)
	{
		std::ofstream outfile("upload/test.txt");
		outfile << this->msgBody;
		this->statusCode = 201;
		outfile.close();
	}
}

/*
** ----------------------- EXCEPTIONS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/