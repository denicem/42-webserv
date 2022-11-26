/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Routes.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:30:29 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/11/26 16:20:06 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Routes.hpp"

#include <iostream>
#include <exception>


Routes::Routes(const HttpRequest &_request, std::string name): request(_request){
	location_name = name;
}

void Routes::registerRoutes(){
	this->uriPath = this->request.getURI();
	
}

//nicht sicher
// bool Routes::checkIfRootOrAlias(){
	
	
// }