/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:07:07 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/14 18:49:25 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_ACTION_HPP
#define HTTP_ACTION_HPP

#include "HttpMessage.hpp"
#include "HttpMethod.hpp"
#include "HttpRequest.hpp"
#include "File.hpp"
#include "Server.hpp"

class HttpAction: public HttpMessage {
	private:
		HttpMethod method;
		int statusCode;
		File file;

		std::string uri;
		std::string path;
		std::string dest;

	private:
		void initVars(const HttpRequest&, const Server&);
		void setURI(const HttpRequest&, const Server&);
		void setDest(const HttpRequest&, const Server&);
		bool isMethodAllowed(const int, const Location&) const;
		int getLocationIndex(const Server&) const;
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
