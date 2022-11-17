/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:36:59 by shaas             #+#    #+#             */
/*   Updated: 2022/11/17 17:56:42 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <unistd.h>

#include "TCPPoll.hpp"

/* COLOURS */

# define RESET	"\e[0m"

/*--- MODES ---*/

# define BOLD		"\e[1m"
# define ITALIC		"\e[3m"
# define UNDERLINED	"\e[4m"

/*-- COLOURED FONT ---*/

# define RED			"\e[31m"
# define GREEN			"\e[32m"
# define YELLOW			"\e[33m"
# define BLUE			"\e[34m"
# define MAGENTA		"\e[35m"
# define CYAN			"\e[36m"
# define LIGHTGRAY		"\e[37m"
# define DARKGRAY		"\e[90m"
# define LIGHTRED		"\e[91m"
# define LIGHTGREEN		"\e[92m"
# define LIGHTYELLOW	"\e[93m"
# define LIGHTBLUE		"\e[94m"
# define LIGHTMAGENTA	"\e[95m"
# define LIGHTCYAN		"\e[96m"

/*--- COLOURED BACKGROUND ---*/

# define RED_BG				"\e[41m"
# define GREEN_BG			"\e[42m"
# define YELLOW_BG			"\e[43m"
# define BLUE_BG			"\e[44m"
# define MAGENTA_BG			"\e[45m"
# define CYAN_BG			"\e[46m"
# define LIGHTGRAY_BG		"\e[47m"
# define DARKGRAY_BG		"\e[100m"
# define LIGHTRED_BG		"\e[101m"
# define LIGHTGREEN_BG		"\e[102m"
# define LIGHTYELLOW_BG		"\e[103m"
# define LIGHTBLUE_BG		"\e[104m"
# define LIGHTMAGENTA_BG	"\e[105m"
# define LIGHTCYAN_BG		"\e[106m"

class webserv{
	
	private:
		std::vector<Server>serverList;
		
	public:
		void addServer(std::vector<int>, std::string);
		
	//+++++++++++++++++++++Helper Function++++++++++++++++++++
		std::string getServerAtIndexName(int);
		void setServerAtIndexName(int);
		
		int getPortAtIndex(int);
		void setPortAtIndex(int);

		Server getServerFromList(int);
		
		
};