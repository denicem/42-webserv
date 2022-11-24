/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:40:22 by shaas             #+#    #+#             */
/*   Updated: 2022/11/24 01:01:09 by shaas            ###   ########.fr       */
/*                                                                            */
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

void	Config::parseConfigFile(void)
{
	for (int line_num = 1; getline(this->_config_stream, this->_line); line_num++)
	{
		//cout << ' ' << WAITING_ICON.substr((line_num % 12) * 4, 4) << "\n";
		if (all_of(_line.begin(), _line.end(), static_cast<int(*)(int)>(&std::isspace)))
			continue;
		switch (_line.back())
		{
			case '{':
				/* just error parsing */
				_line.pop_back();
				_file_location++;
				if (lineHasBrackets(_line) || _file_location > ROUTE_OR_ERROR_PAGES)
					configError(line_num, "Too many open brackets");
				break;
			case '}':
				/* just error parsing */
				_line.pop_back();
				if (!all_of(_line.begin(), _line.end(), static_cast<int(*)(int)>(&std::isspace)))
					configError(line_num, "Closing bracket needs to be alone in line");
				_file_location--;
				if (_file_location < BASE)
					configError(line_num, "Too many closing brackets");
				break;
			default:
				/* just error parsing */
				if (lineHasBrackets(_line))
					configError(line_num, "Bracket needs to be at the end of a line");
				else if (_line.find(':') == string::npos)
					configError(line_num, "No colon in setting");
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
	this->server_settings["server_names"] = Setting(false, true);
	this->server_settings["ports"] = Setting(true, true);
	this->server_settings["max_client_body_size"] = Setting(false, false);

	this->route_settings["http_redirect"] = Setting(false, false);
	this->route_settings["http_methods"] = Setting(false, true);
	this->route_settings["root"] = Setting(false, false);
	this->route_settings["default_file"] = Setting(false, false);
	this->route_settings["upload_directory"] = Setting(false, false);
	this->route_settings["directory_listing"] = Setting(false, false);
	this->route_settings["cgi_extensions"] = Setting(false, true);

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