

#include <dirent.h>
#include <errno.h>
#include <sys/types.h>

#include <stdio.h>
#include "HttpRequest.hpp"
#include "Server.hpp"


class dirListing {
    private:
        //servername
    public:
        std::string generateDirOutput(int index, const Server& server);
        std::string getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host, int port);



};