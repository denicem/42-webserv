/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:43:33 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/14 00:14:09 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include "HttpMessage.hpp"
#include "File.hpp"

class HttpResponse: public HttpMessage
{
private:
	int _statusCode;
	std::string _statusMsg;
	File _file;

public:
	HttpResponse();
	HttpResponse(const HttpResponse&);
	HttpResponse(const std::string&);
	~HttpResponse();

	HttpResponse& operator=(const HttpResponse&);

	std::string genHttpResponseMsg() const;

	int getStatusCode() const;
	std::string getStatusMsg() const;

	void setStatusCode(const int&);
	void setStatusMsg(const std::string&);
};

#endif