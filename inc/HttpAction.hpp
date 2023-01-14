/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:07:07 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 22:38:32 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_ACTION_HPP
#define HTTP_ACTION_HPP

#define ERROR_PAGE_400 "./error/400.html"
#define ERROR_PAGE_404 "./error/404.html"
#define ERROR_PAGE_405 "./error/405.html"
#define ERROR_PAGE_501 "./error/501.html"

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

		int location;
		int route_index;
		std::string path;
		std::string dest;

	private:
		void initVars(const HttpRequest&, const Server&);
		void setPath(const HttpRequest&, const Server&);
		bool isMethodAllowed(const int, const Route&) const;
		int getLocationIndex(const std::string&, const Server&) const;
		int getRouteIndex(const std::string&, const Server&) const;
		bool isDestination(const std::string&) const;
		std::string getDefaultErrorPage(int) const;

	public:
		HttpAction();
		HttpAction(const HttpAction&);
		HttpAction(const HttpRequest&, const Server&);
		~HttpAction();

		HttpAction& operator=(const HttpAction&);

		HttpMethod getHttpMethod() const;
		int getStatusCode() const;
		File getFile() const;

		void doAction(const Server&);
};

#endif
