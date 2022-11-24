
#include "webserv.hpp"

void webserv::addServer(vector<int> Port, string server_name)
{
	Server server_tmp(server_name);
	//Server müssen vorher mit denn ports und all infos init werden.
	if(Port.size() == 1)
		server_tmp.setPort(*Port.begin());
	else{
		for(vector<int>::iterator it = Port.begin(); it != Port.end(); it ++)
			server_tmp.setPort(*it);
	}
	this->serverList.push_back(server_tmp);
}


Server webserv::getServerFromList(int index){
	cout << "server name at index: " << this->serverList[index].getServerName() << endl;
	return(this->serverList[index]);
}