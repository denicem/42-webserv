/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpMethod.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 01:35:14 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/29 01:38:44 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

enum HttpMethod {
	GET = 42,
	POST,
	DELETE
};

std::string getHttpMethodStr(HttpMethod&);