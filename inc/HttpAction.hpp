/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaas <shaas@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:07:07 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/15 21:22:59 by shaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_ACTION_HPP
#define HTTP_ACTION_HPP

#include "File.hpp"
#include "HttpMessage.hpp"
#include "HttpMethod.hpp"
#include "HttpRequest.hpp"
#include "Server.hpp"

class HttpAction: public HttpMessage {
	private:
		HttpMethod method;
		int statusCode;
		File file;

		std::string path;
		std::string dest;

	private:
		void initVars(const HttpRequest&, const Server&);
		void setPath(const HttpRequest&, const Server&);
		bool isMethodAllowed(const int, const Location&) const;
		int getLocationIndex(const std::string&, const Server&) const;
		bool isDestination(const std::string&) const;

	public:
		HttpAction();
		HttpAction(const HttpAction&);
		HttpAction(const HttpRequest&, const Server&);
		~HttpAction();

		HttpAction& operator=(const HttpAction&);

		HttpMethod getHttpMethod() const;
		int getStatusCode() const;
		File getFile() const;
};

#endif
