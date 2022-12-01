/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   Config.cpp	 :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: shaas <shaas@student.42heilbronn.de>	   +#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2022/11/17 17:40:22 by shaas	 #+#	#+#	 */
/*   Updated: 2022/12/01 00:37:11 by shaas	###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#include "Config.hpp"

/*
** ----------------------- PRIVATE METHODS -----------------------
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
	remove_if(str.begin(), str.end(), static_cast<int(*)(int)>(&std::isspace));
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

	while (getline(stream, buffer, ','))
	{
		if (buffer.empty())
			configError(line_num, "Cannot have empty setting value");
		split.push_back(buffer);
	}
}

int	Config::stringToInt(string& str, int lower_limit, int upper_limit, int line_num)
{
	stringstream	stream(str);
	int				integer;

	stream >> integer;
	if (integer < lower_limit || integer > upper_limit)
			configError(line_num, "The number you are trying to set is outside of the setting's limits");
	return (integer);
}

void	Config::setSetting(const string& setting, ServerConfig* server)
{
	if (setting == "server_names")
		splitSettingValues(_line, server->server_names,  _line_num);
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
		if (_line.find(',') != string::npos)
			configError(_line_num, "max_client_body_size can only have one value");
		if (_line.find_first_not_of("0123456789") != string::npos)
				configError(_line_num, "Max client body size is not a positive integer, which it should be");
		server->max_client_body_size = stringToInt(_line, 1, INT_MAX, _line_num);
	}
}

void	Config::setSetting(const string& setting, RouteConfig* route)
{
	// need to fill with the settings
}

void	Config::handleSetting(size_t colon_pos)
{
	switch (_file_location)
	{
		case SERVER:
			map<string, Setting>&	settings

	}
	map<string, Setting>::iterator	curr_setting;

	curr_setting = _server_settings.find(_line.substr(0, colon_pos));
	_line.erase(0, colon_pos+1);
	if (curr_setting == _server_settings.end())
		configError(_line_num, "Unknown server setting");
	else if (curr_setting->second.setting_is_set)
		configError(_line_num, "You are trying to set the same setting twice");
	this->setSetting(curr_setting->first, curr_server);
	curr_setting->second.setting_is_set = true;
}

void	Config::parseConfigFile(void)
{
	ServerConfig*					curr_server = NULL;
	RouteConfig*					curr_route = NULL;
	size_t							colon_pos;
	map<string, Setting>::iterator	curr_setting;

	for (_line_num = 1; getline(this->_config_stream, this->_line); _line_num++)
	{
		//cout << ' ' << WAITING_ICON.substr((_line_num % 12) * 4, 4) << "\n";
		if (_line.find('#') != string::npos)
			_line.erase(_line.find('#'));
		removeWhitespace(_line);
		if (_line.empty())
			continue;
		switch (_line.back())
		{
			case '{':
				_line.erase(_line.end() - 1);
				if (lineHasBrackets(_line) || _file_location >= ROUTE)
					configError(_line_num, "Too many open brackets");
				switch (_file_location)
				{
					case BASE:
						_server_configs.push_back(ServerConfig());
						curr_server = &_server_configs.back();
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
							if (curr_server->routes.insert(map<string, RouteConfig>::value_type(_line, RouteConfig())).second == false)
								configError(_line_num, "Two routes of the same name shouldn't be in the same server");
							curr_route = &curr_server->routes[_line];
							resetSettings(this->_route_settings);
							_file_location = ROUTE;
						}
						else
							configError(_line_num, "Unknown block inside server");
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
					case SERVER:
						if (mandatorySettingsAreSet(_server_settings) == false)
							configError(_line_num, "All mandatory settings for this server were not set");
						_file_location = BASE;
					case ROUTE:
						if (mandatorySettingsAreSet(_route_settings) == false)
							configError(_line_num, "All mandatory settings for this route were not set");
						_file_location = SERVER;
					case ERROR_PAGES:
						_file_location = SERVER;
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
						//this->handleSetting(colon_pos);
						curr_setting = _server_settings.find(_line.substr(0, colon_pos));
						_line.erase(0, colon_pos+1);
						if (curr_setting == _server_settings.end())
							configError(_line_num, "Unknown server setting");
						else if (curr_setting->second.setting_is_set)
							configError(_line_num, "You are trying to set the same setting twice");
						this->setSetting(curr_setting->first, curr_server);
						curr_setting->second.setting_is_set = true;
						break;
					case ROUTE:
						curr_setting = _route_settings.find(_line.substr(0, colon_pos));
						_line.erase(0, colon_pos+1);
						if (curr_setting == _route_settings.end())
							configError(_line_num, "Unknown route setting");
						else if (curr_setting->second.setting_is_set)
							configError(_line_num, "You are trying to set the same setting twice");
						this->setSetting(curr_setting->first, curr_route);
						curr_setting->second.setting_is_set = true;
						break;
					case ERROR_PAGES:
						curr_server->error_pages
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
				break;
		}
	}
	if (this->_config_stream.bad()) {
		cerr << "I/O Error\n";
		throw ConfigException();
	}
	// do stuff
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

Config::Config(string filePath): _config_stream(filePath), _file_location(BASE)
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

Config::~Config() {}

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

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/


/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
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