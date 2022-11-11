/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:32:40 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/10 23:04:53 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "HttpMessage.hpp"

class HttpRequest: public HttpMessage
{
private:
	HttpMethod _httpMethod;
	std::string _uri;
	std::string _restEndpoint;

public:
	HttpRequest();
	HttpRequest(const HttpRequest&);
	~HttpRequest();

	HttpRequest& operator=(const HttpRequest&);

	HttpMethod getHttpMethod() const;
	std::string getURI() const;
	std::string getRestEndpoint() const;

	void setHttpMethod(const HttpMethod&);
	void setURI(const std::string&);
	void setRestEndpoint(const std::string&);
};

#endif