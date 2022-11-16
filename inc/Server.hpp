/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/16 18:40:26 by shaas            ###   ########.fr       */
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

class Server
{
	private:
		int _server_socket_fd;
		int _port;
		size_t len;
		//for identiyfing purposes
		std::string socketId;
	public:
		SCK_ADDR _address;
	
	public:
		Server(int _port, std::string sId);
	
		int getClientSocketFD();
		int getServerSocketFD();
		int getRefAddrlen();
		void setClientSocketFD(int);
		void initSockAddr(int);
		int getPort();
		// void waitForConnect();
		// File getFileContent(std::string&);
		// std::string getHeaderRequest(void*);
	
		class NoSocketException: public std::exception
		{
			const char* what() const throw();
		};
		
};


#endif
