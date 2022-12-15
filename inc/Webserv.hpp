#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <algorithm>

using namespace std;

#include "TCPPoll.hpp"
#include "Config.hpp"
#include "Server.hpp"
#include "Location.hpp"

// #include "HttpMessage.hpp"
#include "HttpMethod.hpp"
// #include "HttpRequest.hpp"
// #include "HttpResponse.hpp"
// #include "File.hpp"
class Server;



/* MODIFIABLE FEATURES */

#define DEFAULT_CONFIG_FILE_PATH "./conf/default.conf"

/* all supported http methods for this server. initialized in initGlobals function */
extern vector<string>	g_http_methods;

/* all supported cgi extensions for this server. initialized in initGlobals function */
extern vector<string>	g_cgi_extensions;

// string	WAITING_ICON("🕐🕑🕒🕓🕔🕕🕖🕗🕘🕙🕚🕛"); // 🌕🌖🌗🌘🌑🌒🌓🌔🌕

/* COLOURS */

# define RESET	"\e[0m"

/*--- MODES ---*/

# define BOLD		"\e[1m"
# define ITALIC		"\e[3m"
# define UNDERLINED	"\e[4m"

/*-- COLOURED FONT ---*/

# define RED			"\e[31m"
# define GREEN			"\e[32m"
# define YELLOW			"\e[33m"
# define BLUE			"\e[34m"
# define MAGENTA		"\e[35m"
# define CYAN			"\e[36m"
# define LIGHTGRAY		"\e[37m"
# define DARKGRAY		"\e[90m"
# define LIGHTRED		"\e[91m"
# define LIGHTGREEN		"\e[92m"
# define LIGHTYELLOW	"\e[93m"
# define LIGHTBLUE		"\e[94m"
# define LIGHTMAGENTA	"\e[95m"
# define LIGHTCYAN		"\e[96m"

/*--- COLOURED BACKGROUND ---*/

# define RED_BG				"\e[41m"
# define GREEN_BG			"\e[42m"
# define YELLOW_BG			"\e[43m"
# define BLUE_BG			"\e[44m"
# define MAGENTA_BG			"\e[45m"
# define CYAN_BG			"\e[46m"
# define LIGHTGRAY_BG		"\e[47m"
# define DARKGRAY_BG		"\e[100m"
# define LIGHTRED_BG		"\e[101m"
# define LIGHTGREEN_BG		"\e[102m"
# define LIGHTYELLOW_BG		"\e[103m"
# define LIGHTBLUE_BG		"\e[104m"
# define LIGHTMAGENTA_BG	"\e[105m"
# define LIGHTCYAN_BG		"\e[106m"

/////////////////////////////////////////////////////////////////////////////////////////

class Webserv {
	private:
		vector<const Server> serverList;
		
	public:
		Webserv();
		Webserv(const Server& server);

		string	getServerName(int) const;
		int		getPort(int) const;
		Server	getServer(int) const;

		void	setServerName(int, string&);
		void	setPort(int, int);

		void	addServer(const Server& server);
};
