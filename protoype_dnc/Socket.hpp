/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/08 21:58:05 by shaas            ###   ########.fr       */
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

#define SCK_ADDR sockaddr_in

#define PORT 8080

class Socket
{
private:
	int _server_socket_fd;
	int _client_socket_fd;
	//int _bind;
	int _listen;
	SCK_ADDR _address;

	void initSockAddr();

public:
	Socket();

	int getClientSocketFD();
	void waitForConnect();

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
