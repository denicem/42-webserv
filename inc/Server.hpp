/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/17 19:29:04 by mjeyavat         ###   ########.fr       */
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

#define SCK_ADDR sockaddr_in

#define PORT 8080

class Server
{
	private:
		int _server_socket_fd;
		// int _port;
		std::vector<int>_port;
		size_t len;
		//for identiyfing porposes
		std::string serverName;
	public:
		SCK_ADDR _address;
	
	public:
		Server(std::string sId);
	
		int getClientSocketFD();
		int getServerSocketFD();
		int getRefAddrlen();
		int getPort(int);
		std::string getServerName();

		void setClientSocketFD(int);
		void initSockAddr(int, int);
		void setServerName(std::string);
		void setPort(int);
	
		class NoSocketException: public std::exception
		{
			const char* what() const throw();
		};
		
};


#endif
