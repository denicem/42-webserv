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
HttpMessage::HttpMessage(const HttpMessage& other): request_line(other.request_line), http_ver(other.http_ver), headers(other.headers), msg_body(other.msg_body) {}
HttpMessage::~HttpMessage() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

HttpMessage& HttpMessage::operator=(const HttpMessage& other)
{
	if (this != &other)
	{
		this->request_line = other.request_line;
		this->http_ver = other.http_ver;
		this->headers = other.headers;
		this->msg_body = other.msg_body;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

std::string HttpMessage::getRequestLine() const {
	return (this->request_line);
}

std::string HttpMessage::getHttpVer() const
{
	return (this->http_ver);
}

const std::map<std::string, std::string>& HttpMessage::getHeaders() const
{
	return (this->headers);
}

std::string HttpMessage::getMsgBody() const
{
	return (this->msg_body);
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
