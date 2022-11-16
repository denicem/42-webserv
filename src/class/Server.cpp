/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/16 16:20:40 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <sstream>

Server::Server(int _port, std::string sId){
	this->_port = _port;
	this->socketId = sId;	
}

void Server::initSockAddr(int len)
{
	this->_server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_server_socket_fd == 0)
		throw NoSocketException();
	memset(&this->_address, 0, sizeof(SCK_ADDR));
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(_port);
	memset(&this->_address.sin_addr, len, sizeof(SCK_ADDR));
	
}	

int Server::getServerSocketFD(){return (this->_server_socket_fd);}
const char* Server::NoSocketException::what() const throw(){return ("\033[31;1mCannot create socket.\033[0m");}

int Server::getPort()
{
	return (this->_port);
}