/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:41:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/07 16:40:24 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

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
	cout <<					"                             \"\"\"\"---\"\"\"\"" << '\n';
	
}

int main(int argc, char* argv[])
{
	try {
		Config	config(Config::getFilePath(argc, argv));
		Config::printServerConfig(config.getConfigData());
		//const vector<ServerConfig>& server_data = config.getConfigData();
	

		logo();

		//TODO: parsing muss ausgeführt werden
		Webserv dmsServer;
		TCPPoll tcpPoll;
		//ports list for testing testing 
		vector<int>			ports;
		vector<HttpMethod>	allowedMethods;
		vector<Location>	locations;
		allowedMethods.push_back(GET);
		allowedMethods.push_back(POST);
		allowedMethods.push_back(DELETE);
		locations.push_back(Location("/hehe", "html", "hello.html", allowedMethods, false));
		locations.push_back(Location("/ho", "www", "/index.html", allowedMethods, true));
		ports.push_back(8080);
		ports.push_back(8081);
		ports.push_back(8082);
		
		dmsServer.addServer(ports, "test_server_1", "html",locations);
		dmsServer.addServer(ports, "test_server_2", "html", locations);
		dmsServer.addServer(ports, "test_server_3", "html", locations);
		for (int i = 0; i < 3; i++)
			tcpPoll.add_fds(dmsServer.getServer(i));
		// 	tcpPoll.add_fds(Server(PORT + i, "simple"));
		tcpPoll.status_check();
	}
	catch (exception& e) {
		cerr << e.what() << " ERRNO: " << errno << '\n';
	}
	return (0);
}