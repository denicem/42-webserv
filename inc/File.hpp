/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   File.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontema <dmontema@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:53:54 by dmontema          #+#    #+#             */
/*   Updated: 2022/11/10 20:34:58 by dmontema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <fstream>

class File
{
private:
	std::string _content;
	int _fileSize;

public:
	File();
	File(const File&);
	File(const std::string&);
	~File();

	File& operator=(const File&);

	std::string getContent() const;
	int getFileSize() const;

	void setContent(const std::string&);
	void setFileSize(const int&);

private:
	void getContentFromFile(std::ifstream&);
	void calcFileSize(std::ifstream&);
};

#endif