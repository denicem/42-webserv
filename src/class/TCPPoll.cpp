/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPPoll.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:33:54 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/12/17 16:28:40 by dmontema         ###   ########.fr       */
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
	static int i = 0;
	std::cout << "server " << i << "is being added to the list" << std::endl;
	this->sfds.push_back(server);
	if(i == 0)
		this->setMaxConnection(1);
	else
		this->setMaxConnection(i);
	i++;
}

void TCPPoll::status_check()
{
	std::cout << "status_check is starting: " << std::endl;
	memset(this->buffer, 0, MAXBUFF);
	
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
	std::cout << "Poll struct about to inizialised" << std::endl;
	//init poll struct
	for(int i = 0; i < getMaxConnection(); i++)
	{
		std::cout << "server filedescriptor: " << sfds[i].getServerSocketFD() << std::endl;
		connection_poll[i].fd = sfds[i].getServerSocketFD();
		connection_poll[i].events = POLL_IN;
	}
	//mainloop 
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
						cout << "\n---------- We have a connection -----------\n\n";
						acceptedFd = accept(sfds[index].getServerSocketFD(), (struct sockaddr *)&sfds[index]._address, (socklen_t *) &len);
						//read and write to client
						if (recv(acceptedFd, this->buffer, MAXBUFF, 0) < 0)
							std::cout << "No bytes are there to read.\n";
						std::cout << "Port " << this->sfds[index].getPort(0) << " connected to client." << std::endl;	
						// std::cout << "$$$$$$$$$$$$$$$$$$$$" << std::endl;
						// std::cout << this->buffer << std::endl;
						// std::cout << "$$$$$$$$$$$$$$$$$$$$" << std::endl;
						HttpRequest req(this->buffer);
						std::cout << MAGENTA;
						for (size_t i = 0; i < sfds[index].getLocations().size(); ++i) {
							std::cout << sfds[index].getLocation(i) << std::endl;
						}
						std::cout << RESET << std::endl;
						std::cout << LIGHTBLUE << req << RESET << std::endl;
						// std::cout << req << std::endl;
						HttpAction act(req, this->sfds[index]);
						// HttpResponse resp(req, this->sfds[i]);
						HttpResponse resp(act);
						std::string respMsg(resp.genHttpResponseMsg(act));
						send(acceptedFd, respMsg.c_str(), respMsg.length(), 0);
						std::cout << "\n-------- msg sent --------\n";
						memset(this->buffer, 0, MAXBUFF); // NOTE: resets everything to zero for the next loop to read into the buffer.
						close(acceptedFd);
					}
				}
		}
	}
}

int TCPPoll::getMaxConnection(){
	return (this->maxConnection);
}

void TCPPoll::setMaxConnection(int connectionAmount){
	this->maxConnection = connectionAmount;
}

const char* TCPPoll::NoBindException::what() const throw()
{
	return ("\033[31;1mBind failed.\033[0m");
}

const char* TCPPoll::NoListenException::what() const throw()
{
	return ("\033[31;1mListen failed.\033[0m");
}