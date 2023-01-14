/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 00:23:37 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 01:02:11 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Route.hpp"

#include <iostream>

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

Route::Route() {}

Route::Route(const std::string& name, const RouteConfig& r_conf):
	name(name),
	http_redirect(r_conf.http_redirect),
	root(r_conf.root),
	dir_list(r_conf.directory_listing),
	default_file(r_conf.default_file),
	upload_dir(r_conf.upload_directory),
	cgi_exts(r_conf.cgi_extensions)
{
	for (std::vector<std::string>::size_type i = 0; i < r_conf.http_methods.size(); ++i) {
		if (r_conf.http_methods[i] == "GET")
			this->http_methods.push_back(GET);
		else if (r_conf.http_methods[i] == "POST")
			this->http_methods.push_back(POST);
		else if (r_conf.http_methods[i] == "DELETE")
			this->http_methods.push_back(DELETE);
	}
}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

std::string Route::getName() const {
	return (this->name);
}

const std::vector<HttpMethod>& Route::getHttpMethods() const {
	return (this->http_methods);
}

std::string Route::getRoot() const {
	return (this->root);
}

std::string Route::getDefaultFile() const {
	return (this->default_file);
}

/*
** ----------------------- METHODS -----------------------
*/

/*
** ----------------------- EXCEPTIONS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/

std::ostream& operator<<(std::ostream& stream, const Route& r) {
	stream << "***** Route *****" << std::endl;

	stream << "Name: " << r.name << std::endl;
	stream << "Allowed Methods: ";
	for (std::vector<HttpMethod>::size_type i = 0; i < r.http_methods.size(); ++i) {
		if (i) stream << " ";
		stream << getHttpMethodStr(r.http_methods[i]);
	}
	stream << std::endl;
	stream << "HTTP Redirection: " << (r.http_redirect.empty() ? "/" : r.http_redirect) << std::endl;
	stream << "Root: " << r.root << std::endl;
	stream << "Directory Listing? " << (r.dir_list ? "on" : "off") << std::endl;
	stream << "Default file: " << r.default_file << std::endl;
	stream << "Upload directory: " << (r.upload_dir.empty() ? "default" : r.upload_dir) << std::endl;
	stream << "CGI extensions: ";
	if (r.cgi_exts.empty())
		stream << "No extensions." << std::endl;
	else {
		for (std::vector<std::string>::size_type i = 0; i < r.cgi_exts.size(); ++i) {
			if (i)	stream << " ";
			stream << r.cgi_exts[i];
		}
	}
	stream << std::endl;
	stream << "********************" << std::endl;

	return (stream);
}