/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:37:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/11/26 22:12:22 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Config.hpp"

class Location {
	private:
		std::string name;
		std::string root; // root or alias
		std::string path; // root from Server + this->name OR alias
		std::string index; //default_file
		std::vector<int> allowedMethods;
		bool isAlias;

	public:
		Location(const std::string& name, const std::string& rootOrAlias, const std::string& index, const vector<int>&, bool);

		std::string getName() const;
		std::string getPath() const;
		std::string getIndex() const;
};
