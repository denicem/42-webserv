
#include "webserv.hpp"

void webserv::addServer(std::vector<int> Port, std::string server_name)
{
	Server server_tmp(server_name);
	//Server müssen vorher mit denn ports und all infos init werden.
	if(Port.size() == 1)
		server_tmp.setPort(*Port.begin());
	else{
		for(std::vector<int>::iterator it = Port.begin(); it != Port.end(); it ++)
			server_tmp.setPort(*it);
	}
	this->serverList.push_back(server_tmp);
}


Server webserv::getServerFromList(int index){
	std::cout << "server name at index: " << this->serverList[index].getServerName() << std::endl;
	return(this->serverList[index]);
}