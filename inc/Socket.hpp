/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/13 21:29:00 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>

#define SCK_ADDR sockaddr_in

#define PORT 8080

struct File
{
	std::string content;
	int fileSize;
};


class Socket
{
	private:
		int _server_socket_fd;
		int _port;
		size_t len;
	public:
		SCK_ADDR _address;
	
	private:
		void printFile(File&);
	
	public:
		Socket(int _port);
	
		int getClientSocketFD();
		int getServerSocketFD();
		int getRefAddrlen();
		void setClientSocketFD(int);
		void initSockAddr(int);
		// void waitForConnect();
		// File getFileContent(std::string&);
		// std::string getHeaderRequest(void*);
	
		class NoSocketException: public std::exception
		{
			const char* what() const throw();
		};
		
};


#endif
