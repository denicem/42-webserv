/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:32:40 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/13 01:42:09 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include "HttpMessage.hpp"

#include <sstream>
#include <string>
#include <vector>

class HttpRequest: public HttpMessage
{
private:
	HttpMethod _httpMethod;
	std::string _uri;
	std::string _restEndpoint;

public:
	HttpRequest();
	HttpRequest(const HttpRequest&);
	HttpRequest(void*);
	~HttpRequest();

	HttpRequest& operator=(const HttpRequest&);

	HttpMessage::HttpMethod getHttpMethod() const;
	std::string getURI() const;
	std::string getRestEndpoint() const;

	void setHttpMethod(const HttpMethod&);
	void setURI(const std::string&);
	void setRestEndpoint(const std::string&);

private:
	void initVars();
	void setHttpMethod(std::stringstream&);
	void setURI(std::stringstream&);
	void setHttpVer(std::stringstream&);

public:
	friend std::ostream& operator<<(std::ostream&, const HttpRequest&);
};

#endif