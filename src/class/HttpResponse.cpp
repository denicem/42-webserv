/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:52 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/17 03:41:36 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

#include <iostream>
#include <sstream>

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpResponse::HttpResponse() {}
HttpResponse::HttpResponse(const HttpResponse& other): HttpMessage(other), status_code(other.status_code), file(other.file), headers(other.headers) {}

HttpResponse::HttpResponse(const HttpAction& act) {
	this->request_line = act.getRequestLine();
	this->http_ver = act.getHttpVer();
	this->headers = act.getHeaders();
	this->msg_body = act.getMsgBody();

	this->status_code = act.getStatusCode();
	this->file = act.getFile();
	this->addHeaders();
}

HttpResponse::~HttpResponse() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

HttpResponse& HttpResponse::operator=(const HttpResponse& other) {
	if (this != &other) {
		this->request_line = other.request_line;
		this->http_ver = other.http_ver;
		this->headers = other.headers;
		this->msg_body = other.msg_body;

		this->status_code = other.status_code;
		this->file = other.file;
		this->headers = other.headers;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

/*
** ----------------------- METHODS -----------------------
*/

std::string HttpResponse::genHttpResponseMsg() const {
	std::stringstream stream;

	stream << this->http_ver << " " << this->status_code << " " << this->getStatusMsg() << std::endl;
	if (!this->headers.empty()) {
		std::map<std::string, std::string>::const_iterator it = this->headers.begin();
		std::map<std::string, std::string>::const_iterator ite = this->headers.end();
		for (; it != ite; ++it) {
			stream << (*it).first << ": " << (*it).second << std::endl;
		}
	}
	stream << std::endl;
	if (!this->file.getContent().empty())
		stream << this->file.getContent();

	return (stream.str());
}

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

std::string HttpResponse::getStatusMsg() const {
	switch (this->status_code) {
		case 200: return ("OK");
		case 201: return ("Created");
		case 204: return ("No Content");
		case 400: return ("Bad Request");
		case 404: return ("Not Found");
		case 405: return ("Method Not Allowed");
		case 501: return ("Not Implemented.");
		default: return ("undefined");
	}
}

void HttpResponse::addHeaders() { // NOTE: maybe a vector would be more effecient?
	if (!this->file.getContent().empty()) {
		std::string file_name = this->file.getFilename();
		std::string file_ext = file_name.substr(file_name.find('.') + 1);

		if (file_ext == "html" || file_ext == "css" || file_ext == "txt")
			this->headers["Content-Type"] = "text/" + file_ext;
		else if (file_ext == "jpeg" || file_ext == "png" || file_ext == "gif")
			this->headers["Content-Type"] = "image/" + file_ext;
		this->headers["Content-Length"] = CGI::intToString(this->file.getFileSize());
	}
}

/*
** ----------------------- FUNCS -----------------------
*/

std::ostream& operator<<(std::ostream& stream, const HttpResponse& resp) {
	stream << "***** Respone *****" << std::endl;
	stream << "Status code: " << resp.status_code << std::endl;
	stream << "Status message: " << resp.getStatusMsg() << std::endl;
	stream << "Response body: " << std::endl;
	if (resp.file.getFileSize() == 0 && resp.file.getContent().empty())
		stream << "Empty body!";
	else {
		stream << "File name: " << resp.file.getFilename() << std::endl;
		stream << "File size: " << resp.file.getFileSize() << " bytes." << std::endl;;
		stream << "Path: " << resp.file.getPath();
	}
	stream << std::endl;
	stream << "********************" << std::endl;
	
	return (stream);
}
