/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:41:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/17 19:00:33 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

void	logo(void)
{
	std::cout <<					"                           _.-,=_\"\"\"--,_" << '\n';
	std::cout <<					"                        .-\" =/7\"   _  .3#\"=." << '\n';
	std::cout <<					"      " << GREEN << "Welcome to" << RESET << "      ,#7  \" \"  ,//)#d#######=." << '\n';
	std::cout <<					"         " << GREEN << "the" << RESET << "        ,/ \"      # ,i-/###########=" << '\n';
	std::cout <<					"                   /         _)#sm###=#=# #######\\" << '\n';
	std::cout <<					"                  /         (#/\"_`;\\//#=#\\-#######\\" << '\n';
	std::cout <<					"                 /         ,d####-_.._.)##P########\\" << '\n';
	std::cout << BLUE << BOLD <<	" __                     _                                              __ " << '\n';
	std::cout <<					"| _|   __ _ _ __   __ _| | ___   __ _   ___  ___ _ ____   _____ _ __  |_ |" << '\n';
	std::cout <<					"| |   / _` | '_ \\ / _` | |/ _ \\ / _` | / __|/ _ \\ '__\\ \\ / / _ \\ '__|  | |" << '\n';
	std::cout <<					"| |  | (_| | | | | (_| | | (_) | (_| | \\__ \\  __/ |   \\ V /  __/ |     | |" << '\n';
	std::cout <<					"| |   \\__,_|_| |_|\\__,_|_|\\___/ \\__, | |___/\\___|_|    \\_/ \\___|_|     | |" << '\n';
	std::cout <<					"|__|                            |___/                                 |__|" << '\n';
	std::cout << RESET <<			"                  \\B             /#######7 /      /" << '\n';
	std::cout <<					"                   \\             \\######\" /\"     /" << '\n';
	std::cout <<					"                    `.            \\###7'       ,'" << '\n';
	std::cout <<					"                      \"-_          `\"'      ,-'     " << DARKGRAY << "by Denice, Mo & Svenja" << RESET << '\n';
	std::cout <<					"                         \"-._           _.-\"" << '\n';
	std::cout <<					"                             \"\"\"\"---\"\"\"\"" << '\n';
	
}

int main()
{
	logo();
	try {
		webserv dsm_server;
		TCPPoll tcp_poll;
		//ports list for testing testing 
		std::vector<int>ports;
		ports.push_back(8080);
		ports.push_back(8081);
		ports.push_back(8082);
		
		dsm_server.addServer(ports, "test_server_1");
		dsm_server.addServer(ports, "test_server_2");
		dsm_server.addServer(ports, "test_server_3");
		for(int i = 0; i < 3; i++)
			tcp_poll.add_fds(dsm_server.getServerFromList(i));
		// 	tcp_poll.add_fds(Server(PORT + i, "simple"));
		tcp_poll.status_check();
	} catch (std::exception& e) {
		std::cout << e.what() << " ERRNO: " << errno << '\n';
	}
	return (0);
}