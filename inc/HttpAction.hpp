/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpAction.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:07:07 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 22:38:32 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_ACTION_HPP
#define HTTP_ACTION_HPP

#define DEF_ERROR_PAGE_400 "./error/400.html"
#define DEF_ERROR_PAGE_404 "./error/404.html"
#define DEF_ERROR_PAGE_405 "./error/405.html"
#define DEF_ERROR_PAGE_501 "./error/501.html"
#define DEF_ERROR_PAGE_542 "./error/542.html"

#include "File.hpp"
#include "HttpMessage.hpp"
#include "HttpMethod.hpp"
#include "HttpRequest.hpp"
#include "Server.hpp"
#include "dirListing.hpp"
#include "CGI.hpp"

class CGI;

class HttpAction: public HttpMessage {
	private:
		HttpMethod http_method;
		int status_code;
		File file;

		std::string path_req, path, dest;
		int route_index;
		std::string http_redirect;
		dirListing dir_list;

		/* for cgi */
		bool is_cgi;
		CGI cgi;
		std::string	cgi_response;
		std::string query;
		/* */

		std::string upload_filename, upload_body;

	public:
		HttpAction();
		HttpAction(const HttpAction&);
		HttpAction(HttpRequest&, const Server&);
		~HttpAction();

		HttpAction& operator=(const HttpAction&);

		HttpMethod getHttpMethod() const;
		int getStatusCode() const;
		File getFile() const;

		void doAction(const Server&);

	private:
		void setupErrorPage(int status_code, const Server&);
		std::string getDefaultErrorPage(int) const;

		void setPath(const HttpRequest&, const Server&);
		int getRouteIndex(const std::string&, const Server&) const;
		void checkHttpRedirection(const Server&);

		bool isMethodAllowed(const int, const Route&) const;

		void actGet(const Server&);
		void actPost(const Server&);
		void actDelete(const Server&);

		void extractMsgBody();
		std::string randomNameGen() const;
};

#endif
