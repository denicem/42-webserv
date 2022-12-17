/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:24:27 by shaas             #+#    #+#             */
/*   Updated: 2022/12/15 23:52:00 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Webserv.hpp"

extern string g_cgi_dir;

class HttpAction;

class CGI
{
	private:
		string	_program_name;
		string	_cgi_extension;
		int		port;
		char**	env;

		//set enviroment
		void		setEnv(void);
		static void	CGIError(string error_msg);


	public:
		CGI(); // for testing
		/* assumes the request has already been established as valid for CGI */
		CGI(const HttpAction& http);
		~CGI() {}

		static bool	isCGI(const string& filename, const vector<string>& allowed_cgi_for_route, const string& method);
		string		executeCGI(void);
		
		struct CGIException: public exception
		{
			const char* what() const throw() {
				return ("\033[31;1mError occured during CGI handling \033[0m");
			}
		};
};
