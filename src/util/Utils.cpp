#include "Utils.hpp"

#include <sys/stat.h>

bool isDirectory(const char* path) {
	struct stat s;

	if (lstat(path, &s) == 0) {
		if (!S_ISDIR(s.st_mode))
			return (false);
	}

	return (true);
}