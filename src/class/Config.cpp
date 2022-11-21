/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:40:22 by shaas             #+#    #+#             */
/*   Updated: 2022/11/21 23:47:21 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void Config::getFilePath(int argc, char* argv[])
{
	switch (argc)
	{
		case 1:
			this->_config_file_path = DEFAULT_CONFIG_FILE_PATH;
			break;
		case 2:
			this->_config_file_path = argv[1];
			break;
		default:
			std::cerr << "Why so many arguments?\n";
			throw ConfigException();
	}
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

Config::Config(int argc, char* argv[])
{
	this->getFilePath(argc, argv);
	// std::ifstream	fileStream(fileName);
	// if (fileStream.is_open() == false) {
	// 	std::cerr	<< "\e[31mError: " << fileName
	// 				<< " couldn't be opened\e[0m" << std::endl;
	// 	return (true);
	// }
}

Config::~Config() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/


/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

/*
** ----------------------- METHODS -----------------------
*/

/*
** ----------------------- CLASS ATTRIBUTES -----------------------
*/

/*
** ----------------------- CLASS METHODS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/