/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/23 20:55:25 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

Server::Server(string sId){
	this->serverName = sId;	
}

void Server::initSockAddr(int len, int index){
	this->_server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_server_socket_fd == 0)
		throw NoSocketException();
	memset(&this->_address, 0, sizeof(SCK_ADDR));
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	//server has more than one port
	// if(this->_port.size() == 1)
	this->_address.sin_port = htons(_port[index]);
	// else {
	// 	for(vector<int>::iterator it = _port.begin(); it != _port.end(); it++){
	// 		cout << "Port: " << *it << endl;
	// 		this->_address.sin_port = htons(*it);
	// 	}
	
	memset(&this->_address.sin_addr, len, sizeof(SCK_ADDR));
	
	
}	

void Server::setServerName(string serverName){
	this->serverName = serverName;
}

int Server::getServerSocketFD(){return (this->_server_socket_fd);}
const char* Server::NoSocketException::what() const throw(){return ("\033[31;1mCannot create socket.\033[0m");}

int Server::getPort(int index){
	return (this->_port[index]);
}

void Server::setPort(int port){
	this->_port.push_back(port);
}

string Server::getServerName(){
	return(this->serverName);
}

