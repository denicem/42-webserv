/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcpPoll.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:33:54 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/11/15 17:29:14 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TCPPoll.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "File.hpp"

TCPPoll::TCPPoll(){

	this->j = 0;
	this->i = 0;
	this->len = INADDR_ANY;
}

void TCPPoll::add_fds(Socket socket){
	this->sfds.push_back(socket);
}

void TCPPoll::status_check()
{
	memset(this->buffer, 0, MAXBUFF);
	
	//bind, listen, sock option (Sockets)
	for(int i = 0; i < MAX_CONN; i++)
	{
		//clean pollfd stuct
		memset(&connection_poll[i], 0, sizeof(pollfd));
		
		//init sockets
		this->sfds[i].initSockAddr(this->len);
		if(bind(this->sfds[i].getServerSocketFD(),
		(struct sockaddr *) &this->sfds[i]._address,
		sizeof(SCK_ADDR)) < 0)
			throw NoBindException();
		
		if( setsockopt(this->sfds[i].getServerSocketFD(), SOL_SOCKET, SO_REUSEADDR, &j, sizeof(int)) < 0)
			perror("Cannot set socket option");

		if(listen(this->sfds[i].getServerSocketFD(), 10) < 0)
			throw NoListenException();
		
	}
	
	//init poll struct
	for(int i = 0; i < MAX_CONN; i++)
	{
		connection_poll[i].fd = sfds[i].getServerSocketFD();
		connection_poll[i].events = POLL_IN;
	}

	//mainloop 
	while(1)
	{
		j = poll(connection_poll, (unsigned int)MAX_CONN,TIMEOUT);
		switch(j)
		{
			case POLL_EXPIRE:
				std::cout << "Timeout has expired!" << std::endl;
				break;
			case POLL_ERR:
				std::cout << "Error on poll" << std::endl;
			default:
				for( i = 0; i < MAX_CONN; i++)
				{
					if(connection_poll[i].revents & POLL_IN)
					{
						std::cout << "\n---------- We have a connection -----------\n\n";
						acceptedFd = accept(sfds[i].getServerSocketFD(), (struct sockaddr *)&sfds[i]._address, (socklen_t *) &len);
						//read and write to client
						if (recv(acceptedFd, this->buffer, 30000, 0) < 0)
							std::cout << "No bytes are there to read.\n";
						// std::cout << "buffer len after recv:\t" << this->len << std::endl; 
						std::cout << "Port " << this->sfds[i].getPort() << " connected to client." << std::endl;
						HttpRequest req(this->buffer);
						HttpResponse resp(req.getURI());
						std::string respMsg(resp.genHttpResponseMsg());
						send(acceptedFd, respMsg.c_str(), respMsg.length(), 0);
						std::cout << "\n-------- msg sent --------\n";
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