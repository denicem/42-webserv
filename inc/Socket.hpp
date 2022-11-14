/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/14 01:16:19 by dmontema         ###   ########.fr       */
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

class Socket
{
	private:
		int _server_socket_fd;
		int _port;
		size_t len;
	public:
		SCK_ADDR _address;
	
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
