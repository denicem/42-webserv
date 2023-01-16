#include "dirListing.hpp"
#include "Server.hpp"


std::string dirListing::generateDirOutput(int index, const Server& server) {

    if(index == -1)
        index = 0;
    std::cout << "Index: " << index << "Listing output" << std::endl;
    std::cout << "server location: " << server.getRoute(index).getName() << std::endl;
    std::cout << "Get root file: " << server.getRoute(index).getRoot() << std::endl;
    std::cout << "Is Listing on?: " << server.getRoute(index).getDirList() << std::endl;

    //anhand dieser Informationenen muss jetzt eine Listing funktion geschrieben werden.
    std::string dirName = server.getRoute(index).getName();
    DIR *dir = opendir(server.getRoute(index).getRoot().c_str());
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
    if (dirName[0] != '/')
        dirName = "/" + dirName;
    for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir)) {
        page += getLink(std::string(dirEntry->d_name), dirName, server.getServerName(), 0000);
    }
    page +="\
    </p>\n\
    </body>\n\
    </html>\n";
    closedir(dir);
    return page;
}

std::string         dirListing::getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host, int port) {
    std::stringstream   ss;
    ss << "\t\t<p><a href=\"http://" + host + ":" <<\
        port << dirName + "/" + dirEntry + "\">" + dirEntry + "</a></p>\n";
    return ss.str();
}