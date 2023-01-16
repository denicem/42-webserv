/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:14:46 by dmontema          #+#    #+#             */
/*   Updated: 2023/01/14 21:55:52 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "File.hpp"

#include <iostream>

/*
** ----------------------- PRIVATE METHODS -----------------------
*/

void File::calcFileSize(std::ifstream& file) {
	// calc the size of the file
	file.seekg(0, std::ios::end);
	this->file_size = file.tellg();

	// resets to beginning of the file
	file.clear();
	file.seekg(0);
}

void File::getContentFromFile(std::ifstream& file) {
	if (file.is_open()) {
		std::string text;
		while (!file.eof()) {
			std::getline(file, text);
			this->content.append(text);
			if (!file.eof())
				this->content.append("\n");
		}
	}
}

/*
** ----------------------- CONSTRUCTORS & DESTRUCTOR -----------------------
*/

File::File(): filename(""), path(""), content(""), file_size(0) {}
File::File(const File& other): filename(other.filename), path(other.path), content(other.content), file_size(other.file_size) {}

File::File(const std::string& path): path(path) {
	this->filename= this->path.substr(this->path.find_last_of('/') + 1);
	std::ifstream file (this->path.c_str());
	if (!file.is_open())
		throw FileNotFoundException();
	if (this->filename.find('.') == std::string::npos) { // TODO: find another solution
		file.close();
		throw FileNotFoundException();
	}
	this->calcFileSize(file);
	this->getContentFromFile(file);
	file.close();
}

File::File(const std::string& filename, const std::string& content): filename(filename), content(content), file_size(content.size()) {}
File::~File() {}

/*
** ----------------------- OPERATOR OVERLOADS -----------------------
*/

File& File::operator=(const File& other) {
	if(this != &other) {
		this->filename = other.filename;
		this->path = other.path;
		this->content = other.content;
		this->file_size = other.file_size;
	}
	return (*this);
}

/*
** ----------------------- GETTER AND SETTER METHODS -----------------------
*/

std::string File::getFilename() const {
	return (this->filename);
}

std::string File::getPath() const {
	return (this->path);
}

std::string File::getContent() const {
	return (this->content);
}

int File::getFileSize() const {
	return (this->file_size);
}


void File::setFilename(const std::string& filename) {
	this->filename = filename;
}

void File::setPath(const std::string& path) {
	this->path = path;
}

void File::setContent(const std::string& content) {
	this->content = content;
}

void File::setFileSize(const int& file_size) {
	this->file_size = file_size;
}

/*
** ----------------------- METHODS -----------------------
*/

/*
** ----------------------- EXCEPTIONS -----------------------
*/
