/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/08 22:41:02 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.hpp"
#include <iostream>

Socket::Socket()
{
	this->_server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_server_socket_fd == 0)
		throw NoSocketException();
	initSockAddr();
	this->_listen = listen(this->_server_socket_fd, 10);
	if(this->_listen < 0)
		throw NoListenException();
}

void Socket::initSockAddr()
{
	// memset((char *)&this->_address, 0, sizeof(this->_address));
	memset(this->_address.sin_zero, 0, sizeof(this->_address.sin_zero));
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(PORT42);
	if (bind(this->_server_socket_fd,(struct sockaddr *) &_address, sizeof(_address)) < 0)
		throw NoBindException();
}

void Socket::waitForConnect()
{
	// std::cout << "hehe\n";
	int addrlen = sizeof(this->_address);
	while (42)
	{
		std::cout << "\n---------- Waiting for connection -----------\n\n";
		this->_client_socket_fd = accept(this->_server_socket_fd, (struct sockaddr *) &this->_address, (socklen_t*) &addrlen);
		if (this->_client_socket_fd < 0)
			throw NoAcceptException();
		char buffer[30000] = {0};
		// int valread = read(this->_client_socket_fd, buffer, 30000);
		int valread = recv(this->_client_socket_fd, buffer, 30000, 0);
		std::cout << buffer << std::endl;
		if (valread < 0)
			std::cout << "No bytes are there to read.\n";
		std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 39\n\n<h1>Hello from the other siiiiide.</h1>";
		// write(this->_client_socket_fd, hello.c_str(), hello.length());
		send(this->_client_socket_fd, hello.c_str(), hello.length(), 0);
		std::cout << "-------- msg sent --------\n";
		close(this->_client_socket_fd);
	}
}

int Socket::getClientSocketFD()
{
	return (this->_client_socket_fd);
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