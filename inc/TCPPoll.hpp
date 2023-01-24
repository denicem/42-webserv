/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPPoll.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:23:50 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/12/17 13:32:25 by mjeyavat         ###   ########.fr       */
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
#include "Server.hpp"
class Server;

#include "Webserv.hpp"

/* our defines */

#define MAXBUFF          (8192)
#define MAX_CONN         (3)
#define TIMEOUT          (1024 * 1024)
#define MY_MAX(a,b)      (a = (a > b) ? a : b )
#define POLL_EXPIRE      (0)

/**
 * nt socketIn, string srcIP, int port
*/

class TCPPoll
{
	private:
		// sockaddr_in sock[MAX_CONN];
		pollfd connection_poll[MAX_CONN];
		vector<Server> sfds;
		int pollStatus, index, acceptedFd;
		size_t len;
		char buffer[MAXBUFF];
		int maxConnection;
		
	public:
		TCPPoll();
		void add_fds(Server);
		void status_check();
		

		int getMaxConnection();
		void setMaxConnection();

		class NoBindException: public exception
		{
			const char* what() const throw();
		};
		
		class NoSocketOpt: public exception
		{
			const char* what() const throw();
		};

		class NoListenException: public exception
		{
			const char* what() const throw();
		};

		class NoAcceptException: public exception
		{
			const char* what() const throw();
		};
		// ~TCPPoll();
};