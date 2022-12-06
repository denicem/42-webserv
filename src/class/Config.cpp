/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:36:32 by shaas             #+#    #+#             */
/*   Updated: 2022/12/06 17:08:20 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

/*
** ----------------------- PRIVATE STATIC METHODS -----------------------
*/

bool	Config::lineHasBrackets(string& line)
{
	if (line.find('{') != string::npos || line.find('}') != string::npos)
		return true;
	return false;
}

void	Config::configError(int line_num, string error_msg)
{
	cerr << "\nLine " << line_num << ": " << error_msg << '\n';
	throw ConfigException();
}

inline void	Config::removeWhitespace(std::string& str)
{
	str.erase(remove_if(str.begin(), str.end(), static_cast<int(*)(int)>(&std::isspace)), str.end());
}

void	Config::resetSettings(map<string, Setting>& settings)
{
	for (map<string, Setting>::iterator i = settings.begin(); i != settings.end(); i++)
	{
		i->second.setting_is_set = false;
	}
}

bool	Config::mandatorySettingsAreSet(map<string, Setting>& settings)
{
	for(map<string, Setting>::iterator i = settings.begin(); i != settings.end(); i++)
	{
		if (i->second.mandatory)
		{
			if (i->second.setting_is_set == false)
				return false;
		}
	}
	return true;
}

void	Config::splitSettingValues(string& values, vector<string>& split, int line_num)
{
	stringstream stream(values);
	string buffer;

	if (values.empty())
		return ;
	while (getline(stream, buffer, ','))
	{
		if (buffer.empty())
			configError(line_num, "Cannot have empty setting value");
		split.push_back(buffer);
	}
}

int	Config::stringToInt(string& str, int lower_limit, int upper_limit, int line_num)
{
	if (str.empty())
		configError(line_num, "Cannot have empty setting value");
	stringstream	stream(str);
	int				integer;

	stream >> integer;
	if (integer < lower_limit || integer > upper_limit)
			configError(line_num, "The number you are trying to set is outside of the setting's limits");
	return (integer);
}

bool	Config::settingHasMultipleValues(string& line)
{
	if (line.find(',') == string::npos)
		return false;
	return true;
}

void	Config::setDefaultValues(map<string, Setting>& route_settings, RouteConfig* route)
{
	if (route_settings["http_methods"].setting_is_set == false)
	{
		route->http_methods.push_back(GET);
		route->http_methods.push_back(DELETE);
		route->http_methods.push_back(POST);
	}
	if (route_settings["cgi_extensions"].setting_is_set == false)
	{
		route->cgi_extensions.push_back(dotDMS);
		route->cgi_extensions.push_back(dotPY);
		route->cgi_extensions.push_back(dotC);
	}
}

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void	Config::setSetting(const string& setting, ServerConfig* server)
{
	if (setting == "server_names")
	{
		if (_line.empty())
			configError(_line_num, "Need at least one server_name");
		splitSettingValues(_line, server->server_names, _line_num);
	}
	else if (setting == "ports")
	{
		if (_line.empty())
			configError(_line_num, "Need at least one port");
		vector<string>	str_ports;
		splitSettingValues(_line, str_ports, _line_num);
		for (vector<string>::iterator i = str_ports.begin(); i != str_ports.end(); i++)
		{
			if (i->find_first_not_of("0123456789") != string::npos)
				configError(_line_num, "Port is not a positive integer, which it should be");
			server->ports.push_back(stringToInt(*i, 0, USHRT_MAX, _line_num));
		}
	}
	else if (setting == "max_client_body_size")
	{
		if (settingHasMultipleValues(_line))
			configError(_line_num, "max_client_body_size can only have one value");
		if (_line.find_first_not_of("0123456789") != string::npos)
				configError(_line_num, "Max client body size is not a positive integer, which it should be");
		server->max_client_body_size = stringToInt(_line, 1, INT_MAX, _line_num);
	}
}

void	Config::setSetting(const string& setting, RouteConfig* route)
{
	if (_line.empty())
			configError(_line_num, "Cannot have empty setting value");
	if (setting == "http_redirect")
	{
		if (settingHasMultipleValues(_line))
			configError(_line_num, "http_redirect can only have one value");
		_http_redirects.push_back(HttpRedirect(_curr_route_name, _line));
	}
	else if (setting == "http_methods")
	{
		vector<string>	str_methods;
		splitSettingValues(_line, str_methods, _line_num);
		for (vector<string>::iterator i = str_methods.begin(); i != str_methods.end(); i++)
		{
			if (*i == "GET")
				route->http_methods.push_back(GET);
			else if (*i == "DELETE")
				route->http_methods.push_back(DELETE);
			else if (*i == "POST")
				route->http_methods.push_back(POST);
			else
				configError(_line_num, "Unknown http method");
		}
	}
	else if (setting == "root")
	{
		if (settingHasMultipleValues(_line))
			configError(_line_num, "root can only have one value");
		if (route->alias.empty() == false)
			configError(_line_num, "Can only either set root or alias, not both");
		if (access(_line.c_str(), F_OK) == -1)
			configError(_line_num, "Cannot access root directory");
		route->root = _line;
		
	}
	else if (setting == "alias")
	{
		if (settingHasMultipleValues(_line))
			configError(_line_num, "alias can only have one value");
		if (route->root.empty() == false)
			configError(_line_num, "Can only either set root or alias, not both");
		route->alias = _line;
	}
	else if (setting == "default_file")
	{
		if (settingHasMultipleValues(_line))
			configError(_line_num, "default_file can only have one value");
		route->default_file = _line;
	}
	else if (setting == "upload_directory")
	{
		if (settingHasMultipleValues(_line))
			configError(_line_num, "upload_directory can only have one value");
		if (access(_line.c_str(), F_OK) == -1)
			configError(_line_num, "Cannot access upload directory");
		route->upload_directory = _line;
	}
	else if (setting == "directory_listing")
	{
		if(_line == "on")
			route->directory_listing = true;
		else if(_line == "off")
			route->directory_listing = false;
		else
			configError(_line_num, "Invalid value for directory listing, must be either on or off");
	}
	else if (setting == "cgi_extensions")
	{
		vector<string>	str_extensions;
		splitSettingValues(_line, str_extensions, _line_num);
		for (vector<string>::iterator i = str_extensions.begin(); i != str_extensions.end(); i++)
		{
			if (*i == ".dms")
				route->cgi_extensions.push_back(dotDMS);
			else if (*i == ".py")
				route->cgi_extensions.push_back(dotPY);
			else if (*i == ".c")
				route->cgi_extensions.push_back(dotC);
			else
				configError(_line_num, "Unknown cgi extension");
		}
	}
}

void	Config::handleSetting(size_t colon_pos)
{
	map<string, Setting>* settings;

	switch (_file_location)
	{
		case SERVER:
			settings = &_server_settings;
			break;
		case ROUTE:
			settings = &_route_settings;
			break;
	}

	map<string, Setting>::iterator	curr_setting;
	curr_setting = settings->find(_line.substr(0, colon_pos));
	_line.erase(0, colon_pos+1);
	if (curr_setting == settings->end())
		configError(_line_num, "Unknown setting for this block");
	else if (curr_setting->second.setting_is_set)
		configError(_line_num, "You are trying to set the same setting twice");

	switch (_file_location)
	{
		case SERVER:
			this->setSetting(curr_setting->first, _curr_server);
			break;
		case ROUTE:
			this->setSetting(curr_setting->first, _curr_route);
			break;
	}

	curr_setting->second.setting_is_set = true;
}

void	Config::assignHttpRedirects(void)
{
	std::map<std::string, RouteConfig>::iterator	redirect;

	for (vector<HttpRedirect>::iterator i = _http_redirects.begin(); i != _http_redirects.end(); i++)
	{
		redirect = _curr_server->routes.find(i->redirect);
		if (redirect == _curr_server->routes.end())
			configError(_line_num, "Http redirect to nonexistent route in this server");
		_curr_server->routes.find(i->route)->second.http_redirect = &redirect->second;
	}
	_http_redirects.clear();
}

void	Config::parseConfigFile(void)
{
	size_t	colon_pos;

	//default values!
	for (_line_num = 1; getline(this->_config_stream, this->_line); _line_num++)
	{
		//cout << ' ' << WAITING_ICON.substr((_line_num % 12) * 4, 4) << "\n";
		if (_line.find('#') != string::npos)
			_line.erase(_line.find('#'));
		removeWhitespace(_line);
		if (_line.empty())
			continue;
		switch (*(_line.end()-1))
		{
			case '{':
				_line.erase(_line.end()-1, _line.end());
				if (lineHasBrackets(_line) || _file_location >= ROUTE)
					configError(_line_num, "Too many open brackets");
				switch (_file_location)
				{
					case BASE:
						_config.push_back(ServerConfig());
						_curr_server = &_config.back();
						resetSettings(this->_server_settings);
						_file_location = SERVER;
						break;
					case SERVER:
						if (_line == "error_pages")
						{
							if (this->_server_settings["error_pages"].setting_is_set)
								configError(_line_num, "Two error_pages in one server not allowed");
							_file_location = ERROR_PAGES;
						}
						else if (*_line.begin() == '/')
						{
							if (_curr_server->routes.insert(map<string, RouteConfig>::value_type(_line, RouteConfig())).second == false)
								configError(_line_num, "Two routes of the same name shouldn't be in the same server");
							_curr_route = &_curr_server->routes[_line];
							_curr_route_name = _line;
							resetSettings(this->_route_settings);
							_file_location = ROUTE;
						}
						else
						{
							configError(_line_num, "Unknown block inside server");
						}
						break;
				}
				break;
			case '}':
				_line.erase(_line.end() - 1);
				if (_line.empty() == false)
					configError(_line_num, "Closing bracket needs to be alone in line");
				switch(_file_location)
				{
					case BASE:
						configError(_line_num, "Too many closing brackets");
						break;
					case SERVER:
						this->assignHttpRedirects();
						if (mandatorySettingsAreSet(_server_settings) == false)
							configError(_line_num, "All mandatory settings for this server were not set");
						_file_location = BASE;
						break;
					case ROUTE:
						if (mandatorySettingsAreSet(_route_settings) == false)
							configError(_line_num, "All mandatory settings for this route were not set");
						setDefaultValues(_route_settings, _curr_route);
						_file_location = SERVER;
						break;
					case ERROR_PAGES:
						_file_location = SERVER;
						break;
				}
				break;
			default:
				colon_pos = _line.find(':');
				if (colon_pos == string::npos)
					configError(_line_num, "No colon in setting");
				else if (lineHasBrackets(_line))
					configError(_line_num, "Bracket needs to be at the end of a line");
				else if (*_line.rbegin() == ',')
					configError(_line_num, "You cannot have a comma at the end of a setting. Where's the last value???");
				switch (_file_location)
				{
					case BASE:
						configError(_line_num, "why is there a setting outside of a block lmao");
						break;
					case SERVER:
						this->handleSetting(colon_pos);
						break;
					case ROUTE:
						this->handleSetting(colon_pos);
						break;
					case ERROR_PAGES:
						if (_line.find(',') != string::npos)
							configError(_line_num, "Can only have one error page per error code");
						if (_line.substr(0, colon_pos).find_first_not_of("0123456789") != string::npos)
							configError(_line_num, "Error code is not a positive integer, which it should be");
						std::string	error_code_str(_line.substr(0, colon_pos));
						int error_code = stringToInt(error_code_str, 100, 599, _line_num);
						if (access(_line.erase(0, colon_pos+1).c_str(), R_OK) == -1)
							configError(_line_num, "Requested error file does not grant read permissions (or doesn't even exist)");
						if (_curr_server->error_pages.insert(map<int, string>::value_type(error_code, _line)).second == false)
							configError(_line_num, "Cannot have multiple pages for one error code");
						break;
				}
				break;
		}
	}
	if (this->_config_stream.bad()) {
		cerr << "I/O Error\n";
		throw ConfigException();
	}
	_config_stream.close();
	_http_redirects.clear();
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

Config::Config(string filePath): _config_stream(filePath.c_str()), _file_location(BASE)
{
	this->_server_settings["server_names"] = Setting(false);
	this->_server_settings["ports"] = Setting(true);
	this->_server_settings["max_client_body_size"] = Setting(false);
	this->_server_settings["error_pages"] = Setting(false);

	this->_route_settings["http_redirect"] = Setting(false);
	this->_route_settings["http_methods"] = Setting(false);
	this->_route_settings["root"] = Setting(false);
	this->_route_settings["alias"] = Setting(false);
	this->_route_settings["default_file"] = Setting(false);
	this->_route_settings["upload_directory"] = Setting(false);
	this->_route_settings["directory_listing"] = Setting(false);
	this->_route_settings["cgi_extensions"] = Setting(false);

	if (this->_config_stream.is_open() == false) {
		cerr << "Config file couldn't be opened\n";
		throw ConfigException();
	}
	this->parseConfigFile();
}

ServerConfig::ServerConfig(const ServerConfig& orig): server_names(orig.server_names), ports(orig.ports),
		max_client_body_size(orig.max_client_body_size), error_pages(orig.error_pages), routes(orig.routes) { }

RouteConfig::RouteConfig(const RouteConfig& orig): http_methods(orig.http_methods),
		root(orig.root), alias(orig.alias), directory_listing(orig.directory_listing), default_file(orig.default_file),
		upload_directory(orig.upload_directory), cgi_extensions(orig.cgi_extensions) {}

/*
** ----------------------- STATIC METHODS -----------------------
*/

string Config::getFilePath(int argc, char* argv[])
{
	switch (argc)
	{
		case 1:
			return DEFAULT_CONFIG_FILE_PATH;
		case 2:
			return argv[1];
		default:
			cerr << "Why so many arguments?\n";
			throw ConfigException();
	}
}

void	Config::printServerConfig(const vector<ServerConfig>& config)
{
	cout << '\n' << BLUE_BG << "ALL THE SERVER BLOCKS" << RESET << "\n\n";
	for (vector<ServerConfig>::const_iterator server = config.begin(); server != config.end(); server++)
	{
		cout << BLUE_BG << "--------NEW SERVER---------" << RESET << "\n\n";
		cout << BLUE << "Server Names:	" << RESET;
		for (vector<string>::const_iterator name = server->server_names.begin(); name != server->server_names.end(); name++) {
			cout << *name;
			if (name != server->server_names.end()-1)
				cout << " | ";
		}
		cout << "\n\n" << BLUE << "Ports:	" << RESET;
		for (vector<int>::const_iterator port = server->ports.begin(); port != server->ports.end(); port++) {
			cout << *port;
			if (port != server->ports.end()-1)
				cout << " | ";
		}
		cout << "\n\n" << BLUE << "Max client body size: " << RESET << server->max_client_body_size << "\n\n";
		cout << BLUE_BG << "Error Pages" << RESET << '\n';
		for (map<int, string>::const_iterator page = server->error_pages.begin(); page != server->error_pages.end(); page++) {
			cout << '	' << BLUE << page->first << ": " << RESET << page->second << '\n';
		}
		cout << "\n" << MAGENTA_BG << "---ROUTES---" << RESET << "\n\n";
		for (map<string, RouteConfig>::const_iterator route = server->routes.begin(); route != server->routes.end(); route++) {
			cout << "	" << MAGENTA_BG << route->first << RESET << '\n';
			cout << '	' << MAGENTA << "Http redirect: " << RESET << route->second.http_redirect << '\n';
			cout << MAGENTA << "	Http methods:	" << RESET;
			for (vector<int>::const_iterator method = route->second.http_methods.begin(); method != route->second.http_methods.end(); method++) {
				cout << *method;
				if (method != route->second.http_methods.end()-1)
					cout << " | ";
				else
					cout << '\n';
			}
			cout << '	' << MAGENTA << "Root: " << RESET << route->second.root << '\n';
			cout << '	' << MAGENTA << "Alias: " << RESET << route->second.alias << '\n';
			cout << '	' << MAGENTA << "Directory listing: " << RESET << route->second.directory_listing << '\n';
			cout << '	' << MAGENTA << "Default file: " << RESET << route->second.default_file << '\n';
			cout << '	' << MAGENTA << "Upload directory: " << RESET << route->second.upload_directory << '\n';
			cout << MAGENTA << "	CGI Extensions:	" << RESET;
			for (vector<int>::const_iterator cgi = route->second.cgi_extensions.begin(); cgi != route->second.cgi_extensions.end(); cgi++) {
				cout << *cgi;
				if (cgi != route->second.cgi_extensions.end()-1)
					cout << " | ";
				else
					cout << '\n';
			}
			cout << '\n';
		}
	}
}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- CLASS METHODS -----------------------
*/

void	Config::extractConfigData(vector<ServerConfig>& buffer) const
{
	for (vector<ServerConfig>::const_iterator i = _config.begin(); i != _config.end(); i++)
	{
		buffer.push_back(ServerConfig(*i));
	}
}
