/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:37:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/12/13 12:38:10 by mjeyavat         ###   ########.fr       */
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
		std::string path; // root (from Server?) + this->name OR  if isAlias == true -> root
		std::string index; //default_file
		std::vector<HttpMethod>allowedMethods;
		bool isAlias;

	public:
		Location(const std::string& name, const std::string& rootOrAlias, 
			const std::string& index, const std::vector<HttpMethod>&, bool);

		std::string getName() const;
		std::string getPath() const;
		std::string getIndex() const;

		std::vector<HttpMethod>getAllowedMethods() const;

		friend std::ostream& operator<<(std::ostream&, const Location&);
};
