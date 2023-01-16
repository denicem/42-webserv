/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:39 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/16 04:55:04 by dmontema         ###   ########.fr       */
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
	std::stringstream firstLineStream(this->firstLine);
	this->setHttpMethod(firstLineStream);
	this->setURI(firstLineStream);
	this->setHttpVer(firstLineStream);
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
	stream >> this->httpVer;
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
		this->msgBody.append(tmp);
		if (!stream.eof())
			this->msgBody.append("\n");
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
	std::getline(stream, this->firstLine);
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
		// this->firstLine = other.firstLine;
		// this->httpVer = other.httpVer;
		// this->headers = other.headers;
		// this->msgBody = other.msgBody; // NOTE: will the operator=() method from the Base class called first?
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
	stream <<  "Request Line: " << req.firstLine << std::endl;
	stream << "HTTP ver: " << req.httpVer << std::endl;
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
	// stream << (req.msgBody.empty() ? "EMPTY BODY" : req.msgBody) << std::endl;
	// stream << "*******************" << std::endl;
	return (stream);
}