#include "Webserv.hpp"

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

Webserv::Webserv() {}

// Webserv::Webserv(const Server& server) {

// }

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

Server Webserv::getServer(int index) const {
	// cout << "Server name at index: " << this->serverList[index].getServerName() << endl;
	return(this->serverList.at(index));
}

/*
** ----------------------- METHODS -----------------------
*/

void Webserv::addServer(const Server& server) {
	this->serverList.push_back(server);
}

/*
** ----------------------- EXCEPTIONS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/
