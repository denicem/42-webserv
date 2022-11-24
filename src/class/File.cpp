/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:14:46 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/16 21:53:58 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

#include <fstream>
#include <iostream>

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void File::getContentFromFile(std::ifstream& file)
{
	if (file.is_open())
	{
		std::string text;
		while (!file.eof())
		{
			std::getline(file, text);
			this->_content.append(text);
			if (!file.eof())
				this->_content.append("\n");
		}
	}
}

void File::calcFileSize(std::ifstream& file)
{
	// calc the size of the file
	file.seekg(0, std::ios::end);
	this->_fileSize = file.tellg();

	// resets to beginning of the file
	file.clear();
	file.seekg(0);
}

void File::changeToRootOrFavicon()
{
	if (this->_path == "/")
		this->_path = "/index.html";
	else if (this->_path.find("favicon.ico") != std::string::npos)
		this->_path = "/favicon.ico";
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

File::File(): _content(""), _fileSize(0) {}
File::File(const File& other):_filename(other._filename), _path(other._path), _content(other._content), _fileSize(other._fileSize) {}

File::File(const std::string& path): _path(path)
{
	this->changeToRootOrFavicon();
	std::ifstream file ("html" + this->_path);
	if (!file.is_open())
		throw FileNotFoundException();
	this->_filename= this->_path.substr(this->_path.find_last_of('/') + 1);
	this->calcFileSize(file);
	this->getContentFromFile(file);
}

File::~File() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

File& File::operator=(const File& other)
{
	if(this != &other)
	{
		this->_filename = other._filename;
		this->_path = other._path;
		this->_content = other._content;
		this->_fileSize = other._fileSize;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

std::string File::getFilename() const
{
	return (this->_filename);
}

std::string File::getPath() const
{
	return (this->_path);
}

std::string File::getContent() const
{
	return (this->_content);
}

int File::getFileSize() const
{
	return (this->_fileSize);
}


void File::setFilename(const std::string& filename)
{
	this->_filename = filename;
}

void File::setPath(const std::string& path)
{
	this->_path = path;
}

void File::setContent(const std::string& content)
{
	this->_content = content;
}

void File::setFileSize(const int& fileSize)
{
	this->_fileSize = fileSize;
}

/*
** ----------------------- METHODS -----------------------
*/

/*
** ----------------------- CLASS ATTRIBUTES -----------------------
*/

/*
** ----------------------- CLASS METHODS -----------------------
*/

/*
** ----------------------- FUNCS -----------------------
*/