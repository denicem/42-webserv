#pragma once

#include "Config.hpp"

#include "Location.hpp"
#include "Server.hpp"

#include "HttpMessage.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "File.hpp"

#include <iostream>
#include <vector>

template < typename T >
void printClassObjs(std::vector<T> vect)
{
	for (typename std::vector<T>::size_type i = 0; i < vect.size(); ++i)
		std::cout << vect[i] << std::endl;
}
