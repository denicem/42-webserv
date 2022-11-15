/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:14:46 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/15 01:33:16 by dmontema         ###   ########.fr       */
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

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

File::File(): _content(""), _fileSize(0) {}
File::File(const File& other): _content(other._content), _fileSize(other._fileSize) {}

File::File(const std::string& pathfile): _pathfile(pathfile)
{
	if (this->_pathfile == "/")
		this->_pathfile = "/index.html";
	if (this->_pathfile.find("favicon.ico") != std::string::npos)
		this->_pathfile = "/favicon.ico";
	// std::cout << this->_pathfile << std::endl;

	std::ifstream file("html" + this->_pathfile);

	if (!file.is_open())
		throw std::exception();

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
		this->_content = other._content;
		this->_fileSize = other._fileSize;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

std::string File::getPathfile() const
{
	return (this->_pathfile);
}

std::string File::getContent() const
{
	return (this->_content);
}

int File::getFileSize() const
{
	return (this->_fileSize);
}


void File::setPathfile(const std::string& pathfile)
{
	this->_pathfile = pathfile;
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