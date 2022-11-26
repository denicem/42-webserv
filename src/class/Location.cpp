/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:30:29 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/11/26 22:09:08 by dmontema         ###   ########.fr       */
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

Location::Location(const std::string& name, const std::string& root, const std::string& index, const vector<int>& allowedMethods, bool isAlias = false)
	: name(name), root(root), index(index), allowedMethods(allowedMethods), isAlias(isAlias)
{
	if (!isAlias)
		this->path = root + name;
	else
		this->path = root;
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
