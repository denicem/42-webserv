/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:41:54 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 03:41:12 by dmontema         ###   ########.fr       */
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

		logo();

		// CGI	cgi;
		// cout << cgi.executeCGI();
		// return (0);
		//return (0);

		Webserv dmsServer;
		TCPPoll tcpPoll;
		vector<Server> servers;
		
		PRINT_W_COLOR(LIGHTGREEN, "Servers are being initialized.")
		for(size_t i = 0; i < server_data.size(); ++i) {
			Server s(server_data[i]);
			servers.push_back(s);
			dmsServer.addServer(servers[i]);
		}
		for(size_t i = 0; i < servers.size(); ++i) {
			std::cout << "Server: " << servers.at(i).getPort(0) << std::endl;
			std::cout << "server name: " <<
				(dmsServer.getServer(i).getServernameList().empty() ? "-" : *dmsServer.getServer(i).getServernameList().begin()) 
				<< std::endl;
		}

		PRINT_W_COLOR(LIGHTGREEN, "\nServer fds being added to poll");
		for (size_t i = 0; i < server_data.size(); i++)
		{
			std::cout << "i in Loop is: " << i << std::endl;
			tcpPoll.add_fds(dmsServer.getServer(i));
			// std::cout << "server port: " << dmsServer.getServer(i).getServerName() << std::endl;
		}
		tcpPoll.setMaxConnection();
		// 	tcpPoll.add_fds(Server(PORT + i, "simple"));
		PRINT_W_COLOR(LIGHTGREEN, "\nStatus check is being called");

		tcpPoll.status_check();
	}
	catch (exception& e) {
		cerr << e.what() << '\n'; //"\nERRNO: " << errno << '\n';
	}
	return (0);
}
