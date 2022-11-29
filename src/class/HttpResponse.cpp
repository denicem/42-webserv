/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:44:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/29 02:36:30 by dmontema         ###   ########.fr       */
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
HttpResponse::HttpResponse(const HttpResponse& other): HttpMessage(other), statusCode(other.statusCode), statusMsg(other.statusMsg) {}

HttpResponse::HttpResponse(const std::string& filename)
{
	this->file = File(filename);
	this->statusCode = 200;
	this->statusMsg = "OK";
}

HttpResponse::HttpResponse(const HttpRequest& req)
{
	if (req.getHttpMethod() == GET) //TODO: switch case!!
	{
		try
		{
			this->file = File(req.getURI());
			this->statusCode = 200;
			this->statusMsg = "OK";
		}
		catch (File::FileNotFoundException& e)
		{
			this->file = File("/404/404.html");
			this->statusCode = 404;
			this->statusMsg = "Not Found";
		}
	}
}

HttpResponse::HttpResponse(const HttpRequest& req, const Server& server)
{
	for (unsigned long i = 0; i < server.getLocations().size(); ++i)
	{
		std::cout << server.getLocation(i) << std::endl;
		// if ((req.getURI() == server.getLocation(i).getName()) || req.getURI() == "/") {
		if (req.getURI().find(server.getLocation(i).getName()) != std::string::npos) {
			std::cout << "LOCATION FOUND" << std::endl;
			// if (!isMethodAllowed(req.getHttpMethod(), server.getLocation(i)))
			// 	std::cout << "ERROR!" << std::endl;
			// 	// throw exception(); // TODO: implement own exception
			// else {
				if (req.getHttpMethod() == GET)
				{
					try
					{
						std::cout << "hehe" << std::endl;
						// this->file = File(req.getURI());
						this->file = File(server.getLocation(i).getName(), server, i, true);
						this->statusCode = 200;
						this->statusMsg = "OK";
					}
					catch (File::FileNotFoundException& e)
					{
						this->file = File("/404/404.html");
						this->statusCode = 404;
						this->statusMsg = "Not Found";
					}
					break ;
				}
			// }
		}
		else
		{
			if (req.getHttpMethod() == GET)
			{
				try
				{
					this->file = File(req.getURI());
					this->statusCode = 200;
					this->statusMsg = "OK";
				}
				catch (File::FileNotFoundException& e)
				{
					this->file = File("/404/404.html");
					this->statusCode = 404;
					this->statusMsg = "Not Found";
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
		// this->firstLine = other.firstLine;
		// this->httpVer = other.httpVer;
		// this->headers = other.headers;
		// this->msgBody = other.msgBody; // NOTE: will the operator=() method from the Base class called first?
		this->statusCode = other.statusCode;
		this->statusMsg = other.statusMsg;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

int HttpResponse::getStatusCode() const
{
	return (this->statusCode);
}

std::string HttpResponse::getStatusMsg() const
{
	return (this->statusMsg);
}


void HttpResponse::setStatusCode(const int& statusCode)
{
	this->statusCode = statusCode;
}

void HttpResponse::setStatusMsg(const std::string& statusMsg)
{
	this->statusMsg = statusMsg;
}

/*
** ----------------------- METHODS -----------------------
*/

std::string HttpResponse::genHttpResponseMsg(const HttpRequest& req) const
{
	std::stringstream stream;

	stream << "HTTP/1.1 " << std::to_string(this->statusCode) << " " << this->statusMsg << std::endl;
	stream << "Content-Type: text/html\nContent-Length: " << std::to_string(this->file.getFileSize()) << std::endl;
	stream << std::endl;
	if (req.getHttpMethod() == GET)
		stream << this->file.getContent();

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