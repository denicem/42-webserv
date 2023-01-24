/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPPoll.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:33:54 by mjeyavat          #+#    #+#             */
/*   Updated: 2023/01/14 22:10:26 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TCPPoll.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "File.hpp"

TCPPoll::TCPPoll() {
	this->pollStatus = 1;
	this->index = 0;
	this->len = INADDR_ANY;
}

void TCPPoll::add_fds(Server server) {
	this->sfds.push_back(server);
}

void TCPPoll::status_check() {
	PRINT_W_COLOR(LIGHTGREEN, "Status check is starting")
	PRINT_W_COLOR(BLUE, ("\nMax connection are: " + intToString(getMaxConnection())))
	
	//bind, listen, sock option (Sockets)
	for(int i = 0; i < getMaxConnection(); i++)
	{
		//clean pollfd stuct
		memset(&connection_poll[i], 0, sizeof(pollfd));
		
		//init sockets !Falls es mehr ports sind einfach die 0 auf i umstellen
		this->sfds[i].initSockAddr(this->len , 0);
		
		//kill all ports that are in use
		if (setsockopt(this->sfds[i].getServerSocketFD(), SOL_SOCKET, SO_REUSEADDR, &pollStatus, sizeof(this->pollStatus)) != 0)
			perror("Cannot set socket option");
		
		if (bind(this->sfds[i].getServerSocketFD(),
			(struct sockaddr *) &this->sfds[i]._address,
			sizeof(SCK_ADDR)) < 0)
			throw NoBindException();

		if (listen(this->sfds[i].getServerSocketFD(), 10) < 0)
			throw NoListenException();
	}
	PRINT_W_COLOR(LIGHTGREEN, "\nPoll struct about to inizialised")
	//init poll struct
	for(int i = 0; i < getMaxConnection(); i++)
	{
		std::cout << "server filedescriptor: " << sfds[i].getServerSocketFD() << std::endl;
		connection_poll[i].fd = sfds[i].getServerSocketFD();
		connection_poll[i].events = POLL_IN;
	}
	//mainloop 
	PRINT_W_COLOR(LIGHTCYAN, "\n\nHTTP PART")
	while(1)
	{
		pollStatus = poll(connection_poll, (unsigned int) getMaxConnection(), TIMEOUT);
		switch (pollStatus)
		{
			case POLL_EXPIRE:
				cout << "Timeout has expired!" << endl;
				break;
			case POLL_ERR:
				cout << "Error on poll" << endl;
				break ;
			default:
				for (index = 0; index < getMaxConnection(); index++)
				{
					if (connection_poll[index].revents & POLL_IN)
					{
						std::vector<unsigned char> buff(MAXBUFF);
						std::string str_buff;
						cout << "\n---------- We have a connection -----------\n\n";
						acceptedFd = accept(sfds[index].getServerSocketFD(), (struct sockaddr *)&sfds[index]._address, (socklen_t *) &len);
						std::cout << MAGENTA << "Port " << this->sfds[index].getPort(0) << " connected to client." << RESET << std::endl;	
						//read and write to client
						while (1) {
							int bytes_rec = recv(acceptedFd, &buff[0], MAXBUFF, 0);
							str_buff.insert(str_buff.end(), &buff[0], &buff[bytes_rec]);
							buff.clear();
							if (bytes_rec < MAXBUFF)
								break ;
						}

						// PRINT_W_COLOR(LIGHTBLUE, "BUFFER")
						// PRINT_W_COLOR(BOLD, str_buff)

						// this->sfds[index].printRoutes();

						HttpRequest req(str_buff);
						PRINT_W_COLOR(LIGHTBLUE, "HTTP Request")
						PRINT_W_COLOR(BOLD, req)

						HttpAction act(req, this->sfds[index]);
						act.doAction(this->sfds[index]);

						HttpResponse resp(act);
						std::string resp_msg(resp.genHttpResponseMsg());
						PRINT_W_COLOR(LIGHTBLUE, "HTTP Response")
						PRINT_W_COLOR(BOLD, resp)

						send(acceptedFd, resp_msg.c_str(), resp_msg.length(), 0);
						std::cout << "\n-------- msg sent --------\n";
						close(acceptedFd);
					}
				}
		}
	}
}

int TCPPoll::getMaxConnection(){
	return (this->maxConnection);
}

void TCPPoll::setMaxConnection(){
	int connectionAmount = 1;

	for(size_t i = 0; i < sfds.size(); i++, connectionAmount++)
	{
		std::cout << "i: " << i << std::endl;
		this->maxConnection = connectionAmount;
	}
}

const char* TCPPoll::NoBindException::what() const throw()
{
	return ("\033[31;1mBind failed.\033[0m");
}

const char* TCPPoll::NoListenException::what() const throw()
{
	return ("\033[31;1mListen failed.\033[0m");
}