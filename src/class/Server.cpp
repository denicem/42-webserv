/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/26 22:30:25 by dmontema         ###   ########.fr       */
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

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

string Server::getServerName() const {
	return(this->serverName);
}

string Server::getRoot() const {
	return(this->root);
}

int Server::getPort(const int index) const {
	return (this->ports[index]);
}

Location Server::getLocation(const int index) const {
	return (this->locations[index]);
}

int Server::getServerSocketFD() const {
	return (this->serverSocketFD);
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
	// if(this->_port.size() == 1)
	this->_address.sin_port = htons(ports[index]);
	// else {
	// 	for(vector<int>::iterator it = _port.begin(); it != _port.end(); it++){
	// 		cout << "Port: " << *it << endl;
	// 		this->_address.sin_port = htons(*it);
	// 	}

	memset(&this->_address.sin_addr, len, sizeof(SCK_ADDR));
}

/*
** ----------------------- EXCEPTIONS -----------------------
*/
const char* Server::NoSocketException::what() const throw(){return ("\033[31;1mCannot create socket.\033[0m");}

/*
** ----------------------- FUNCS -----------------------
*/

