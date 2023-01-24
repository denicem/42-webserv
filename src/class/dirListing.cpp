#include "dirListing.hpp"
#include "Server.hpp"


std::string dirListing::generateDirOutput(int index, const Server& server) {

	if(index == -1)
		index = 0;
	PRINT_W_COLOR(BOLD, "DIR-LISTING");
	std::cout << RED <<"Index: " << index << "Listing output" << RESET << std::endl;
	std::cout << RED << "server location: " << server.getRoute(index).getName() << RESET << std::endl;
	std::cout << RED << "Get root file: " << server.getRoute(index).getRoot() << RESET << std::endl;
	std::cout << RED <<  "Is Listing on?: " << server.getRoute(index).getDirList() << RESET << std::endl;

	// anhand dieser Informationen muss jetzt eine Listing funktion geschrieben werden.
	std::string dirName = server.getRoute(index).getName();

	DIR *dir;
	DIR *subDir;

	dir = opendir(server.getRoute(index).getRoot().c_str());
	// dir = opendir(".");
	std::string page =\
	"<!DOCTYPE html>\n\
	<html>\n\
	<head>\n\
			<title>" + dirName + "</title>\n\
	</head>\n\
	<body>\n\
	<h1>INDEX</h1>\n\
	<p>\n";

	if (dir == NULL) {
		std::cerr << RED << "Error: could not open [" << server.getRoute(index).getRoot() << "]" << RESET << std::endl;
		return "";
	}
	for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir)) {
		std::cout << "http://" << "localhost:" << server.getPort(0) << dirName << "/" << std::string(dirEntry->d_name) << std::endl;
		std::cout << "dirEntry: " << std::string(dirEntry->d_name) << std::endl;
		if(dirEntry->d_type == DT_DIR) {
			// std::cout << "dirEntry: " << "is a directory" << std::endl;
			if(std::string(dirEntry->d_name) == "." || std::string(dirEntry->d_name) == "..")
				page += getLink(std::string(dirEntry->d_name), dirName, "localhost", server.getPort(0));
			else {
				// page += getLink(std::string(dirEntry->d_name), dirName, "localhost", server.getPort(0));
				std::string dName = server.getRoute(index).getRoot() + '/' + std::string(dirEntry->d_name);
				// std::cout << "serverroot + dName: " << server.getRoute(index).getRoot()<< dName << std::endl;
				subDir = opendir(dName.c_str());
				for(struct dirent *dirent2 = readdir(subDir); dirent2; dirent2 = readdir(subDir)) {
					if(std::string(dirent2->d_name) == "." || std::string(dirent2->d_name) == "..")
						dirent2 = readdir(subDir);
					else {
						std::string newPlace = "/" + std::string(dirEntry->d_name);
						page += getSubLink(std::string(dirent2->d_name), std::string(dirEntry->d_name), newPlace, "localhost", server.getPort(0));
					}
				}
				closedir(subDir);
			}
		}
		else {
			std::cout << "is a File" << std::endl;
			page += getLink(std::string(dirEntry->d_name), dirName, "localhost", server.getPort(0));
		}
	}
	page +="\
	</p>\n\
	</body>\n\
	</html>\n";
	closedir(dir);
	return page;
}

std::string dirListing::getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host, int port) {
	std::stringstream   ss;
	ss << "\t\t<p><a href=\"http://" + host + ":" <<\
		port << dirName + "/" + dirEntry + "\">" + dirEntry + "</a></p>\n";
	PRINT_W_COLOR(RED ,ss.str());
	return ss.str();
}

std::string dirListing::getSubLink(std::string const &dirEntry, std::string const &secEntry, std::string const &dirName, std::string const &host, int port) {
	std::stringstream   ss;
	ss << "\t\t<p><a href=\"http://" + host + ":" <<\
		port << dirName + "/" + dirEntry + secEntry + "\">" + secEntry + "</a></p>\n";
	PRINT_W_COLOR(RED ,ss.str());
	return ss.str();
}