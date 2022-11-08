/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/08 20:51:34 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"
#include <iostream>

Socket::Socket()
{
	this->_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_server_fd == 0)
		throw NoSocketException();
	initSockAddr();
	this->_listen = listen(this->_server_fd, 10);
	if(this->_listen < 0)
		throw NoListenException();
}

void Socket::initSockAddr()
{
	// memset((char *)&this->_address, 0, sizeof(this->_address));
	memset(this->_address.sin_zero, 0, sizeof(this->_address.sin_zero));
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(PORT);
	if (bind(this->_server_fd,(struct sockaddr *) &_address, sizeof(_address)) < 0)
		throw NoBindException();
	std::cout << errno << std::endl;
}

void Socket::waitForConnect()
{
	// std::cout << "hehe\n";
	int addrlen = sizeof(this->_address);
	while (1)
	{
		std::cout << "\n---------- Waiting for connection -----------\n\n";
		this->_newSocket = accept(this->_server_fd, (struct sockaddr *)&this->_address, (socklen_t*) &addrlen);
		if (this->_newSocket < 0)
			throw NoAcceptException();
		char buffer[30000] = {0};
		int valread = read(this->getNewSocket(), buffer, 30000);
		std::cout << buffer << std::endl;
		if (valread < 0)
			std::cout << "No bytes are there to read.\n";
		std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 30\n\nHello from the other siiiiide.";
		write(this->getNewSocket(), hello.c_str(), hello.length());
		std::cout << "-------- msg sent --------\n";
		close(this->getNewSocket());
	}
}

int Socket::getNewSocket()
{
	return (this->_newSocket);
}

const char* Socket::NoSocketException::what() const throw()
{
	return ("\033[31;1mCannot create socket.\033[0m");
}
const char* Socket::NoBindException::what() const throw()
{
	return ("\033[31;1mBind failed.\033[0m");
}
const char* Socket::NoListenException::what() const throw()
{
	return ("\033[31;1mIn listen.\033[0m");
}
const char* Socket::NoAcceptException::what() const throw()
{
	return ("\033[31;1mIn accept.\033[0m");
}