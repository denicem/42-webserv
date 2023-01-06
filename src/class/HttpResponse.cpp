/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/03 18:17:32 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

#include <iostream>
#include <sstream>

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

std::string HttpResponse::getStatusMsg() const {
	switch (this->statusCode) {
		case 200: return ("OK");
		case 201: return ("Created");
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

HttpResponse::HttpResponse(const HttpAction& act) {
	this->httpVer = act.getHttpVer();
	this->msgBody = act.getMsgBody();

	this->statusCode = act.getStatusCode();
	this->file = act.getFile();
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

std::string HttpResponse::genHttpResponseMsg(const HttpAction& act) const {
	std::stringstream stream;

	stream << this->httpVer << " " << this->statusCode << " " << this->getStatusMsg() << std::endl;
	if (act.getStatusCode() != 405) {
		stream << "Content-Type: text/";
		// std::cout << req.getURI() << ": " << req.getRestEndpoint() << std::endl;
		if (this->file.getFilename().find(".css") != std::string::npos)
			stream << "css";
		else if (this->file.getFilename().find(".html") != std::string::npos)
			stream << "html";
		stream << std::endl;
		stream << "Content-Length: " << this->file.getFileSize() << std::endl;
		stream << std::endl;
		if (act.getHttpMethod() == GET)
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
