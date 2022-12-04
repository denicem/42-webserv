/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:07:07 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/04 22:08:03 by dmontema         ###   ########.fr       */
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

	private:
		void initVars(const HttpRequest&);
		bool isMethodAllowed(const int, const Location&) const;

	public:
		HttpAction();
		HttpAction(const HttpAction&);
		HttpAction(const HttpRequest&, const Server&);
		~HttpAction();

		HttpMethod getHttpMethod() const;
		int getStatusCode() const;
		File getFile() const;

		HttpAction& operator=(const HttpAction&);
};

#endif
