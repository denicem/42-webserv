/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:41:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/15 14:45:13 by mjeyavat         ###   ########.fr       */
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
	g_cgi_extensions.push_back(".c");
	g_cgi_extensions.push_back(".dms");
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

		//TODO: parsing muss ausgeführt werden
		Webserv dmsServer;
		TCPPoll tcpPoll;
		//ports list for testing testing 
		// vector<int>			ports;
		// vector<HttpMethod>	allowedMethods;
		// vector<Location>	locations;
		// allowedMethods.push_back(GET);
		// allowedMethods.push_back(POST);
		// allowedMethods.push_back(DELETE);
		// locations.push_back(Location("/hehe", "html", "hello.html", allowedMethods, false));
		// locations.push_back(Location("/ho", "www", "/index.html", allowedMethods, true));
		// ports.push_back(8080);
		// ports.push_back(8081);
		// ports.push_back(8082);
		
		// dmsServer.addServer(ports, "test_server_1", "html",locations);
		// dmsServer.addServer(ports, "test_server_2", "html", locations);
		// dmsServer.addServer(ports, "test_server_3", "html", locations);
		vector<Server> servers;
		for(size_t i = 0; i < server_data.size(); i++) {
			Server s(server_data[i]);
			servers.push_back(s);
			dmsServer.addServer(servers[i]);
		}

		// for(size_t i = 0; i < servers.size(); i++)
		// 	std::cout << "Server: " << servers.at(i).getPort(0) << std::endl;
		// std::cout << "server name: " << *dmsServer.getServer(0).getServernameList().begin() << std::endl;

		for (int i = 0; i < 3; i++)
		{
			tcpPoll.add_fds(dmsServer.getServer(i));
			// std::cout << "server port: " << dmsServer.getServer(i) << std::endl;
		}
		// 	tcpPoll.add_fds(Server(PORT + i, "simple"));
		
		tcpPoll.status_check(); }
	catch (exception& e) {
		cerr << e.what() << "\nERRNO: " << errno << '\n';
	}
	return (0);
}