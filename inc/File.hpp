/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:53:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/28 18:19:12 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
#define FILE_HPP

#include "Server.hpp"

#include <string>
#include <fstream>
#include <exception>

class File
{
private:
	std::string _filename;
	std::string _path;
	bool isLocation;
	std::string _content;
	int _fileSize;

public:
	File();
	File(const File&);
	File(const std::string&);
	File(const std::string&, const Server&, int, bool);
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

private:
	void getContentFromFile(std::ifstream&);
	void calcFileSize(std::ifstream&);
	void changeToRootOrFavicon();
};

#endif