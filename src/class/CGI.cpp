/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.ccgi_out                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:25:48 by shaas             #+#    #+#             */
/*   Updated: 2023/01/09 04:48:32 by shaas            ###   ########.fr       */
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

string	CGI::intToString(int i)
{
	stringstream ss;
	ss << i;
	return (ss.str());
}

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void	CGI::setEnv(void)
{
	vector<string>	prepare_env;

	prepare_env.push_back("SERVER_SOFTWARE=DMS-Server/0.5");
	prepare_env.push_back("SERVER_NAME=" + _server_name);
	prepare_env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	prepare_env.push_back("SERVER_PORT=" + intToString(_server_port));
	prepare_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	prepare_env.push_back("REQUEST_METHOD=" + _request_method);
	prepare_env.push_back("PATH_INFO=" + _path_info);
	prepare_env.push_back("PATH_TRANSLATED=" + _path_info);
	prepare_env.push_back("SCRIPT_NAME=" + _script_name);
	prepare_env.push_back("QUERY_STRING=" + _query_string);
	prepare_env.push_back("CONTENT_TYPE=" + _content_type);
	prepare_env.push_back("CONTENT_LENGTH=" + _content_length);

	_env = (char **)malloc(sizeof(char *) * (prepare_env.size() + 1));
	if (_env == NULL)
		CGIError("Could not allocate memory");
	_env[prepare_env.size()] = NULL;
	for (unsigned long i = 0; i < prepare_env.size(); i++)
	{
		_env[i] = strdup(prepare_env[i].c_str());
		if (_env[i] == NULL)
			CGIError("Could not allocate memory");
	}
	cout << LIGHTBLUE << "ENV\n" << RESET; 
	for (int i = 0; _env[i] != NULL; i++)
	{
		cout << _env[i] << '\n';
	}
}

string	CGI::executeCGI(void)
{
	int 	pid;
	int		cgi_out[2];
	int		cgi_in[2];
	string	cgi_out_str;

	if (pipe(cgi_out) == -1 || pipe(cgi_in) == -1)
		CGIError("Error when opening pipe");
	write(cgi_in[WRITE], _input_content.c_str(), _input_content.size());
	close(cgi_in[WRITE]);

	pid = fork();
	if (pid == 0)
	{
		dup2(cgi_out[WRITE], STDOUT_FILENO);
		close(cgi_out[WRITE]);
		close(cgi_out[READ]);
		dup2(cgi_in[READ], STDIN_FILENO);
		close(cgi_in[READ]);
		if (_cgi_extension == ".cgi") {
			if (execle(("./cgi-bin/" + _program_name).c_str(), _program_name.c_str(), (char*)NULL, _env) == -1)
				CGIError("Could not execute binary CGI program");
		}
		else if (_cgi_extension == ".py") {
			if (execle("/usr/bin/python3", "python3", ("./cgi-bin/" + _program_name).c_str(), (char*)NULL, _env) == -1 )
				std::cerr << "Could not execute Python CGI program\n";
		}
		else
			CGIError("Invalid CGI extension");
		exit(0);
	}
	else if (pid == -1)
		CGIError("Fork has failed");
	else
	{
		waitpid(-1, NULL, 0);
		char hold;
		fcntl(cgi_out[READ], F_SETFL, O_NONBLOCK);
		while (read(cgi_out[READ], &hold, 1) != -1)
			cgi_out_str += hold;
		close(cgi_out[READ]);
		close(cgi_out[WRITE]);
		close(cgi_in[READ]);
	}
	return (cgi_out_str);
}

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
	_program_name = "webscrap_mal.py";
	_cgi_extension = ".py";
	this->setEnv(); // temporary
}

CGI::~CGI() // TEST!!
{
	for (int i = 0; _env[i] != NULL; i++)
	{
		free(_env[i]);
	}
	free(_env);
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
