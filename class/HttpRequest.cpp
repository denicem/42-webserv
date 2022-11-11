/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:39 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/10 23:06:55 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/HttpRequest.hpp"

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpRequest::HttpRequest() {}
HttpRequest::HttpRequest(const HttpRequest& other): HttpMessage(other), _httpMethod(other._httpMethod), _uri(other._uri), _restEndpoint(other._restEndpoint) {}
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

HttpMethod HttpRequest::getHttpMethod() const
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