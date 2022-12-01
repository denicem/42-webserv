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

void	Config::splitSettingValues(string& values, vector<string>& split)
{
	stringstream stream(values);
	string buffer;

	while (getline(stream, buffer, ','))
	{
		split.push_back(buffer);
	}
}

void	Config::setSetting(const string& setting, ServerConfig* server, int line_num)
{
	if (setting == "server_names")
		splitSettingValues(_line, server->server_names);
	else if (setting == "ports")
	{
		vector<string>	str_ports;
		splitSettingValues(_line, str_ports);
		
	}
	else if (setting == "max_client_body_size")
}

void	Config::parseConfigFile(void)
{
	ServerConfig*					curr_server = NULL;
	RouteConfig*					curr_route = NULL;
	map<string, Setting>::iterator	curr_setting;
	size_t							colon_pos;

	for (int line_num = 1; getline(this->_config_stream, this->_line); line_num++)
	{
		//cout << ' ' << WAITING_ICON.substr((line_num % 12) * 4, 4) << "\n";
		if (all_of(_line.begin(), _line.end(), static_cast<int(*)(int)>(&std::isspace)))
			continue;
		switch (_line.back())
		{
			case '{':
				_line.erase(_line.end() - 1); removeWhitespace(_line);
				if (lineHasBrackets(_line) || _file_location >= ROUTE)
					configError(line_num, "Too many open brackets");
				else if (_file_location == BASE)
				{
					_server_configs.push_back(ServerConfig());
					curr_server = &_server_configs.back();
					resetSettings(this->_server_settings);
					_file_location = SERVER;
				}
				else if (_file_location == SERVER)
				{
					if (_line == "error_pages")
					{
						if (this->_server_settings["error_pages"].setting_is_set)
							configError(line_num, "Two error_pages in one server not allowed");
						_file_location = ERROR_PAGES;
					}
					else if (*_line.begin() == '/')
					{
						if (curr_server->routes.insert(map<string, RouteConfig>::value_type(_line, RouteConfig())).second == false)
							configError(line_num, "Two routes of the same name shouldn't be in the same server");
						curr_route = &curr_server->routes[_line];
						resetSettings(this->_route_settings);
						_file_location = ROUTE;
					}
					else
						configError(line_num, "Unknown block inside server");
				}
				break;
			case '}':
				_line.erase(_line.end() - 1);
				if (!all_of(_line.begin(), _line.end(), static_cast<int(*)(int)>(&std::isspace)))
					configError(line_num, "Closing bracket needs to be alone in line");
				switch(_file_location)
				{
					case BASE:
						configError(line_num, "Too many closing brackets");
					case SERVER:
						if (mandatorySettingsAreSet(_server_settings) == false)
							configError(line_num, "All mandatory settings for this server were not set");
						_file_location = BASE;
					case ROUTE:
						if (mandatorySettingsAreSet(_route_settings) == false)
							configError(line_num, "All mandatory settings for this route were not set");
						_file_location = SERVER;
					case ERROR_PAGES:
						_file_location = SERVER;
				}
				break;
			default:
				colon_pos = _line.find(':');
				removeWhitespace(_line);
				if (lineHasBrackets(_line))
					configError(line_num, "Bracket needs to be at the end of a line");
				else if (colon_pos == string::npos)
					configError(line_num, "No colon in setting");
				switch (_file_location)
				{
					case BASE:
						configError(line_num, "why is there a setting outside of a block lmao");
					case SERVER:
						curr_setting = _server_settings.find(_line.substr(0, colon_pos));
						_line.erase(0, colon_pos+1); /// <--------- here i am
						if (curr_setting == _server_settings.end())
							configError(line_num, "Unknown server setting");
						else if (curr_setting->second.setting_is_set)
							configError(line_num, "You are trying to set the same setting twice");
						else if (*_line.rbegin() == ',')
							configError(line_num, "You cannot have a comma at the end of a setiting. Where's the last value???");
						this->setSetting(curr_setting->first, curr_server, line_num);
						curr_setting->second.setting_is_set = true;
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