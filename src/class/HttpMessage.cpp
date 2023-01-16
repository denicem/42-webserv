/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:41:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/04 22:27:14 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpMessage.hpp"

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpMessage::HttpMessage() {}
HttpMessage::HttpMessage(const HttpMessage& other): firstLine(other.firstLine), httpVer(other.httpVer), headers(other.headers), msgBody(other.msgBody) {}
HttpMessage::~HttpMessage() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

HttpMessage& HttpMessage::operator=(const HttpMessage& other)
{
	if (this != &other)
	{
		this->firstLine = other.firstLine;
		this->httpVer = other.httpVer;
		this->headers = other.headers;
		this->msgBody = other.msgBody;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

std::string HttpMessage::getHttpVer() const
{
	return (this->httpVer);
}

const std::map<std::string, std::string>& HttpMessage::getHeaders() const
{
	return (this->headers);
}

std::string HttpMessage::getMsgBody() const
{
	return (this->msgBody);
}


void HttpMessage::setHttpVer(const std::string& httpVer)
{
	this->httpVer = httpVer;
}

// void HttpMessage::setHeaders(const std::string& headers)
// {
// 	this->headers = headers;
// }

void HttpMessage::setMsgBody(const std::string& msgBody)
{
	this->msgBody = msgBody;
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