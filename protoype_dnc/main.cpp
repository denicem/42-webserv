/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:41:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/08 20:02:13 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"
#include <iostream>
#include <unistd.h>

int main()
{
	Socket socket;

	char buffer[1024] = {0};
	int valread = read(socket.getNewSocket(), buffer, 1024);
	std::cout << buffer << std::endl;
	if (valread < 0)
		std::cout << "No bytes are there to read.\n";
	std::string hello = "Hello from the other siiiiide.";
	write(socket.getNewSocket(), hello.c_str(), hello.length());
	close(socket.getNewSocket());
}