/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMethod.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:35:14 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/16 02:31:57 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_METHOD_HPP
#define HTTP_METHOD_HPP

#include <string>

enum HttpMethod {
	METHOD_UNDEFINED = -1,
	GET,
	POST,
	DELETE
};

std::string getHttpMethodStr(const HttpMethod&);

#endif