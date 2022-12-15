/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:30:29 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/12/12 22:44:41 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Location.hpp"

#include <iostream>
#include <exception>

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

Location::Location(const std::string& name, const std::string& root, const std::string& index, const std::vector<HttpMethod>& allowedMethods, bool isAlias = false)
	: name(name), root(root), index(index), allowedMethods(allowedMethods), isAlias(isAlias)
{
	this->path = !this->isAlias ? root + name : root;
}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

std::string Location::getName() const {
	return (this->name);
}

std::string Location::getPath() const {
	return (this->path);
}

std::string Location::getIndex() const {
	return (this->index);
}

std::vector<HttpMethod> Location::getAllowedMethods() const {
	return(this->allowedMethods);
}

/*
** ----------------------- METHODS -----------------------
*/



/*
** ----------------------- CLASS ATTRIBUTES -----------------------
*/

/*
** ----------------------- CLASS METHODS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/

std::ostream& operator<<(std::ostream& stream, const Location& loc)
{
	stream << "***** LOCATION *****" << std::endl;
	stream << "Name: " << loc.name << std::endl;
	stream << "Root: " << loc.root << std::endl;
	stream << "Path: " << loc.path << (loc.isAlias ? "(Alias)" : "") << std::endl;
	stream << "Index/Default file: " << loc.index << std::endl;
	stream << "Allowed Methods: ";
	if (loc.allowedMethods.empty())
		stream << "NO METHODS ALLOWED" << std::endl;
	else
	{
		for (std::vector<Location>::size_type i = 0; i < loc.allowedMethods.size(); ++i)
		{
			if (i)
				stream << " ";
			switch (loc.allowedMethods[i])
			{
				case GET: stream << "GET"; break;
				case POST: stream << "POST"; break;
				case DELETE: stream << "DELETE"; break;
				default: stream << "undefined"; break;
			}
		}
		stream << std::endl;
	}
	stream << "********************" << std::endl;
	return (stream);
}
