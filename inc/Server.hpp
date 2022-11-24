/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/24 00:06:29 by shaas            ###   ########.fr       */
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
#include <vector>

#include "webserv.hpp"

#define SCK_ADDR sockaddr_in

#define PORT 8080

class Server
{
	private:
		int _server_socket_fd;
		// int _port;
		vector<int>_port;
		size_t len;
		//for identiyfing porposes
		string serverName;
	public:
		SCK_ADDR _address;
	
	public:
		Server(string sId);
	
		int getClientSocketFD();
		int getServerSocketFD();
		int getRefAddrlen();
		int getPort(int);
		string getServerName();

		void setClientSocketFD(int);
		void initSockAddr(int, int);
		void setServerName(string);
		void setPort(int);
	
		class NoSocketException: public exception
		{
			const char* what() const throw();
		};
		
};


#endif
