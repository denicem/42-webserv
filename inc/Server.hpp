/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 22:32:10 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

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

#include "Webserv.hpp"
#include "Route.hpp"
#include "Config.hpp"
#include "HttpMethod.hpp"

#define SCK_ADDR sockaddr_in

class Route;

class Server
{
	private:
		string serverName;
		vector<string> serverNames;
		int clientMaxBody;
		string root;
		string indexFile;
		vector<int> ports;
		vector<Route> routes;
		map<int, string> error_pages;

		/* for TCP */
		int serverSocketFD;

	public:
		SCK_ADDR _address;

	public:
		Server(const struct ServerConfig& config);
	
		string getIndexFile() const;
		string							getServerName() const;
		int 							getClientMaxBody() const;
		string							getRoot() const;
		int								getPort(const int) const;
		Route							getRoute(const int) const;
		int								getRouteCount() const;
		int 							getServerSocketFD() const;
		string							getErrorPage(int) const;
		vector<string> getServernameList();

		void	setServerName(string&);
		void	setPort(int);
		void 	setRoutes(map<string, struct RouteConfig>);

		void initSockAddr(int, int);
		vector<HttpMethod> genarateAllowedMethods(vector<string>methods);
		void printRoutes() const;

		class NoSocketException: public exception
		{
			const char* what() const throw();
		};
};
