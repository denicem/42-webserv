/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:24:27 by shaas             #+#    #+#             */
/*   Updated: 2022/12/07 17:32:37 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Webserv.hpp"

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
		~CGI() {}

		//set enviroment
		void	setEnv(void);

		void	executeCGI(void);

};