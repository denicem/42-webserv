/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCPPoll.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:33:54 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/12/15 16:29:39 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TCPPoll.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "File.hpp"

TCPPoll::TCPPoll() {
	this->pollStatus = 1;
	this->i = 0;
	this->len = INADDR_ANY;
}

void TCPPoll::add_fds(Server server) {
	this->sfds.push_back(server);
}

void TCPPoll::status_check()
{
	memset(this->buffer, 0, MAXBUFF);
	
	//bind, listen, sock option (Sockets)
	for(int i = 0; i < MAX_CONN; i++)
	{
		//clean pollfd stuct
		memset(&connection_poll[i], 0, sizeof(pollfd));
		
		//init sockets !Falls es mehr ports sind einfach die 0 auf i umstellen
		this->sfds[i].initSockAddr(this->len , 0);
		
		//kill all ports that are in use
		if (setsockopt(this->sfds[i].getServerSocketFD(), SOL_SOCKET, SO_REUSEADDR, &pollStatus, sizeof(int)) == -1)
			perror("Cannot set socket option");
		
		if (bind(this->sfds[i].getServerSocketFD(),
			(struct sockaddr *) &this->sfds[i]._address,
			sizeof(SCK_ADDR)) < 0)
			throw NoBindException();

		if (listen(this->sfds[i].getServerSocketFD(), 10) < 0)
			throw NoListenException();
	}
	
	//init poll struct
	for(int i = 0; i < MAX_CONN; i++)
	{
		std::cout << "server filedescriptor: " << sfds[i].getServerSocketFD() << std::endl;
		connection_poll[i].fd = sfds[i].getServerSocketFD();
		connection_poll[i].events = POLL_IN;
	}
	//mainloop 
	while(1)
	{
		pollStatus = poll(connection_poll, (unsigned int) MAX_CONN, TIMEOUT);
		switch (pollStatus)
		{
			case POLL_EXPIRE:
				cout << "Timeout has expired!" << endl;
				break;
			case POLL_ERR:
				cout << "Error on poll" << endl;
			default:
				for (i = 0; i < MAX_CONN; i++)
				{
					if (connection_poll[i].revents & POLL_IN)
					{
						cout << "\n---------- We have a connection -----------\n\n";
						acceptedFd = accept(sfds[i].getServerSocketFD(), (struct sockaddr *)&sfds[i]._address, (socklen_t *) &len);
						//read and write to client
						if (recv(acceptedFd, this->buffer, MAXBUFF, 0) < 0)
							std::cout << "No bytes are there to read.\n";
						std::cout << "Port " << this->sfds[i].getPort(0) << " connected to client." << std::endl;	
						// std::cout << "$$$$$$$$$$$$$$$$$$$$" << std::endl;
						// std::cout << this->buffer << std::endl;
						// std::cout << "$$$$$$$$$$$$$$$$$$$$" << std::endl;
						HttpRequest req(this->buffer);
						// std::cout << req << std::endl;
						HttpAction act(req, this->sfds[i]);
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

const char* TCPPoll::NoBindException::what() const throw()
{
	return ("\033[31;1mBind failed.\033[0m");
}

const char* TCPPoll::NoListenException::what() const throw()
{
	return ("\033[31;1mListen failed.\033[0m");
}