/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:09:52 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/10 18:07:23 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.hpp"
#include <sstream>

Socket::Socket()
{
	this->_server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_server_socket_fd == 0)
		throw NoSocketException();
	initSockAddr();
	// this->_listen = listen(this->_server_socket_fd, 10);
	// if(this->_listen < 0)
		// throw NoListenException();
}

void Socket::initSockAddr()
{
	// memset((char *)&this->_address, 0, sizeof(this->_address));
	memset(this->_address.sin_zero, 0, sizeof(this->_address.sin_zero));
	this->_address.sin_family = AF_INET;
	this->_address.sin_addr.s_addr = INADDR_ANY;
	this->_address.sin_port = htons(PORT42);
	
	if (bind(this->_server_socket_fd,(struct sockaddr *) &_address, sizeof(_address)) < 0)
		throw NoBindException();
}

void Socket::printFile(File& file)
{
	std::cout << file.fileSize << " bytes." << std::endl << "Content:\n" << file.content << std::endl;
}

// NOTE: gets the (html-)file from the html directory
File Socket::getFileContent(std::string& name)
{
	
	File res; // NOTE: struct File, which has the variables content (std::string) and fileSize (int).
	std::cout << name << std::endl;
	std::ifstream file("html" + name, std::ios::binary);

	// calc the size of the file
	file.seekg(0, std::ios::end);
	res.fileSize = file.tellg();
	//resets to beginning of the file
	file.clear();
	file.seekg(0);

	// copy its content to the string
	if (file.is_open())
	{
		std::string text;
		while (!file.eof())
		{
			std::getline(file, text);
			res.content.append(text);
			if (!file.eof())
				res.content.append("\n");
		}
	}
	return (res);
}

// NOTE: gets the header of the request (GET / HTTP/1.1, ...)
std::string Socket::getHeaderRequest(void* buff)
{
	std::string res((const char *)buff);
	std::stringstream strstr(res);
	strstr >> res;
	strstr >> res;
	return (res);
}

void Socket::waitForConnect()
{
	int addrlen = sizeof(this->_address);
	if(listen(this->_server_socket_fd, 10) < 0)
		throw NoListenException();
	while (42)
	{
		std::cout << "\n---------- Waiting for connection -----------\n\n";
		this->_client_socket_fd = accept(this->_server_socket_fd, (struct sockaddr *) &this->_address, (socklen_t*) &addrlen);
		if (this->_client_socket_fd < 0)
			throw NoAcceptException();
		char buffer[30000] = {0};
		int valread = recv(this->_client_socket_fd, buffer, 30000, 0);
		if (valread < 0)
			std::cout << "No bytes are there to read.\n";
		std::cout << buffer << std::endl;
		std::string hello = "HTTP/1.1 200 OK\nFilename from Server: ";
		std::string filename = getHeaderRequest(buffer);
		if (filename == "/")
			filename = "/index.html";
		if (filename.find("favicon.ico") != std::string::npos)
			filename = "/favicon.ico";
		File file = getFileContent(filename);
		// printFile(file);
		std::cout << filename << " (" << file.fileSize << " bytes.)" << std::endl;
		hello.append(filename);
		hello.append("\nContent-Type: text/html\nContent-Length: ");
		hello.append(std::to_string(file.fileSize)); // TODO: implement own to_string()
		hello.append("\n\n");
		hello.append(file.content);

		send(this->_client_socket_fd, hello.c_str(), hello.length(), 0);
		std::cout << "-------- msg sent --------\n";
		close(this->_client_socket_fd);
	}
}

int Socket::getClientSocketFD()
{
	return (this->_client_socket_fd);
}

const char* Socket::NoSocketException::what() const throw()
{
	return ("\033[31;1mCannot create socket.\033[0m");
}
const char* Socket::NoBindException::what() const throw()
{
	return ("\033[31;1mBind failed.\033[0m");
}
const char* Socket::NoListenException::what() const throw()
{
	return ("\033[31;1mIn listen.\033[0m");
}
const char* Socket::NoAcceptException::what() const throw()
{
	return ("\033[31;1mIn accept.\033[0m");
}