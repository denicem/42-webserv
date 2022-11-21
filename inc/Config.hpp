/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:36:32 by shaas             #+#    #+#             */
/*   Updated: 2022/11/17 22:47:37 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "webserv.hpp"

// enum modes {
	
// };

typedef struct s_server_config
{
	
} ServerConfig;

class Config
{
	private:
		std::vector<ServerConfig> _server_configs;
	
		std::string	_config_file_path;
		int			_mode; //?
		int			_open_brackets;
	
		void	getFilePath(int argc, char* argv[]);
	
	public:
		Config(int argc, char* argv[]);
		~Config();
	
		struct ConfigException: public std::exception
		{
			const char* what() const throw() {
				return ("\033[31;1mError occured during config parsing 🛠️\033[0m");
			}
		};
};

#endif