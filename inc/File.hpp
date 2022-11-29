/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:53:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/29 17:43:58 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
#define FILE_HPP

#include "HttpRequest.hpp"
#include "Server.hpp"

#include <string>
#include <fstream>
#include <exception>

class File {
	private:
		std::string filename;
		std::string path;
		std::string content;
		int fileSize;
		bool isLocation;

	private:
		void getContentFromFile(std::ifstream&);
		void calcFileSize(std::ifstream&);
		void changeToRootOrFavicon();

	public:
		File();
		File(const File&);
		File(const std::string&);
		File(const std::string&, const Server&, int, bool);
		File(const HttpRequest&, const Server&, int, bool);
		~File();

		File& operator=(const File&);

		std::string getFilename() const;
		std::string getPath() const;
		std::string getContent() const;
		int getFileSize() const;

		void setFilename(const std::string&);
		void setPath(const std::string&);
		void setContent(const std::string&);
		void setFileSize(const int&);

		class FileNotFoundException: public std::exception {};
};

#endif