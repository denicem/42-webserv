/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:08:03 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/13 16:36:15 by mjeyavat         ###   ########.fr       */
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
#include "Config.hpp"
#include "HttpMethod.hpp"

#define SCK_ADDR sockaddr_in

#define PORT 8080

class Location;

class Server
{
	private:
		string serverName;
		vector<string> serverNames;
		// int onePort;
		int clientMaxBody;
		string root;
		string indexFile;
		//string index/default_file -> TODO:
		vector<int> ports;
		vector<Location> locations;
		// NOTE: Locations as a map<string, Location> with location name as Key

		/* for TCP */
		int serverSocketFD;
		// size_t len;

	public:
		SCK_ADDR _address;
	
	public:
		Server(const string&, const string&, const vector<Location> &);
		Server(const struct ServerConfig& config);
	
		string							getServerName() const;
		string							getRoot() const;
		int								getPort(const int) const;
		Location						getLocation(const int) const;
		const std::vector<Location>&	getLocations() const;
		int 							getServerSocketFD() const;

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
