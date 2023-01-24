/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:39 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/24 20:53:10 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"

#include <iostream>
#include <sstream>
#include <string>

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpRequest::HttpRequest() {}
HttpRequest::HttpRequest(const HttpRequest& other): HttpMessage(other), http_method(other.http_method), uri(other.uri), path(other.path), query(other.query) {}

HttpRequest::HttpRequest(const std::string& buff) {
	std::stringstream req_buff(buff);
	std::getline(req_buff, this->request_line);
	this->fetchRequestBuffer(req_buff);
}

HttpRequest::~HttpRequest() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

HttpRequest& HttpRequest::operator=(const HttpRequest& other) {
	if (this != &other) {
		this->request_line = other.request_line;
		this->http_ver = other.http_ver;
		this->headers = other.headers;
		this->msg_body = other.msg_body;

		this->http_method = other.http_method;
		this->uri = other.uri;
		this->path = other.path;
		this->query = other.query;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

HttpMethod HttpRequest::getHttpMethod() const {
	return (this->http_method);
}

std::string HttpRequest::getURI() const {
	return (this->uri);
}

std::string HttpRequest::getPath() const {
	return (this->path);
}

std::string HttpRequest::getQuery() const {
	return (this->query);
}


void HttpRequest::setURI(const std::string& uri) {
	this->uri = uri;
}

void HttpRequest::setPath(const std::string& path) {
	this->path = path;
}

/*
** ----------------------- METHODS -----------------------
*/

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void HttpRequest::fetchRequestBuffer(std::stringstream& req_buff) {
	std::stringstream request_line_stream(this->request_line);
	this->fetchHttpMethod(request_line_stream);
	this->fetchURI(request_line_stream);
	this->fetchHttpVer(request_line_stream);

	this->fetchHeaders(req_buff);
	if (this->http_method == POST)
		this->fetchMsgBody(req_buff);
}

void HttpRequest::fetchHttpMethod(std::stringstream& stream) {
	std::string tmp;

	stream >> tmp;
	if (tmp == "GET")
		this->http_method = GET;
	else if (tmp == "POST")
		this->http_method = POST;
	else if (tmp == "DELETE")
		this->http_method = DELETE;
	else
		this->http_method = METHOD_UNDEFINED;
}

void HttpRequest::fetchURI(std::stringstream& stream) {
	stream >> this->uri;
	this->path = this->uri.substr(0, this->uri.find_first_of('?'));
	if (this->uri.find('?') != std::string::npos) {
		this->query = this->uri.substr(this->uri.find_first_of('?') + 1);
	}
}

void HttpRequest::fetchHttpVer(std::stringstream& stream) {
	stream >> this->http_ver;
}

void HttpRequest::fetchHeaders(std::stringstream& stream) {
	std::string tmp;

	while (!stream.eof() && tmp != "\r") {
		std::getline(stream, tmp);
		if (tmp != "\r")
			this->headers[tmp.substr(0, tmp.find(":"))] = tmp.substr(tmp.find(":") + 2, tmp.find("\r") - (tmp.find(":") + 2));
	}
}

void HttpRequest::fetchMsgBody(std::stringstream& stream) {
	std::string tmp;

	while (!stream.eof()) {
		std::getline(stream, tmp);
		this->msg_body.append(tmp);
		if (!stream.eof())
			this->msg_body.append("\n");
	}
}

/*
** ----------------------- FUNCS -----------------------
*/

std::ostream& operator<<(std::ostream& stream, const HttpRequest& req) {
	stream << "***** REQUEST *****" << std::endl;
	stream <<  "Request line: " << req.request_line << std::endl;
	stream << "HTTP ver: " << req.http_ver << std::endl;
	stream << "HTTP method: " << getHttpMethodStr(req.http_method) << std::endl;
	stream << "HTTP URI: " << req.uri << std::endl;
	stream << "HTTP path: " << req.path << std::endl;
	stream << "HTTP query: " << req.query << std::endl;
	// stream << std::endl << "HTTP Headers: " << std::endl;
	// for (std::map<std::string, std::string>::const_iterator it = req.headers.begin(); it != req.headers.end(); ++it)
	// 	stream << (*it).first << ": " << (*it).second << std::endl;
	// stream << std::endl;
	// stream << "HTTP body:" << std::endl;
	// stream << (req.msg_body.empty() ? "Empty body" : req.msg_body) << std::endl;
	// stream << "*******************" << std::endl;

	return (stream);
}
