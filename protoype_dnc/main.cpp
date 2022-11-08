/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:41:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/08 20:33:41 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"
#include <iostream>
#include <unistd.h>

int main()
{
	Socket socket;
	socket.waitForConnect();
	return (0);
}