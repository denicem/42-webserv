/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:14:46 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/11 17:55:26 by dmontema         ###   ########.fr       */
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
			this->content.append(text);
			if (!file.eof())
				this->content.append("\n");
		}
	}
}

void File::calcFileSize(std::ifstream& file)
{
	// calc the size of the file
	file.seekg(0, std::ios::end);
	this->fileSize = file.tellg();

	// resets to beginning of the file
	file.clear();
	file.seekg(0);
}

void File::changeToRootOrFavicon()
{
	if (this->path == "/")
		this->path = "/index.html";
	else if (this->path.find("favicon.ico") != std::string::npos)
		this->path = "/favicon.ico";
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

File::File(): filename(""), path(""), content(""), fileSize(0), isLocation(false) {}
File::File(const File& other): filename(other.filename), path(other.path), content(other.content), fileSize(other.fileSize), isLocation(other.isLocation) {}

File::File(const std::string& path): path(path)
{
	std::ifstream file (this->path.c_str());
	if (!file.is_open())
		throw FileNotFoundException();
	this->filename= this->path.substr(this->path.find_last_of('/') + 1);
	this->calcFileSize(file);
	this->getContentFromFile(file);
}

File::File(const std::string& path, const std::string& dest): filename(dest), path(path)
{
	std::ifstream file(path.c_str());
	if (!file.is_open())
		throw FileNotFoundException();
	this->calcFileSize(file);
	this->getContentFromFile(file);
	std::cout << "File: " << this->path << std::endl;
}

File::~File() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

File& File::operator=(const File& other)
{
	if(this != &other)
	{
		this->filename = other.filename;
		this->path = other.path;
		this->content = other.content;
		this->fileSize = other.fileSize;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

std::string File::getFilename() const
{
	return (this->filename);
}

std::string File::getPath() const
{
	return (this->path);
}

std::string File::getContent() const
{
	return (this->content);
}

int File::getFileSize() const
{
	return (this->fileSize);
}


void File::setFilename(const std::string& filename)
{
	this->filename = filename;
}

void File::setPath(const std::string& path)
{
	this->path = path;
}

void File::setContent(const std::string& content)
{
	this->content = content;
}

void File::setFileSize(const int& fileSize)
{
	this->fileSize = fileSize;
}

/*
** ----------------------- METHODS -----------------------
*/

/*
** ----------------------- EXCEPTIONS -----------------------
*/
