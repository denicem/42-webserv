/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:36:32 by shaas             #+#    #+#             */
/*   Updated: 2022/11/29 02:03:18 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

// #include <string>
// #include <fstream>
// #include <iostream>
// #include <vector>
// #include <map>
// #include <algorithm>

// #include "Webserv.hpp"

// struct Setting
// {

// 	bool	mandatory;
// 	bool	multiple_values_allowed;

// 	Setting(bool mandatory, bool multiple_values_allowed)
// 	{
// 		this->mandatory = mandatory;
// 		this->multiple_values_allowed = multiple_values_allowed;
// 	}
// 	Setting() {}
// };

// enum file_location {
// 	BASE,
// 	SERVER,
// 	ROUTE,
// 	ERROR_PAGES
// };

// enum http_methods {
// 	GET,
// 	DELETE,
// 	POST
// };

// enum cgi_extensions {
// 	dotDMS,
// 	dotPY,
// 	dotC
// };

// struct RouteConfig
// {
// 	RouteConfig*	http_redirect; // can be NULL, then no redirect
// 	vector<int>		http_methods; // will use values of enum "http_methods"
// 	string			root;
	string			alias;
// 	bool			directory_listing;
// 	string			default_file; // if empty string, no default file
// 	vector<int>		cgi_extensions; // will use values of enum "cgi_extension"
// 	string			upload_directory;
// };

// struct ServerConfig
// {
// 	vector<string>				server_names;
// 	vector<int>					ports;
// 	int							max_client_body_size; //if -1, allow infinite size
// 	map<int, string>			error_pages; // "int" is error code, "string" is the corresponding page
// 	map<string, RouteConfig>	routes; // "string" element of map is name of route
// };

// class Config
// {
// 	private:
// 		/*-CONSTANT VARIABLES FOR THE FORMATTING RULES-*/
// 		map<string, Setting>	server_settings;
// 		map<string, Setting>	route_settings;
// 		/*---------------------------------------------*/

// 		vector<ServerConfig> _server_configs;
	
// 		ifstream	_config_stream;
// 		string		_line;
// 		int			_file_location;

// 		void	parseConfigFile(void);

// 		static bool	lineHasBrackets(string& line);
// 		static void	configError(int line_num, string error_msg);
// 		static void	removeWhitespace(std::string& string);
	
// 	public:
// 		Config(string filePath);
// 		~Config();
	
// 		static string	getFilePath(int argc, char* argv[]);

// 		struct ConfigException: public exception
// 		{
// 			const char* what() const throw() {
// 				return ("\033[31;1mError occured during config parsing 🛠️\033[0m");
// 			}
// 		};
// };

#endif