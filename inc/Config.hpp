/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:36:32 by shaas             #+#    #+#             */
/*   Updated: 2022/12/06 01:10:06 by shaas            ###   ########.fr       */
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
#include <limits.h>
#include <unistd.h>

#include "webserv.hpp"

struct HttpRedirect
{
	string	route;
	string	redirect;

	HttpRedirect(string route, string redirect): route(route), redirect(redirect) {}
};

struct Setting
{
	bool	mandatory;
	bool	setting_is_set;

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
	RouteConfig*	http_redirect; // can be NULL, then no redirect. need to be concious that it can redirect to another route with a redirection
	vector<int>		http_methods; // will use values of enum "http_methods". will always be at least one
	string			root; // one of root or alias will be empty.
	string			alias;
	bool			directory_listing;
	string			default_file; // if empty string, no default file // relative to location root
	vector<int>		cgi_extensions; // will use values of enum "cgi_extension". can be empty, then no cgi allowed
	string			upload_directory; // relative to server root, not location root

	RouteConfig(): http_redirect(NULL), directory_listing(false) {}
	RouteConfig(const RouteConfig& orig);
};

struct ServerConfig
{
	vector<string>				server_names; // can be empty, then no server names
	vector<int>					ports; // always at least one port
	int							max_client_body_size; //if 0, allow infinite size
	map<int, string>			error_pages; // "int" is error code, "string" is the corresponding page
	map<string, RouteConfig>	routes; // "string" element of map is name of route

	ServerConfig(): max_client_body_size(0) {}
	ServerConfig(const ServerConfig& orig);
};

class Config
{
	private:
		/*-THE FINAL RESULT-*/
		vector<ServerConfig> _config;

		/*-CONSTANT VARIABLES FOR THE FORMATTING RULES-*/
		map<string, Setting>	_server_settings;
		map<string, Setting>	_route_settings;
		/*---------------------------------------------*/

		/*-THESE ARE FOR THE CONFIG PARSING-*/
		ifstream		_config_stream;
		string			_line;
		int				_line_num;
		int				_file_location;
		ServerConfig*	_curr_server;
		RouteConfig*	_curr_route;
		string			_curr_route_name;
		vector<HttpRedirect>	_http_redirects;
		/*-----------------------------------*/

		void	parseConfigFile(void);
		void	handleSetting(size_t colon_pos);
		void	setSetting(const string& setting, ServerConfig* server);
		void	setSetting(const string& setting, RouteConfig* route);
		void	assignHttpRedirects(void);

		static bool	lineHasBrackets(string& line);
		static void	configError(int line_num, string error_msg);
		static void	removeWhitespace(std::string& string);
		static void	resetSettings(map<string, Setting>& settings);
		static bool	mandatorySettingsAreSet(map<string, Setting>& settings);
		static void	splitSettingValues(string& str, vector<string>& split, int line_num);
		static int	stringToInt(string& string, int lower_limit, int upper_limit, int line_num);
		static bool	settingHasMultipleValues(string& line);
		static void	setDefaultValues(map<string, Setting>& route_settings, RouteConfig* route);

	public:
		Config(string filePath);
		~Config() {}
	
		static string	getFilePath(int argc, char* argv[]);
		static void		printServerConfig(const vector<ServerConfig>& config);

		void						extractConfigData(vector<ServerConfig>& buffer) const; // try this function!
		const vector<ServerConfig>&	getConfigData(void) { return (_config); }

		struct ConfigException: public exception
		{
			const char* what() const throw() {
				return ("\033[31;1mError occured during config parsing 🛠️\033[0m");
			}
		};
};

#endif