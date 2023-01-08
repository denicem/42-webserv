/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:37:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/12/17 16:57:03 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Config.hpp"
#include "HttpMethod.hpp"

#include <iostream>
#include <string>
#include <vector>

class Location {
	private:
		std::string name;
		std::string root;
		std::string index; //default_file
		std::vector<HttpMethod>allowedMethods;
		bool directoryListing;

	public:
		Location(const std::string& name, const std::string& root, 
			const std::string& index, const std::vector<HttpMethod>&, bool directoryListing);

		std::string getName() const;
		std::string getIndex() const;
		std::string getRoot() const;
		std::vector<HttpMethod>getAllowedMethods() const;

		friend std::ostream& operator<<(std::ostream&, const Location&);
};
