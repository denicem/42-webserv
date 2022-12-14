/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:15:07 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/14 19:53:52 by dmontema         ###   ########.fr       */
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
	this->setURI(req, server);
	this->setDest(req, server);
}

void HttpAction::setURI(const HttpRequest& req, const Server& server) {
	if (req.getURI() == "/") // NOTE: if URI wants to access root folder
		this->uri = server.getRoot() + "/index.html";
		// this->uri = server.getRoot() + "/" + server.getIndexFile(); // TODO: implement on class Server / create another var: path + index
	else if (req.getURI().find("favicon.ico") != std::string::npos) // NOTE: URI wants to access favicon.ico (automatically from browser)
		this->uri = server.getRoot() + "/favicon.ico";
	else
		this->uri = server.getRoot() + req.getURI();
	std::cout << "REQUEST URI: " << req.getURI() << std::endl;
	std::cout << "THIS URI: " << this->uri << std::endl;
}

void HttpAction::setDest(const HttpRequest& req, const Server& server) {
	(void) req;
	int loc_index = getLocationIndex(server);
	if (loc_index >= 0)
	{
			std::cout << "Location name: " << server.getLocation(loc_index).getName() << std::endl;
			std::cout << "Location index: " << server.getLocation(loc_index).getIndex() << std::endl;
			std::cout << "Location path: " << server.getLocation(loc_index).getPath() << std::endl;
			std::string loc_name = server.getLocation(loc_index).getName();

			// if (this->uri.substr(0, loc_name.size()) == loc_name && this->uri.find(".") == std::string::npos) {
			if (this->uri.find(loc_name) != std::string::npos && this->uri.find(".") == std::string::npos) {
				// if URI has no specific destination,  route to index file
				std::cout << "hehe" << std::endl;
				this->uri = server.getLocation(loc_index).getPath() + "/" + server.getLocation(loc_index).getIndex();
				this->path = server.getLocation(loc_index).getPath() + "/" + server.getLocation(loc_index).getIndex();
			}
			else {
				// otherwise get exact path for destination
				// this->uri = server.getLocation(loc_index).getPath() + "/" + this->uri.substr(this->uri.find_last_of('/') + 1);
				this->path = server.getLocation(loc_index).getPath() + "/" + this->uri.substr(server.getLocation(loc_index).getPath().size() + 1);
				this->uri = server.getLocation(loc_index).getPath() + "/" + this->uri.substr(server.getLocation(loc_index).getPath().size() + 1);
			}
			this->dest = this->uri.substr(this->uri.find_last_of("/") + 1);
			return ;
	}
	// if URI didn't access one of the Routes/Location
	this->path = this->uri;
	this->dest = this->uri.substr(this->uri.find_last_of("/") + 1);
}

bool HttpAction::isMethodAllowed(const int method, const Location& location) const {
	for (unsigned long i = 0; i < location.getAllowedMethods().size(); ++i) {
		if (location.getAllowedMethods().at(i) == method)
			return (true);
	}
	return (false);
}

int HttpAction::getLocationIndex(const Server& server) const {
	size_t res;

	for (res = 0; res < server.getLocations().size(); ++res) {
		if (this->uri.find(server.getLocation(res).getName()) != std::string::npos)
			return (res);
	}
	return (-1);
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpAction::HttpAction(const HttpRequest& req, const Server& server) {
	this->initVars(req, server);
	std::cout << "URI: " <<  this->uri << std::endl;
	std::cout << "Path: " << this->path << std::endl;
	std::cout << "Destination: " << this->dest << std::endl;
	std::cout << "METHOD: " << getHttpMethodStr(req.getHttpMethod()) << std::endl;
	// if (req.getHttpMethod() == GET) // TODO: move this to a seperate func called doAction() ???
	if (this->method == GET)
	{
		try {
			this->file = File(this->uri, this->dest);
			this->statusCode = 200;
		}
		catch (File::FileNotFoundException& e) {
			this->file = File("/404/404.html");
			this->statusCode = 404;
		}
	}
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

/*
** ----------------------- EXCEPTIONS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/