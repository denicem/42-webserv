/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/15 19:27:51 by mjeyavat         ###   ########.fr       */
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

Server::Server(const string& serverName, const string &root, const vector<Location> &locations)
: serverName(serverName), root(root), locations(locations){}

Server::Server(const ServerConfig& config) {
	this->ports.push_back(config.port);
	this->clientMaxBody = config.max_client_body_size;
	this->serverNames = config.server_names;
	// this->indexFile = config.IndexFile; //TODO:
	setLocations(config.routes);
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

//TODO: mach dies getter für Dnice
// string Server::getIndexFile() const{
// 	return this.
// }

string Server::getRoot() const {
	return(this->root);
}

int Server::getPort(const int index) const {
	return (this->ports[index]);
}

Location Server::getLocation(const int index) const {
	return (this->locations[index]);
}

const std::vector<Location>& Server::getLocations() const {
	return (this->locations);
}

int Server::getServerSocketFD() const {
	return (this->serverSocketFD);
}

vector<string> Server::getServernameList() {
	return(this->serverNames);
}

void Server::setServerName(string& serverName) {
	this->serverName = serverName;
}

void Server::setPort(int port){
	this->ports.push_back(port);
}

void Server::setLocation(const Location &location){
	this->locations.push_back(location);
}

void Server::setLocations(map<string, struct RouteConfig> routs){
	map<string, RouteConfig>::iterator it = routs.begin();
	// Location locTmp;
	//!DONT NO IF WORKS
	for(;it != routs.end(); it++){
		Location locTmp((*it).first, (*it).second.root, (*it).second.default_file, genarateAllowedMethods((*it).second.http_methods ), (*it).second.directory_listing);
		this->locations.push_back(locTmp);	
	}
}

/*
** ----------------------- METHODS -----------------------
*/

void Server::initSockAddr(int len, int index) {
	// std::cout << "len: " << len << "index: " << index << std::endl;
	this->serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	// std::cout << "HEHEHEH" << std::endl;
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

/*
** ----------------------- EXCEPTIONS -----------------------
*/
const char* Server::NoSocketException::what() const throw(){return ("\033[31;1mCannot create socket.\033[0m");}

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