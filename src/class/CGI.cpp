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

char**	CGI::envConverter(const vector<string>& env)
{
	char** c_env;

	c_env = (char **)malloc(sizeof(char *) * (env.size() + 1));
	if (c_env == NULL)
		CGIError("Could not allocate memory");
	c_env[env.size()] = NULL;
	for (unsigned long i = 0; i < env.size(); i++)
	{
		c_env[i] = strdup(env[i].c_str());
		if (c_env[i] == NULL)
			CGIError("Could not allocate memory");
	}
	return (c_env);
}

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void	CGI::setEnv(void)
{
	string	buf;

	if (!g_PATH.empty())
		_env.push_back(g_PATH);
	_env.push_back("SERVER_SOFTWARE=DMS-Server/1.0");
	_env.push_back("GATEWAY_INTERFACE=CGI/1.1");
	_env.push_back("SERVER_PROTOCOL=HTTP/1.1");
	_env.push_back("REQUEST_METHOD=GET"); //because we only allow cgi for GET
	_env.push_back("PATH_INFO=");
	_env.push_back("PATH_TRANSLATED=");
	_env.push_back("QUERY_STRING=" + _query_string);
	_env.push_back("SCRIPT_NAME=" + _program_name);
	if (_request_headers.find("Host") != _request_headers.end()) {
		buf = _request_headers.find("Host")->second;
		_server_name = buf.substr(0, buf.find(':') == string::npos ? buf.size() : buf.find(':'));
		_request_headers.erase("Host");
	}
	_env.push_back("SERVER_NAME=" + _server_name);
	_env.push_back("SERVER_PORT=" + intToString(_server_port));
	_env.push_back("REMOTE_ADDR=");

	for (map<string, string>::iterator i = _request_headers.begin(); i != _request_headers.end(); i++) {
		buf = i->first;
		for (string::iterator j = buf.begin(); j != buf.end(); j++) {
			*j = toupper(*j);
			if (*j == '-')
				*j = '_';
		}
		_env.push_back("HTTP_" + buf + '=' + i->second);
	}
}

void	CGI::executeCGI(void)
{
	char**	env = envConverter(_env);

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
			if (execle(_program_name.c_str(), _program_name.c_str(), (char*)NULL, env) == -1)
				CGIError("Could not execute binary CGI program");
		}
		else if (_cgi_extension == ".py") {
			if (execle("/usr/bin/python3", "python3", _program_name.c_str(), (char*)NULL, env) == -1)
				CGIError("Could not execute Python CGI program");
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

		for (int i = 0; env[i] != NULL; i++)
		{
			free(env[i]);
		}
		free(env);

		if (cgi_out_str.find("\r\n\r\n") == string::npos) {
			_response_type = "plain";
			_response_body = cgi_out_str;
		}
		else {
			_response_type = cgi_out_str.substr(0, cgi_out_str.find("\r\n\r\n"));
			if (_response_type.find("Content-type:") == string::npos)
				_response_type = "plain";
			else {
				_response_type = _response_type.substr(_response_type.find("Content-type:")+13);
				_response_type = _response_type.substr(_response_type.find("/") == string::npos ? 0 : _response_type.find("/")+1); //
				_response_type = _response_type.substr(0, _response_type.find("\n") == string::npos ? INT_MAX : _response_type.find("\n")+1);
			}
			_response_body = cgi_out_str.substr(cgi_out_str.find("\r\n\r\n")+4);
		}
	}
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

CGI::CGI(const map<string, string>& request_headers, int port,
		const string& query_string, const string& cgi_file,
		const string& http_version)
{
	if (access(("./cgi-bin/" + cgi_file).c_str(), F_OK) == -1)
		throw File::FileNotFoundException();
	_program_name = "./cgi-bin/" + cgi_file;
	_cgi_extension = cgi_file.substr(cgi_file.rfind('.'));
	_server_port = port;
	_query_string = query_string;
	_server_protocol = http_version;
	_request_headers = request_headers;
	this->setEnv();
}

/*
** ----------------------- STATIC METHODS -----------------------
*/

bool	CGI::isCGI(const string& filename, const vector<string>& allowed_cgi_for_route, const string& method)
{
	if (method != "GET") // hardcoded.. if we were to add more methods, need to change
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

CGI&	CGI::operator=(const CGI& rhs)
{
	if (this != &rhs) {
		this->_program_name = rhs._program_name;
		this->_cgi_extension = rhs._cgi_extension;
		this->_request_headers = rhs._request_headers;
		this->_server_port = rhs._server_port;
		this->_query_string = rhs._query_string;
		this->_server_protocol = rhs._server_protocol;
		this->_server_name = rhs._server_name;
		this->_env = rhs._env;
		this->_response_type = rhs._response_type;
		this->_response_body = rhs._response_body;
	}
	return *this;
}

/*
** ----------------------- PUBLIC METHODS -----------------------
*/
