/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:32:40 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/02 17:57:24 by dmontema         ###   ########.fr       */
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
		HttpMethod httpMethod;
		std::string uri;
		std::string restEndpoint;

	public:
		HttpRequest();
		HttpRequest(const HttpRequest&);
		HttpRequest(void*);
		~HttpRequest();

		HttpRequest& operator=(const HttpRequest&);

		HttpMethod getHttpMethod() const;
		std::string getURI() const;
		std::string getRestEndpoint() const;

		void setHttpMethod(const HttpMethod&);
		void setURI(const std::string&);
		void setRestEndpoint(const std::string&);

	private:
		void initVars(std::stringstream&);
		void setHttpMethod(std::stringstream&);
		void setURI(std::stringstream&);
		void setHttpVer(std::stringstream&);
		void setHeaders(std::stringstream&);
		void setMsgBody(std::stringstream&);

	public:
		friend std::ostream& operator<<(std::ostream&, const HttpRequest&);
};

#endif