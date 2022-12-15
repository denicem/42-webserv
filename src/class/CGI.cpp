/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:25:48 by shaas             #+#    #+#             */
/*   Updated: 2022/12/15 19:17:36 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"


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

// string	CGI::executeCGI(void)
// {
// 	string	compile_cmd;

// 	compile_cmd = "gcc ./cgi-bin/" + _program_name + " -o cgi_prg";
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
// 	}
// }

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

CGI::CGI(const HttpAction& http)
{
	//change later!!!
	(void)http;
	_program_name = "telephone.c";
	_cgi_extension = ".c";
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
	for (vector<string>::const_iterator i = allowed_cgi_for_route.cbegin(); i != allowed_cgi_for_route.end(); i++)
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
