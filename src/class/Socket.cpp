/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/15 01:33:16 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"
#include <sstream>

Socket::Socket(int _port){this->_port = _port;}

void Socket::initSockAddr(int len)
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

int Socket::getServerSocketFD(){return (this->_server_socket_fd);}
const char* Socket::NoSocketException::what() const throw(){return ("\033[31;1mCannot create socket.\033[0m");}