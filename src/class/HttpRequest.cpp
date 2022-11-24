/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:39 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/24 01:41:26 by dmontema         ###   ########.fr       */
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
	std::stringstream firstLineStream(this->_firstLine);
	this->setHttpMethod(firstLineStream);
	this->setURI(firstLineStream);
	this->setHttpVer(firstLineStream);
	this->setHeaders(stream);
}

void HttpRequest::setHttpMethod(std::stringstream& stream)
{
	std::string tmp;

	stream >> tmp;
	if (tmp == "GET")
		this->_httpMethod = GET;
	else if (tmp == "POST")
		this->_httpMethod = POST;
	else if (tmp == "DELETE")
		this->_httpMethod = DELETE;
	else
		throw std::exception(); // no http method found.
}

void HttpRequest::setURI(std::stringstream& stream)
{
	stream >> this->_uri;
	this->_restEndpoint = this->_uri.substr(this->_uri.find_last_of('/') + 1);
}

void HttpRequest::setHttpVer(std::stringstream& stream)
{
	stream >> this->_httpVer;
}

void HttpRequest::setHeaders(std::stringstream& stream)
{
	std::string tmp;

	while (!stream.eof() && tmp != "\r") // NOTE: "\r" identifies if HTTP headers end 
	{
		std::getline(stream, tmp);
		// if (tmp.find(":") == std::string::npos)
		// 	std::cout << "ERROR: " << tmp << std::endl;
		if (tmp != "\r")
			this->_headers[tmp.substr(0, tmp.find(":"))] = tmp.substr(tmp.find(":") + 2, tmp.find("\r") - (tmp.find(":") + 2));
	}
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpRequest::HttpRequest() {}
HttpRequest::HttpRequest(const HttpRequest& other): HttpMessage(other), _httpMethod(other._httpMethod), _uri(other._uri), _restEndpoint(other._restEndpoint) {}

HttpRequest::HttpRequest(void* buff)
{
	std::stringstream stream(std::string((const char*) buff));
	std::getline(stream, this->_firstLine);
	this->initVars(stream);
	// print map headers
	// std::cout << "Headers size: " << this->_headers.size() << std::endl;
	// for (std::map<std::string, std::string>::iterator it = this->_headers.begin(); it != this->_headers.end(); ++it)
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
		// this->_firstLine = other._firstLine;
		// this->_httpVer = other._httpVer;
		// this->_headers = other._headers;
		// this->_msgBody = other._msgBody; // NOTE: will the operator=() method from the Base class called first?
		this->_httpMethod = other._httpMethod;
		this->_uri = other._uri;
		this->_restEndpoint = other._restEndpoint;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

HttpMessage::HttpMethod HttpRequest::getHttpMethod() const
{
	return (this->_httpMethod);
}

std::string HttpRequest::getURI() const
{
	return (this->_uri);
}

std::string HttpRequest::getRestEndpoint() const
{
	return (this->_restEndpoint);
}


void HttpRequest::setHttpMethod(const HttpMethod& httpMethod)
{
	this->_httpMethod = httpMethod;
}

void HttpRequest::setURI(const std::string& uri)
{
	this->_uri = uri;
}

void HttpRequest::setRestEndpoint(const std::string& restEndpoint)
{
	this->_restEndpoint = restEndpoint;
}

/*
** ----------------------- METHODS -----------------------
*/

/*
** ----------------------- CLASS ATTRIBUTES -----------------------
*/

/*
** ----------------------- CLASS METHODS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/

std::ostream& operator<<(std::ostream& stream, const HttpRequest& req)
{
	stream << "HTTP Request | ver-" << req._httpVer << std::endl;
	stream << "- ----------------- -\n";
	stream << "Http method: " << req._httpMethod << std::endl;
	stream << "Http URI: " << req._uri << std::endl;
	stream << "Http Restendpoint: " << req._restEndpoint;

	return (stream);
}