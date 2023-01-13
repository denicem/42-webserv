/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Route.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 00:09:17 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/13 01:28:43 by dmontema         ###   ########.fr       */
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
		std::vector<HttpMethod> http_methods;
		std::string http_redirect;
		std::string root;
		bool dir_list;
		std::string default_file;
		std::string upload_dir;
		std::vector<std::string> cgi_exts;

	public:
		Route();
		Route(const RouteConfig&);

		friend std::ostream& operator<<(std::ostream&, const Route&);
};

#endif