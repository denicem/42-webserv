/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registertRoutes.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:37:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/11/21 18:57:27 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Server.hpp"
#include "HttpRequest.hpp"


class registertRoutes{

	private:
		//HTTP REQUEST path
		Server server;	
		// 9 possible methodes in http	
		int methodes[9];		
		std::string uri;

	public:
		registertRoutes();
		std::string routeFunction(Server server, HttpRequest request);
		
};

