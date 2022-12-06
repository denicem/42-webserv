/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Routes.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:37:57 by mjeyavat          #+#    #+#             */
/*   Updated: 2022/12/06 00:38:43 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpMessage.hpp"
#include "Config.hpp"

class Routes{

	private:
		//Config routeSetting;
		bool alias;
		std::string location_name;
		std::string uriPath;
		/**
		 * Request hat:
		 * 	Methode, uri, endpoint
		 * macht:
		 * 	holt sich die uri, wie?
		 * 	holt sich denn endpoint, wie? mit setURI();
		 * 	setst sich denn header
		 * 	
		*/
		HttpRequest request;
		HttpMessage message;
		/**
		 * response hatt:
		 * 	status code, status message, file
		 * macht:
		 * 	generiert response message -> braucht request referense
		 * 	
		*/
		HttpResponse response; //sends stuff
		
		//location block
		


	public:
		Routes(const HttpRequest &request, std::string name);
		//std::string getRelativPath();
		/**
		 * Returns true if root is in location
		*/
		// bool checkIfRootOrAlias();
		/**
		 * if root then append name to uri
		*/
		void registerRoutes();
		string appendTOUri();
		/**
		 * takes Uri sees on wicht location it is and executes it
		 * */ 
		int executedeOnUri();
};

