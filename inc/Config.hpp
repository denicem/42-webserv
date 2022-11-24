/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:36:32 by shaas             #+#    #+#             */
/*   Updated: 2022/11/24 00:30:11 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "webserv.hpp"

struct Setting
{

	bool	mandatory;
	bool	multiple_values_allowed;

	Setting(bool mandatory, bool multiple_values_allowed)
	{
		this->mandatory = mandatory;
		this->multiple_values_allowed = multiple_values_allowed;
	}
	Setting() {}
};

enum file_location {
	BASE,
	SERVER,
	ROUTE_OR_ERROR_PAGES
};

struct RouteConfig
{
	
};

struct ServerConfig
{
	map<string, RouteConfig>	routes;
};

class Config
{
	private:
		/*-CONSTANT VARIABLES FOR THE FORMATTING RULES-*/
		map<string, Setting>	server_settings;
		map<string, Setting>	route_settings;
		/*---------------------------------------------*/

		vector<ServerConfig> _server_configs;
	
		ifstream	_config_stream;
		string		_line;
		int			_file_location;

		void	parseConfigFile(void);

		static bool	lineHasBrackets(string& line);
		static void	configError(int line_num, string error_msg);
	
	
	public:
		Config(string filePath);
		~Config();
	
		static string	getFilePath(int argc, char* argv[]);

		struct ConfigException: public exception
		{
			const char* what() const throw() {
				return ("\033[31;1mError occured during config parsing 🛠️\033[0m");
			}
		};
};

#endif