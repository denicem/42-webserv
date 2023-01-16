/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:52 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/16 22:03:17 by dmontema         ###   ########.fr       */
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
		case 400: return ("Bad Request");
		case 404: return ("Not Found");
		case 405: return ("Method Not Allowed");
		case 501: return ("Not Implemented.");
		default: return ("undefined");
	}
}

void HttpResponse::addHeaders() {
	if (!this->file.getContent().empty()) {
		std::string file_name = this->file.getFilename();
		std::string file_ext = file_name.substr(file_name.find('.') + 1);

		if (file_ext == "html" || file_ext == "css" || file_ext == "txt") {
			this->headers["Content-Type"] = "text/" + file_ext;
		}
		else if (file_ext == "jpeg" || file_ext == "gif") {
			this->headers["Content-Type"] = "image/" + file_ext;
		}
		this->headers["Content-Length"] = CGI::intToString(this->file.getFileSize());
	}
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpResponse::HttpResponse() {}
HttpResponse::HttpResponse(const HttpResponse& other): HttpMessage(other), statusCode(other.statusCode) {}

HttpResponse::HttpResponse(const HttpAction& act) {
	this->http_ver = act.getHttpVer();
	this->msg_body = act.getMsgBody();

	this->statusCode = act.getStatusCode();
	this->file = act.getFile();
	this->addHeaders();
}

HttpResponse::~HttpResponse() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

HttpResponse& HttpResponse::operator=(const HttpResponse& other) {
	if (this != &other) {
		// this->request_line = other.request_line;
		// this->http_ver = other.http_ver;
		// this->headers = other.headers;
		// this->msg_body = other.msg_body; // NOTE: will the operator=() method from the Base class called first?
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
	(void) act;

	stream << this->http_ver << " " << this->statusCode << " " << this->getStatusMsg() << std::endl;
	if (!this->headers.empty()) {
		std::map<std::string, std::string>::const_iterator it = this->headers.begin();
		std::map<std::string, std::string>::const_iterator ite = this->headers.end();
		for (; it != ite; ++it) {
			stream << (*it).first << ": " << (*it).second << std::endl;
		}
	}
	// stream << "Content-Type: text/";
	// // std::cout << req.getURI() << ": " << req.getRestEndpoint() << std::endl;
	// if (this->file.getFilename().find(".css") != std::string::npos)
	// 	stream << "css";
	// else if (this->file.getFilename().find(".html") != std::string::npos)
	// 	stream << "html";
	// stream << std::endl;
	// stream << "Content-Length: " << this->file.getFileSize() << std::endl;
	stream << std::endl;
	if (!this->file.getContent().empty())
		stream << this->file.getContent();

	return (stream.str());
}

/*
** ----------------------- FUNCS -----------------------
*/

std::ostream& operator<<(std::ostream& stream, const HttpResponse& resp) {
	stream << "***** Respone *****" << std::endl;
	stream << "Status code: " << resp.statusCode << std::endl;
	stream << "Status message: " << resp.getStatusMsg() << std::endl;
	stream << "Response Body: ";
	if (resp.file.getFileSize() == 0 && resp.file.getContent().empty())
		stream << "Empty body!";
	else {
		stream << resp.file.getFilename() << ": " << resp.file.getFileSize() << " bytes.";
		stream << " Path: " << resp.file.getPath();
	}
	stream << std::endl;
	stream << "********************" << std::endl;
	
	return (stream);
}
