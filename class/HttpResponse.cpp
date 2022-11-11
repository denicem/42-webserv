/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/11 01:30:39 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/HttpResponse.hpp"

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpResponse::HttpResponse() {}
HttpResponse::HttpResponse(const HttpResponse& other): HttpMessage(other), _statusCode(other._statusCode), _statusMsg(other._statusMsg) {}
HttpResponse::~HttpResponse() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

HttpResponse& HttpResponse::operator=(const HttpResponse& other)
{
	if (this != &other)
	{
		// this->_firstLine = other._firstLine;
		// this->_httpVer = other._httpVer;
		// this->_headers = other._headers;
		// this->_msgBody = other._msgBody; // NOTE: will the operator=() method from the Base class called first?
		this->_statusCode = other._statusCode;
		this->_statusMsg = other._statusMsg;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

int HttpResponse::getStatusCode() const
{
	return (this->_statusCode);
}

std::string HttpResponse::getStatusMsg() const
{
	return (this->_statusMsg);
}


void HttpResponse::setStatusCode(const int& statusCode)
{
	this->_statusCode = statusCode;
}

void HttpResponse::setStatusMsg(const std::string& statusMsg)
{
	this->_statusMsg = statusMsg;
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