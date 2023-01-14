/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 01:43:34 by dmontema         ###   ########.fr       */
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
#include "Location.hpp"
#include "Route.hpp"
#include "Config.hpp"
#include "HttpMethod.hpp"

#define SCK_ADDR sockaddr_in

class Location;
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
		vector<Location> locations; // NOTE: Locations as a map<string, Location> with location name as Key??
		vector<Route> routes;
		map<int, string> error_pages;
		

		/* for TCP */
		int serverSocketFD;
	public:
		SCK_ADDR _address;
		Server(const string&, const string&, const vector<Location> &);
		Server(const struct ServerConfig& config);
	
		string							getServerName() const;
		string							getRoot() const;
		int								getPort(const int) const;
		Location						getLocation(const int) const;
		Route							getRoute(const int) const;
		int								getRouteCount() const;
		const std::vector<Location>&	getLocations() const;
		int 							getServerSocketFD() const;
		string							getErrorPage(int) const;

		void	setServerName(string&);
		void	setPort(int);
		void	setLocation(const Location&);

		void setLocations(map<string, struct RouteConfig>);
		void initSockAddr(int, int);
	
		string getIndexFile() const;
		vector<HttpMethod> genarateAllowedMethods(vector<string>methods);
		vector<string> getServernameList();
		class NoSocketException: public exception
		{
			const char* what() const throw();
		};
};
