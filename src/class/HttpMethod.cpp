/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:36:28 by dmontema          #+#    #+#             */
/*   Updated: 2022/12/13 15:16:34 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpMethod.hpp"

#include <string>

std::string getHttpMethodStr(const HttpMethod& method) {
	switch (method) {
		case GET: return ("GET");
		case POST: return ("POST");
		case DELETE: return ("DELETE");
		default: return ("undefined");
	}
}