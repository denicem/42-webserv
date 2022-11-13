/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:14:46 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/10 22:59:43 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/File.hpp"
#include <fstream>

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

File::File(const std::string& filename)
{
	std::ifstream file("html" + filename, std::ios::binary);

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

std::string File::getContent() const
{
	return (this->_content);
}

int File::getFileSize() const
{
	return (this->_fileSize);
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