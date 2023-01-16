/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:39 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/16 22:03:17 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"

#include <sstream>
#include <string>
#include <iostream>
#include <exception>

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void HttpRequest::initVars(std::stringstream& stream)
{
	std::stringstream request_line_stream(this->request_line);
	this->setHttpMethod(request_line_stream);
	this->setURI(request_line_stream);
	this->setHttpVer(request_line_stream);
	this->setHeaders(stream);
	if (this->httpMethod == POST)
		this->setMsgBody(stream);
}

void HttpRequest::setHttpMethod(std::stringstream& stream)
{
	std::string tmp;

	stream >> tmp;
	if (tmp == "GET")
		this->httpMethod = GET;
	else if (tmp == "POST")
		this->httpMethod = POST;
	else if (tmp == "DELETE")
		this->httpMethod = DELETE;
	else
		this->httpMethod = METHOD_UNDEFINED;
}

void HttpRequest::setURI(std::stringstream& stream)
{
	stream >> this->uri;
	this->restEndpoint = this->uri.substr(this->uri.find_last_of('/') + 1);
	if (this->uri.find('?') != std::string::npos) {
		this->query = this->uri.substr(this->uri.find_first_of('?'));
		this->path = this->uri.substr(0, this->uri.find_first_of('?'));
		this->uri = this->path;
	}
}

void HttpRequest::setHttpVer(std::stringstream& stream)
{
	stream >> this->http_ver;
}

void HttpRequest::setHeaders(std::stringstream& stream)
{
	std::string tmp;

	while (!stream.eof() && tmp != "\r") // NOTE: "\r" identifies if HTTP headers end; NOTE: what about CRLF??
	{
		std::getline(stream, tmp);
		// if (tmp.find(":") == std::string::npos)
		// 	std::cout << "ERROR: " << tmp << std::endl;
		if (tmp != "\r") // TODO: should only do if right syntax!
			this->headers[tmp.substr(0, tmp.find(":"))] = tmp.substr(tmp.find(":") + 2, tmp.find("\r") - (tmp.find(":") + 2));
	}
}

void HttpRequest::setMsgBody(std::stringstream& stream)
{
	std::string tmp;

	while (!stream.eof()) // TODO: find out what to extract exactly
	{
		std::getline(stream, tmp);
		this->msg_body.append(tmp);
		if (!stream.eof())
			this->msg_body.append("\n");
	}
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpRequest::HttpRequest() {}
HttpRequest::HttpRequest(const HttpRequest& other): HttpMessage(other), httpMethod(other.httpMethod), uri(other.uri), restEndpoint(other.restEndpoint) {}

HttpRequest::HttpRequest(void* buff)
{
	std::stringstream stream(std::string((const char*) buff));
	std::getline(stream, this->request_line);
	this->initVars(stream);
	// print map headers
	// std::cout << "Headers size: " << this->headers.size() << std::endl;
	// for (std::map<std::string, std::string>::iterator it = this->headers.begin(); it != this->headers.end(); ++it)
	// 	std::cout << "|" << (*it).first << "_" << (*it).second << "|" << std::endl;
}

HttpRequest::~HttpRequest() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

HttpRequest& HttpRequest::operator=(const HttpRequest& other)
{
	if (this != &other)
	{
		// this->request_line = other.request_line;
		// this->http_ver = other.http_ver;
		// this->headers = other.headers;
		// this->msg_body = other.msg_body; // NOTE: will the operator=() method from the Base class called first?
		this->httpMethod = other.httpMethod;
		this->uri = other.uri;
		this->restEndpoint = other.restEndpoint;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

HttpMethod HttpRequest::getHttpMethod() const
{
	return (this->httpMethod);
}

std::string HttpRequest::getURI() const
{
	return (this->uri);
}

std::string HttpRequest::getPath() const
{
	return (this->path);
}

std::string HttpRequest::getQuery() const
{
	return (this->query);
}

std::string HttpRequest::getRestEndpoint() const
{
	return (this->restEndpoint);
}


void HttpRequest::setHttpMethod(const HttpMethod& httpMethod)
{
	this->httpMethod = httpMethod;
}

void HttpRequest::setURI(const std::string& uri)
{
	this->uri = uri;
}

void HttpRequest::setRestEndpoint(const std::string& restEndpoint)
{
	this->restEndpoint = restEndpoint;
}

/*
** ----------------------- METHODS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/

std::ostream& operator<<(std::ostream& stream, const HttpRequest& req)
{
	stream << "***** REQUEST *****" << std::endl;
	stream <<  "Request Line: " << req.request_line << std::endl;
	stream << "HTTP ver: " << req.http_ver << std::endl;
	stream << "HTTP method: " << getHttpMethodStr(req.httpMethod) << std::endl;
	stream << "HTTP URI: " << req.uri << std::endl;
	stream << "HTTP PATH: " << req.path << std::endl;
	stream << "HTTP QUERY: " << req.query << std::endl;
	stream << "HTTP Restendpoint: " << req.restEndpoint << std::endl;
	// stream << std::endl << "HTTP HEADERS: " << std::endl;
	// for (std::map<std::string, std::string>::const_iterator it = req.headers.begin(); it != req.headers.end(); ++it)
	// {
	// 	stream << (*it).first << ": " << (*it).second << std::endl;
	// }
	// stream << std::endl;
	// stream << (req.msg_body.empty() ? "EMPTY BODY" : req.msg_body) << std::endl;
	// stream << "*******************" << std::endl;
	return (stream);
}