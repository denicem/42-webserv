/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:41:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/10 22:41:20 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/HttpMessage.hpp"

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpMessage::HttpMessage() {}
HttpMessage::HttpMessage(const HttpMessage& other): _firstLine(other._firstLine), _httpVer(other._httpVer), _headers(other._headers), _msgBody(other._msgBody) {}
HttpMessage::~HttpMessage() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

HttpMessage& HttpMessage::operator=(const HttpMessage& other)
{
	if (this != &other)
	{
		this->_firstLine = other._firstLine;
		this->_httpVer = other._httpVer;
		this->_headers = other._headers;
		this->_msgBody = other._msgBody;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

std::string HttpMessage::getHttpVer() const
{
	return (this->_httpVer);
}

std::string HttpMessage::getHeaders() const
{
	return (this->_headers);
}

std::string HttpMessage::getMsgBody() const
{
	return (this->_msgBody);
}


void HttpMessage::setHttpVer(const std::string& httpVer)
{
	this->_httpVer = httpVer;
}

void HttpMessage::setHeaders(const std::string& headers)
{
	this->_headers = headers;
}

void HttpMessage::setMsgBody(const std::string& msgBody)
{
	this->_msgBody = msgBody;
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