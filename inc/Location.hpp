/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:37:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/11/29 14:08:18 by dmontema         ###   ########.fr       */
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
		std::string root; // root or alias
		std::string path; // root from Server + this->name OR alias
		std::string index; //default_file
		std::vector<HttpMethod>allowedMethods;
		bool isAlias;

	public:
		Location(const std::string& name, const std::string& rootOrAlias, const std::string& index, const std::vector<HttpMethod>&, bool);

		std::string getName() const;
		std::string getPath() const;
		std::string getIndex() const;

		std::vector<HttpMethod>getAllowedMethods() const;

		friend std::ostream& operator<<(std::ostream&, const Location&);
};
