//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// SpriteParser
//

#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include "Error.hpp"
#include "SpriteParser.hpp"

void SpriteParser::setName(const std::string &line) noexcept
{
}

void SpriteParser::ReadFile(const std::string &filename, std::vector<Sprite> &_vector)
{
	std::ifstream s(filename);
	std::string tmp;

	std::cout << "File: " << filename << std::endl;
	if (s.is_open()) {
		while (getline(s, tmp)) {
			std::cout << tmp << std::endl;
		}
	} else {
		std::string _s("Error: can't open '");
		_s += filename;
		_s += "'.";
		throw ParserError(_s);
	}
}

std::vector<Sprite> SpriteParser::Parser(const std::string &folder)
{
	DIR *dirptr = opendir(folder.c_str());
	struct dirent *s;
	std::string tmp;
	std::vector<Sprite> _vector;

	if (dirptr == NULL) {
		std::string _s("Error: Directory '");
		_s += folder;
		_s += "' does not exist";
		throw ParserError(_s);
	}
	while ((s = readdir(dirptr)) != NULL) {
		tmp = s->d_name;
		if (tmp[0] != '.')
			std::cout << tmp << std::endl;
	}
	closedir(dirptr);
	return (_vector);
}
