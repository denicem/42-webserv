/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:15:07 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/03 17:38:08 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpAction.hpp"

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

bool HttpAction::isMethodAllowed(const int method, const Location& location) const {
	for (unsigned long i = 0; i < location.getAllowedMethods().size(); ++i) {
		if (location.getAllowedMethods().at(i) == method)
			return (true);
	}
	return (false);
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

HttpAction::HttpAction(const HttpRequest& req, const Server& server) {
	this->method = req.getHttpMethod();
	this->httpVer = req.getHttpVer();
	this->msgBody = req.getMsgBody();
	for (unsigned long i = 0; i < server.getLocations().size(); ++i) {
		// std::cout << server.getLocation(i) << std::endl;
		if (req.getURI().find(server.getLocation(i).getName()) != std::string::npos) {
			if (!isMethodAllowed(req.getHttpMethod(), server.getLocation(i))) {
				// throw exception(); // TODO: implement own exception
				std::cout << "ERROR!" << std::endl;
				this->statusCode = 405;
				break ;
			}
			else {
				if (req.getHttpMethod() == GET) {
					try {
						this->file = File(req, server, i, true);
						this->statusCode = 200;
					}
					catch (File::FileNotFoundException& e) {
						this->file = File("/404/404.html");
						this->statusCode = 404;
					}
					break ;
				}
			}
		}
		else {
			if (req.getHttpMethod() == GET) {
				try {
					this->file = File(req.getURI());
					this->statusCode = 200;
				}
				catch (File::FileNotFoundException& e) {
					this->file = File("/404/404.html");
					this->statusCode = 404;
				}
			}
		}
	}
}

HttpAction::~HttpAction() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

HttpMethod HttpAction::getHttpMethod() const {
	return (this->method);
}

int HttpAction::getStatusCode() const {
	return (this->statusCode);
}

File HttpAction::getFile() const {
	return (this->file);
}

/*
** ----------------------- METHODS -----------------------
*/

/*
** ----------------------- EXCEPTIONS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/