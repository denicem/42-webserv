/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:15:07 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/04 23:47:07 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpAction.hpp"

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void HttpAction::initVars(const HttpRequest& req, const Server& server) {
	this->httpVer = req.getHttpVer();

	// NOTE: deep copy map
	// NOTE: typedefs in snake_case??
	typedef std::map<std::string, std::string>::const_iterator str_map_iter;
	str_map_iter it = req.getHeaders().begin();
	str_map_iter ite = req.getHeaders().end();
	for (; it != ite; ++it)
		this->headers[(*it).first] = (*it).second;

	this->msgBody = req.getMsgBody();
	this->method = req.getHttpMethod();
	this->setURI(req, server);
}

void HttpAction::setURI(const HttpRequest& req, const Server& server) {
	if (req.getURI() == "/")
		this->uri = server.getRoot() + "/index.html";
		// this->uri = server.getRoot() + "/" + server.getIndex(); // TODO: implement on class Server / create another var: path + index
	else if (req.getURI().find("favicon.ico") != std::string::npos)
		this->uri = server.getRoot() + "/favicon.ico";
	else
		this->uri = req.getURI();
}

bool HttpAction::isMethodAllowed(const int method, const Location& location) const {
	for (unsigned long i = 0; i < location.getAllowedMethods().size(); ++i) {
		if (location.getAllowedMethods().at(i) == method)
			return (true);
	}
	return (false);
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpAction::HttpAction(const HttpRequest& req, const Server& server) {
	this->initVars(req, server);
	for (unsigned long i = 0; i < server.getLocations().size(); ++i) {
		if (this->uri.find(server.getLocation(i).getName()) != std::string::npos) {
			if (!isMethodAllowed(req.getHttpMethod(), server.getLocation(i))) {
				std::cout << "ERROR!" << std::endl;
				this->statusCode = 405;
				break ;
			}
			else {
				if (req.getHttpMethod() == GET) {
					try {
						this->file = File(this->uri, server, i, true);
						this->statusCode = 200;
					}
					catch (File::FileNotFoundException& e) {
						this->file = File("/404/404.html");
						this->statusCode = 404;
					}
					break ;
				}
			}
		}
		else {
			if (req.getHttpMethod() == GET) {
				try {
					this->file = File(req.getURI());
					this->statusCode = 200;
				}
				catch (File::FileNotFoundException& e) {
					this->file = File("/404/404.html");
					this->statusCode = 404;
				}
			}
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