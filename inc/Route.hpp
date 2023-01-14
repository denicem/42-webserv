/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 00:09:17 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 21:46:28 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <string>
#include <vector>
#include <iostream>

#include "HttpMethod.hpp"
#include "Config.hpp"

struct RouteConfig;

class Route {
	private:
		std::string name;
		std::vector<HttpMethod> http_methods;
		std::string http_redirect;
		std::string root;
		bool dir_list;
		std::string default_file;
		std::string upload_dir;
		std::vector<std::string> cgi_exts;

	public:
		Route();
		Route(const std::string&, const RouteConfig&);

		std::string getName() const;
		const std::vector<HttpMethod>& getHttpMethods() const;
		std::string getRoot() const;
		bool getDirList() const;
		std::string getDefaultFile() const;

		friend std::ostream& operator<<(std::ostream&, const Route&);
};

#endif