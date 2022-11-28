/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/28 19:19:09 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpResponse.hpp"

#include <iostream>
#include <sstream>

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

bool HttpResponse::isMethodAllowed(const int method, const Location& location) const {
	for (unsigned long i = 0; i < location.getAllowedMethods().size(); ++i)
	{
		if (location.getAllowedMethods().at(i) == method)
			return (true);
	}
	return (false);
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpResponse::HttpResponse() {}
HttpResponse::HttpResponse(const HttpResponse& other): HttpMessage(other), _statusCode(other._statusCode), _statusMsg(other._statusMsg) {}

HttpResponse::HttpResponse(const std::string& filename)
{
	this->_file = File(filename);
	this->_statusCode = 200;
	this->_statusMsg = "OK";
}

HttpResponse::HttpResponse(const HttpRequest& req)
{
	if (req.getHttpMethod() == GET) //TODO: switch case!!
	{
		try
		{
			this->_file = File(req.getURI());
			this->_statusCode = 200;
			this->_statusMsg = "OK";
		}
		catch (File::FileNotFoundException& e)
		{
			this->_file = File("/404/404.html");
			this->_statusCode = 404;
			this->_statusMsg = "Not Found";
		}
	}
}

HttpResponse::HttpResponse(const HttpRequest& req, const Server& server)
{
	for (unsigned long i = 0; i < server.getLocations().size(); ++i)
	{
		std::cout << server.getLocation(i) << std::endl;
		if ((req.getURI() == server.getLocation(i).getName()) || req.getURI() == "/") {
			std::cout << "LOCATION FOUND" << std::endl;
			// if (!isMethodAllowed(req.getHttpMethod(), server.getLocation(i)))
			// 	std::cout << "ERROR!" << std::endl;
			// 	// throw exception(); // TODO: implement own exception
			// else {
				if (req.getHttpMethod() == GET)
				{
					try
					{
						this->_file = File(req.getURI());
						this->_file = File(server.getLocation(i).getPath(), server, i, true);
						this->_statusCode = 200;
						this->_statusMsg = "OK";
					}
					catch (File::FileNotFoundException& e)
					{
						this->_file = File("/404/404.html");
						this->_statusCode = 404;
						this->_statusMsg = "Not Found";
					}
				}
			// }
		}
		else
		{
			if (req.getHttpMethod() == GET)
			{
				try
				{
					this->_file = File(req.getURI());
					this->_statusCode = 200;
					this->_statusMsg = "OK";
				}
				catch (File::FileNotFoundException& e)
				{
					this->_file = File("/404/404.html");
					this->_statusCode = 404;
					this->_statusMsg = "Not Found";
				}
			}
		}
	}

}

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

std::string HttpResponse::genHttpResponseMsg(const HttpRequest& req) const
{
	std::stringstream stream;

	stream << "HTTP/1.1 " << std::to_string(this->_statusCode) << " " << this->_statusMsg << std::endl;
	stream << "Content-Type: text/html\nContent-Length: " << std::to_string(this->_file.getFileSize()) << std::endl;
	stream << std::endl;
	if (req.getHttpMethod() == GET)
		stream << this->_file.getContent();

	return (stream.str());
}

/*
** ----------------------- CLASS ATTRIBUTES -----------------------
*/

/*
** ----------------------- CLASS METHODS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/