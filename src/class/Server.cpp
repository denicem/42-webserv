/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:52 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 22:32:49 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

#include <sstream>

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

Server::Server(const ServerConfig& config) {
	this->ports.push_back(config.port);
	this->clientMaxBody = config.max_client_body_size;
	this->serverNames = config.server_names;
	this->root = config.root;
	this->indexFile = config.default_file;
	setRoutes(config.routes);
	this->error_pages = config.error_pages;
}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

string Server::getServerName() const {
	return(this->serverName);
}

int Server::getClientMaxBody() const {
	return (this->clientMaxBody);
}

string Server::getIndexFile() const {
	return (this->indexFile);
}

string Server::getRoot() const {
	return(this->root);
}

int Server::getPort(const int index) const {
	return (this->ports[index]);
}

Route Server::getRoute(const int index) const {
	return (this->routes[index]);
}

int Server::getRouteCount() const {
	return (this->routes.size());
}

int Server::getServerSocketFD() const {
	return (this->serverSocketFD);
}

vector<string> Server::getServernameList() {
	return(this->serverNames);
}

string Server::getErrorPage(int code) const {
	return (this->error_pages.at(code));
}


void Server::setServerName(string& serverName) {
	this->serverName = serverName;
}

void Server::setPort(int port){
	this->ports.push_back(port);
}

void Server::setRoutes(map<string, struct RouteConfig> routes) {
	map<string, RouteConfig>::iterator it = routes.begin();
	for (; it != routes.end(); ++it)
		this->routes.push_back(Route((*it).first, (*it).second));
}

/*
** ----------------------- METHODS -----------------------
*/

void Server::initSockAddr(int len, int index) {
	this->serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (this->serverSocketFD == 0)
		throw NoSocketException();
	memset(&this->_address, 0, sizeof(SCK_ADDR));
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	//server has more than one port
	if(this->ports.size() == 1)
		this->_address.sin_port = htons(ports[index]);
	else{
		for(vector<int>::iterator it = ports.begin(); it != ports.end(); it++){
			cout << "Port: " << *it << endl;
			this->_address.sin_port = htons(*it);
		}
	}
	memset(&this->_address.sin_addr, len, sizeof(SCK_ADDR));
}

void Server::printRoutes() const {
	PRINT_W_COLOR(LIGHTYELLOW, "ROUTES")
	for (std::vector<Route>::size_type i = 0; i < this->routes.size(); ++i) {
		PRINT_W_COLOR(BOLD, this->routes[i])
	}
}

/*
** ----------------------- EXCEPTIONS -----------------------
*/
const char* Server::NoSocketException::what() const throw() {
	return ("\033[31;1mCannot create socket.\033[0m");
}

/*
** ----------------------- FUNCS -----------------------
*/

vector<HttpMethod> Server::genarateAllowedMethods(vector<string>methods) {
	vector<HttpMethod>result;

	for(vector<string>::iterator it = methods.begin(); it != methods.end(); it++) {
		if(*it == "GET")
			result.push_back(GET);
		else if (*it == "POST")
			result.push_back(POST);
		else if (*it == "DELETE")
			result.push_back(DELETE);
	}
	return result;
}