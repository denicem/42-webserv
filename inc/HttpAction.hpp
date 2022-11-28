/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:07:07 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/22 17:17:18 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPACTION_HPP
#define HTTPACTION_HPP

#include "HttpMessage.hpp"
#include "HttpRequest.hpp"
#include "File.hpp"

class HttpAction: public HttpMessage
{
private:
	
public:
	HttpAction();
	HttpAction(const HttpAction&);
	HttpAction(const HttpRequest&);
	~HttpAction();

	HttpAction& operator=(const HttpAction&);

};

#endif

