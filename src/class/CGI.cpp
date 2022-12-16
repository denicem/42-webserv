/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:25:48 by shaas             #+#    #+#             */
/*   Updated: 2022/12/16 17:21:47 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

/*
** ----------------------- GLOBAL VARIABLES -----------------------
*/

string g_cgi_dir("./cgi-bin/");

/*
** ----------------------- PRIVATE STATIC METHODS -----------------------
*/

void	CGI::CGIError(string error_msg)
{
	cout << error_msg << '\n';
	throw CGIException();
}

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

// void	CGI::setEnv(void)
// {
// 	vector<string>	prepare_env;

// 	prepare_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
// 	prepare_env.push_back("SERVER_PORT=" + )
// }

// string	CGI::executeCGI(void)
// {
// 	int pid;
// 	int	pp[2];
// 	if (pipe(pp) == -1)
// 		CGIError("Error when opening pipe");
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		dup2(pp[1], STDOUT_FILENO);
// 		close(pp[1]);
// 		close(pp[0]);
// 		if (execl("/usr/bin/perl", "perl", phpfile.c_str(), NULL) == -1 )
// 			std::cerr << "Error in perl cgi Execution\n";
// 		exit(0);
// 	}
// 	else if (pid == -1)
// 		CGIError("Fork has failed");
// 	else
// 	{
// 		waitpid(-1, NULL, 0);
// 		char hold;
// 		fcntl(fd[0], F_SETFL, O_NONBLOCK);
// 		while (read(fd[0], &hold, 1) != -1)
// 			temp += hold;
// 		close(fd[1]);
// 		close(fd[0]);
// 	}
// 	return (temp);
// }

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

CGI::CGI(const HttpAction& http)
{
	//change later!!!
	(void)http;
	_program_name = "telephone.cgi";
	_cgi_extension = ".cgi";
}

CGI::CGI()
{
	_program_name = "telephone.cgi";
	_cgi_extension = ".cgi";
}

/*
** ----------------------- STATIC METHODS -----------------------
*/

bool	CGI::isCGI(const string& filename, const vector<string>& allowed_cgi_for_route, const string& method)
{
	if (method != "GET" && method != "POST") // hardcoded.. if we were to add more methods, need to change
		return false;
	if (filename.rfind('.') == string::npos)
		return false;
	string file_extension = filename.substr(filename.rfind('.'));
	for (vector<string>::const_iterator i = allowed_cgi_for_route.begin(); i != allowed_cgi_for_route.end(); i++)
	{
		if (file_extension == *i)
			return true;
	}
	return false;
}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- PUBLIC METHODS -----------------------
*/
