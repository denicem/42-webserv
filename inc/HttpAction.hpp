/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:07:07 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/29 02:33:56 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_ACTION_HPP
#define HTTP_ACTION_HPP

#include "HttpMessage.hpp"
#include "HttpRequest.hpp"
#include "File.hpp"

class HttpAction: public HttpMessage {
	private:
	public:
		HttpAction();
		HttpAction(const HttpAction&);
		HttpAction(const HttpRequest&);
		~HttpAction();

		HttpAction& operator=(const HttpAction&);
};

#endif
