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
#include "File.hpp"
#include <cstring>
#include <sys/wait.h>

#define WRITE 1
#define READ 0

extern string g_cgi_dir;

class CGI
{
	private:
		string	_program_name;
		string	_cgi_extension;
		string	_input_content;

		/* ENV FOR CGI */
		map<string, string> _request_headers;
		int					_server_port;
		string				_query_string;
		string				_server_protocol;
		string				_server_name;
		vector<string>		_env;
		/*             */

		/* CGI response */
		string	_response_type;
		string	_response_body;

		void			setEnv(void);
		static char**	envConverter(const vector<string>& env); //allocates char**
		static void		CGIError(string error_msg);

	public:
		CGI() {}
		CGI(const map<string, string>& request_headers, int port,
			const string& query_string, const string& cgi_file,
			const string& http_version);
		CGI& operator=(const CGI& rhs);
		~CGI() {}

		void			executeCGI(void);
		const string&	getResponseType(void) { return this->_response_type; }
		const string&	getResponseBody(void) { return this->_response_body; }

		static bool		isCGI(const string& filename, const vector<string>& allowed_cgi_for_route, const string& method);
		
		struct CGIException: public exception
		{
			const char* what() const throw() {
				return ("\033[31;1mError occured during CGI handling \033[0m");
			}
		};
};
