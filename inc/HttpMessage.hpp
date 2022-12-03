/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMessage.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:11:57 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/03 17:51:30 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_MESSAGE_HPP
#define HTTP_MESSAGE_HPP

#include <string>
#include <map>

class HttpMessage {
	protected:
		std::string firstLine;
		std::string httpVer;
		std::map<std::string, std::string> headers;
		std::string msgBody;

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