/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/09 03:49:32 by dmontema         ###   ########.fr       */
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
#define PORT42 4242

struct File
{
	std::string content;
	int fileSize;
};

class Socket
{
private:
	int _server_socket_fd;
	int _client_socket_fd;
	//int _bind;
	int _listen;
	SCK_ADDR _address;

	void printFile(File&);
	void initSockAddr();

public:
	Socket();

	int getClientSocketFD();
	void waitForConnect();
	File getFileContent(std::string&);
	std::string getHeaderRequest(void*);

	class NoSocketException: public std::exception
	{
		const char* what() const throw();
	};
	class NoBindException: public std::exception
	{
		const char* what() const throw();
	};
	class NoListenException: public std::exception
	{
		const char* what() const throw();
	};
	class NoAcceptException: public std::exception
	{
		const char* what() const throw();
	};
};


#endif
