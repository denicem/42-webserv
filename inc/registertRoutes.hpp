/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   registertRoutes.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeyavat <mjeyavat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:37:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/11/22 22:31:43 by mjeyavat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "./Server.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"


class registertRoutes{

	private:
		//HTTP REQUEST path
		HttpRequest request;
		//HttpAction action; //perpares stuff
		HttpResponse response; //sends stuff
		// on which server
		Server server;	
		// 9 possible methodes in http
		std::string uri;
		
		//location block
		


	public:
		registertRoutes(Server server, HttpRequest request);
		std::string getRelativPath();
		bool checkOnMethod();
		void responseOnEndpoint();
};

