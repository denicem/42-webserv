/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcpPoll.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:23:50 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/11/13 21:30:16 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <poll.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <vector>
#include "Socket.hpp"


/* our defines */

#define MAXBUFF          (30000)
#define MAX_CONN         (3)
#define TIMEOUT          (1024 * 1024)
#define MY_MAX(a,b)      (a = (a > b) ? a : b )
#define POLL_EXPIRE      (0)

/**
 * nt socketIn, std::string srcIP, int port
*/

class tcpPoll
{
	private:
		// sockaddr_in sock[MAX_CONN];
		pollfd connection_poll[MAX_CONN];
		std::vector<Socket> sfds;
		int j, i, acceptedFd;
		size_t len;
		char buffer[30000];
		
	public:
		tcpPoll();
		void add_fds(Socket);
		void status_check();
		

		class NoBindException: public std::exception
		{
			const char* what() const throw();
		};
		
		class NoSocketOpt: public std::exception
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
		// ~tcpPoll();
};