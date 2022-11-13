/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:11:57 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/13 01:46:17 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPMESSAGE_HPP
#define HTTPMESSAGE_HPP

#include <string>


class HttpMessage
{
protected:
	std::string _firstLine;
	std::string _httpVer;
	std::string _headers;
	std::string _msgBody;

	enum HttpMethod
	{
		GET = 42,
		POST,
		DELETE
	};

public:
	HttpMessage();
	HttpMessage(const HttpMessage&);
	~HttpMessage();

	HttpMessage& operator=(const HttpMessage&);

	std::string getHttpVer() const;
	std::string getHeaders() const;
	std::string getMsgBody() const;

	void setHttpVer(const std::string&);
	void setHeaders(const std::string&);
	void setMsgBody(const std::string&);
};

#endif