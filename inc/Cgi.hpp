/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:24:27 by shaas             #+#    #+#             */
/*   Updated: 2022/12/09 19:49:17 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Webserv.hpp"
#include "HttpAction.hpp"

extern char **enviroment;

class CGI
{
	private:
		
		// char **_argvp;
		// char **_envp;
		string request;
		

	public:
		int _fd_in[2];
		int _fd_out[2];
		
		CGI() {}
		CGI(const HttpAction& http);
		~CGI() {}

		//set enviroment
		void	setEnv(void);

		void	executeCGI(void);

		static bool	isCGI(const string& filename, const vector<string>& allowed_cgi_for_route);

};