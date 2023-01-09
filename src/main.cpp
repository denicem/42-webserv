/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:41:54 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/09 05:23:57 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

vector<string>	g_http_methods;
vector<string>	g_cgi_extensions;

void	initGlobals(void)
{
	g_http_methods.push_back("GET");
	g_http_methods.push_back("DELETE");
	g_http_methods.push_back("POST");

	g_cgi_extensions.push_back(".py");
	g_cgi_extensions.push_back(".cgi");
}

void	logo(void)
{
	cout <<					"                           _.-,=_\"\"\"--,_" << '\n';
	cout <<					"                        .-\" =/7\"   _  .3#\"=." << '\n';
	cout << GREEN << BOLD <<	"      " << "Welcome to" << RESET << "      ,#7  \" \"  ,//)#d#######=." << '\n';
	cout << GREEN << BOLD <<	"         " << "the" << RESET << "        ,/ \"      # ,i-/###########=" << '\n';
	cout <<					"                   /         _)#sm###=#=# #######\\" << '\n';
	cout <<					"                  /         (#/\"_`;\\//#=#\\-#######\\" << '\n';
	cout <<					"                 /         ,d####-_.._.)##P########\\" << '\n';
	cout << BLUE << BOLD <<	" __                     _                                              __ " << '\n';
	cout <<					"| _|   __ _ _ __   __ _| | ___   __ _   ___  ___ _ ____   _____ _ __  |_ |" << '\n';
	cout <<					"| |   / _` | '_ \\ / _` | |/ _ \\ / _` | / __|/ _ \\ '__\\ \\ / / _ \\ '__|  | |" << '\n';
	cout <<					"| |  | (_| | | | | (_| | | (_) | (_| | \\__ \\  __/ |   \\ V /  __/ |     | |" << '\n';
	cout <<					"| |   \\__,_|_| |_|\\__,_|_|\\___/ \\__, | |___/\\___|_|    \\_/ \\___|_|     | |" << '\n';
	cout <<					"|__|                            |___/                                 |__|" << '\n';
	cout << RESET <<			"                  \\B             /#######7 /      /" << '\n';
	cout <<					"                   \\             \\######\" /\"     /" << '\n';
	cout <<					"                    `.            \\###7'       ,'" << '\n';
	cout <<					"                      \"-_          `\"'      ,-'     " << DARKGRAY << BOLD << "by Denice, Mo & Svenja" << RESET << '\n';
	cout <<					"                         \"-._           _.-\"" << '\n';
	cout <<					"                             \"\"\"\"---\"\"\"\"" << "\n\n\n";
	
}

int main(int argc, char* argv[])
{
	try {
		initGlobals();

		Config*	config = new Config(Config::getFilePath(argc, argv));
		vector<struct ServerConfig>	server_data;
		config->extractConfigData(server_data);
		delete config;
		Config::printServerConfig(server_data);
		// const vector<ServerConfig>& server_data = *config.getConfigData();

		logo();

		CGI	cgi;
		cout << cgi.executeCGI();
		return (0);
		//cgi.executeCGI();

		//TODO: parsing muss ausgeführt werden
		Webserv dmsServer;
		TCPPoll tcpPoll;
		vector<Server> servers;
		
std::cout << "\e[31m servers are being inizialised\e[0m" << std::endl;
		for(size_t i = 0; i < server_data.size(); i++) {
			Server s(server_data[i]);
			servers.push_back(s);
			dmsServer.addServer(servers[i]);
		}
		// for(size_t i = 0; i < servers.size(); i++)
		// 	std::cout << "Server: " << servers.at(i).getPort(0) << std::endl;
		// std::cout << "server name: " << *dmsServer.getServer(0).getServernameList().begin() << std::endl;

std::cout << "\e[31m server fds being added to poll\e[0m" << std::endl;
		for (size_t i = 0; i < server_data.size(); i++)
		{
			std::cout << "i in Loop is: " << i << std::endl;
			tcpPoll.add_fds(dmsServer.getServer(i));
			// std::cout << "server port: " << dmsServer.getServer(i) << std::endl;
		}
		// 	tcpPoll.add_fds(Server(PORT + i, "simple"));
std::cout << "\e[31m status check is being called\e[0m" << std::endl;
		
		tcpPoll.status_check(); 
	}
	catch (exception& e) {
		cerr << e.what() << "\nERRNO: " << errno << '\n';
	}
	return (0);
}
