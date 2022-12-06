
#pragma once

extern char **enviroment;


class CGI
{
	private:
		
		// char **_argvp;
		// char **_envp;
		std::string request;
		

	public:
		int _fd_in[2];
		int _fd_out[2];
		
		CGI();
		~CGI();

		//set enviroment
		void set_envs(void);
		
		void execute_cgi(void);

}