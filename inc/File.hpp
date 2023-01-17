/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:53:54 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 03:24:37 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <fstream>
#include <exception>

class File {
	private:
		std::string file_name;
		std::string path;
		std::string content;
		int file_size;

	public:
		File();
		File(const File&);
		File(const std::string&);
		File(const std::string&, const std::string&);
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

	private:
		void calcFileSize(std::ifstream&);
		void getContentFromFile(std::ifstream&);

	public:
		class FileNotFoundException: public std::exception {};
};

#endif
