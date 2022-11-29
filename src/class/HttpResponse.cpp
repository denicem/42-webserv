/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/29 14:59:59 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

#include <iostream>
#include <sstream>

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

bool HttpResponse::isMethodAllowed(const int method, const Location& location) const {
	for (unsigned long i = 0; i < location.getAllowedMethods().size(); ++i) {
		if (location.getAllowedMethods().at(i) == method)
			return (true);
	}
	return (false);
}

std::string HttpResponse::getStatusMsg() const {
	switch (this->statusCode) {
		case 200: return ("OK");
		case 404: return ("Not Found");
		case 405: return ("Method Not Allowed");
		default: return ("undefined");
	}
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpResponse::HttpResponse() {}
HttpResponse::HttpResponse(const HttpResponse& other): HttpMessage(other), statusCode(other.statusCode) {}

HttpResponse::HttpResponse(const std::string& filename) {
	this->file = File(filename);
	this->statusCode = 200;
}

HttpResponse::HttpResponse(const HttpRequest& req) {
	if (req.getHttpMethod() == GET) {  //TODO: switch case!!
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

HttpResponse::HttpResponse(const HttpRequest& req, const Server& server) {
	for (unsigned long i = 0; i < server.getLocations().size(); ++i) {
		std::cout << server.getLocation(i) << std::endl;
		if (req.getURI().find(server.getLocation(i).getName()) != std::string::npos) {
			if (!isMethodAllowed(req.getHttpMethod(), server.getLocation(i))) {
				// throw exception(); // TODO: implement own exception
				std::cout << "ERROR!" << std::endl;
				this->statusCode = 405;
				break ;
			}
			else {
				if (req.getHttpMethod() == GET) {
					try {
						this->file = File(req.getURI(), server, i, true);
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

HttpResponse::~HttpResponse() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

HttpResponse& HttpResponse::operator=(const HttpResponse& other) {
	if (this != &other) {
		// this->firstLine = other.firstLine;
		// this->httpVer = other.httpVer;
		// this->headers = other.headers;
		// this->msgBody = other.msgBody; // NOTE: will the operator=() method from the Base class called first?
		this->statusCode = other.statusCode;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

int HttpResponse::getStatusCode() const {
	return (this->statusCode);
}


void HttpResponse::setStatusCode(const int& statusCode) {
	this->statusCode = statusCode;
}

/*
** ----------------------- METHODS -----------------------
*/

std::string HttpResponse::genHttpResponseMsg(const HttpRequest& req) const {
	std::stringstream stream;

	stream << req.getHttpVer() << " " << std::to_string(this->statusCode) << " " << this->getStatusMsg() << std::endl;
	if (req.getHttpMethod() == GET && this->statusCode != 405) {
		stream << "Content-Type: text/html\nContent-Length: " << std::to_string(this->file.getFileSize()) << std::endl;
		stream << std::endl;
		stream << this->file.getContent();
	}
	return (stream.str());
}

/*
** ----------------------- FUNCS -----------------------
*/

std::ostream& operator<<(std::ostream& stream, const HttpResponse& resp) {
	stream << "***** RESPONSE *****" << std::endl;
	stream << "HTTP ver: " << resp.httpVer << std::endl;
	stream << "Status code: " << resp.statusCode <<  std::endl;
	stream << "********************" << std::endl;
	return (stream);
}
