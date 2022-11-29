/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMethod.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:36:28 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/29 01:39:33 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpMethod.hpp"

#include <string>

std::string getHttpMethodStr(HttpMethod& method) {
	switch (method) {
		case GET: return ("GET");
		case POST: return ("POST");
		case DELETE: return ("DELETE");
		default: return ("undefined");
	}
}