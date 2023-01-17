/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:24:27 by shaas             #+#    #+#             */
/*   Updated: 2023/01/12 19:15:22 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Webserv.hpp"
#include <cstring>
#include <sys/wait.h>

#define WRITE 1
#define READ 0

extern string g_cgi_dir;

class HttpAction;

class CGI
{
	private:
		string	_program_name;
		string	_cgi_extension;
		string	_input_content;

		/* ENV FOR CGI */
		string	_server_name;
		int		_server_port;
		string	_request_method; // or get as int?
		string	_path_info;
		string	_script_name;
		string	_query_string;
		string	_content_type;
		string	_content_length;
		char**	_env;

		//set enviroment
		void			setEnv(void);

		static void		CGIError(string error_msg);

	public:
		CGI(); // for testing
		/* assumes the request has already been established as valid for CGI */
		CGI(const HttpAction& http);
		~CGI();

		static bool	isCGI(const string& filename, const vector<string>& allowed_cgi_for_route, const string& method);
		string		executeCGI(void);
		static string	intToString(int i);
		
		struct CGIException: public exception
		{
			const char* what() const throw() {
				return ("\033[31;1mError occured during CGI handling \033[0m");
			}
		};
};
