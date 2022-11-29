/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:43:33 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/29 13:51:10 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include "HttpMessage.hpp"
#include "HttpRequest.hpp"
#include "File.hpp"
#include "Server.hpp"

class HttpResponse: public HttpMessage {
	private:
		int statusCode;
		File file;

	private:
		bool isMethodAllowed(const int, const Location&) const;
		std::string getStatusMsg() const;

	public:
		HttpResponse();
		HttpResponse(const HttpResponse&);
		HttpResponse(const std::string&);
		HttpResponse(const HttpRequest&);
		HttpResponse(const HttpRequest&, const Server&);
		~HttpResponse();

		HttpResponse& operator=(const HttpResponse&);

		int getStatusCode() const;

		void setStatusCode(const int&);

		std::string genHttpResponseMsg(const HttpRequest&) const;

		friend std::ostream& operator<<(std::ostream&, const HttpResponse&);
};

#endif