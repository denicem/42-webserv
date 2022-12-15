/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMethod.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:35:14 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/13 15:16:39 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_METHOD_HPP
#define HTTP_METHOD_HPP

#include <string>

enum HttpMethod {
	GET,
	POST,
	DELETE
};

std::string getHttpMethodStr(const HttpMethod&);

#endif