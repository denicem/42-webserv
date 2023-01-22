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

    //anhand dieser Informationenen muss jetzt eine Listing funktion geschrieben werden.
    std::string dirName = server.getRoute(index).getName();
    // size_t pos = server.getRoute(index).getRoot().find("/");
    DIR *dir;
    // std::string fixedRoot = server.getRoute(index).getRoot();
    // if( pos == std::string::npos)
        dir = opendir(server.getRoute(index).getRoot().c_str());
    // else
    // {
        // fixedRoot = dirName.substr(pos+4);
        // PRINT_W_COLOR(BLUE, fixedRoot);
        // PRINT_W_COLOR(YELLOW, dirName);
        // dir = opendir(fixedRoot.c_str());
        // std::cout << GREEN <<"http://localhost:"<< server.getPort(0) << "/" << std::string(dir->d) << RESET <<std::endl;  
    // }
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
    /***
     * DT_REG

    A regular file.
    DT_DIR

    A directory.

    */
    // if (dirName[0] != '/')
        // dirName = "/" + dirName;
    
    for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir)) {
        std::cout << "http://" << "localhost:" << server.getPort(0) << dirName << "/" << std::string(dirEntry->d_name) << std::endl;
        std::cout << "dirEntry: " << std::string(dirEntry->d_name) << std::endl;
        if(dirEntry->d_type == DT_DIR) {
            std::cout << "dirEntry: " << "is a directory" << std::endl;
            if(std::string(dirEntry->d_name) == "." || std::string(dirEntry->d_name) == "..")
                page += getLink(std::string(dirEntry->d_name), dirName, "localhost", server.getPort(0));
            else {
                dirEntry = readdir(dir);
                // page += getLink(std::string(dirEntry->d_name), dirName, "localhost", server.getPort(0));
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

std::string         dirListing::getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host, int port) {
    std::stringstream   ss;
    ss << "\t\t<p><a href=\"http://" + host + ":" <<\
        port << dirName + "/" + dirEntry + "\">" + dirEntry + "</a></p>\n";
    PRINT_W_COLOR(RED ,ss.str());
    return ss.str();
}