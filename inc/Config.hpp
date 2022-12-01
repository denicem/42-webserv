/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:36:32 by shaas             #+#    #+#             */
/*   Updated: 2022/12/01 22:15:11 by shaas            ###   ########.fr       */
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
#include <sstream>
#include <limits>

#include "webserv.hpp"

struct Setting
{
	const bool	mandatory;
	bool		setting_is_set;

	Setting(bool mandatory): mandatory(mandatory)
	{
		this->setting_is_set = false;
	}
	Setting() {}
};

enum file_location {
	BASE,
	SERVER,
	ROUTE,
	ERROR_PAGES
};

enum http_methods {
	GET,
	DELETE,
	POST
};

enum cgi_extensions {
	dotDMS,
	dotPY,
	dotC
};

struct RouteConfig
{
	RouteConfig*	http_redirect; // can be NULL, then no redirect
	vector<int>		http_methods; // will use values of enum "http_methods"
	string			root;
	string			alias;
	bool			directory_listing;
	string			default_file; // if empty string, no default file
	vector<int>		cgi_extensions; // will use values of enum "cgi_extension"
	string			upload_directory;
};

struct ServerConfig
{
	vector<string>				server_names;
	vector<int>					ports;
	int							max_client_body_size; //if 0, allow infinite size
	map<int, string>			error_pages; // "int" is error code, "string" is the corresponding page
	map<string, RouteConfig>	routes; // "string" element of map is name of route
};

class Config
{
	private:
		vector<ServerConfig> _server_configs;

		/*-CONSTANT VARIABLES FOR THE FORMATTING RULES-*/
		map<string, Setting>	_server_settings;
		map<string, Setting>	_route_settings;
		/*---------------------------------------------*/

		ifstream	_config_stream;
		string		_line;
		id_t		_line_num;
		int			_file_location;

		void	parseConfigFile(void);
		void	handleSetting(size_t colon_pos);
		void	setSetting(const string& setting, ServerConfig* server);
		void	setSetting(const string& setting, RouteConfig* route);

		static bool	lineHasBrackets(string& line);
		static void	configError(int line_num, string error_msg);
		static void	removeWhitespace(std::string& string);
		static void	resetSettings(map<string, Setting>& settings);
		static bool	mandatorySettingsAreSet(map<string, Setting>& settings);
		static void	splitSettingValues(string& str, vector<string>& split, int line_num);
		static int	stringToInt(string& string, int lower_limit, int upper_limit, int line_num);

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