#include "Webserv.hpp"

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

Webserv::Webserv() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

Server Webserv::getServer(int index) const {
	cout << "Server name at index: " << this->serverList[index].getServerName() << endl;
	return(this->serverList[index]);
}

/*
** ----------------------- METHODS -----------------------
*/

void Webserv::addServer(vector<int>& ports, const string& serverName, const string& root, const vector<Location>& locations) {
	Server tmpServer(serverName, root, locations);

	//Server müssen vorher mit den ports und all infos init werden.
	if (ports.size() == 1)
		tmpServer.setPort(*ports.begin());
	else {
		for (vector<int>::iterator it = ports.begin(); it != ports.end(); it ++)
			tmpServer.setPort(*it);
	}
	this->serverList.push_back(tmpServer);
}

/*
** ----------------------- EXCEPTIONS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/
