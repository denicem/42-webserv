/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:32:40 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/17 21:36:48 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "HttpMessage.hpp"
#include "HttpMethod.hpp"

#include <sstream>
#include <string>
#include <vector>

class HttpRequest: public HttpMessage {
	private:
		HttpMethod http_method;
		std::string uri;
		std::string path;
		std::string query;

	public:
		HttpRequest();
		HttpRequest(const HttpRequest&);
		HttpRequest(void*);
		HttpRequest(const std::string&);
		~HttpRequest();

		HttpRequest& operator=(const HttpRequest&);

		HttpMethod getHttpMethod() const;
		std::string getURI() const;
		std::string getPath() const;
		std::string getQuery() const;

		void setURI(const std::string&);
		void setPath(const std::string&);

	private:
		void fetchRequestBuffer(std::stringstream&);
		void fetchHttpMethod(std::stringstream&);
		void fetchURI(std::stringstream&);
		void fetchHttpVer(std::stringstream&);
		void fetchHeaders(std::stringstream&);
		void fetchMsgBody(std::stringstream&);

	public:
		friend std::ostream& operator<<(std::ostream&, const HttpRequest&);
};

#endif
