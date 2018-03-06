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

Sprite &createSprite(const std::string &name, const std::string &path,
		     const char &substitute)
{
	
}

std::string SpriteParser::findType(const std::string &line) noexcept
{
	std::string tmp = line;
	int place = tmp.find(":");
	if (place > 0) {
		tmp = tmp.substr(0, place);
	}
	return tmp;
}

std::string SpriteParser::findValue(const std::string &line) noexcept
{
	std::string tmp = line;

	int place = tmp.find(":") + 1;
	if (place > 1) {
		tmp = tmp.substr(place, tmp.length());
	}
	return tmp;
}

void SpriteParser::setName(const std::string &line) noexcept
{
}

void SpriteParser::readFile(const std::string &filename, std::vector<Sprite> &_vector)
{
	std::ifstream s(filename);
	std::string tmp;

	std::cout << "File: " << filename << std::endl;
	if (s.is_open()) {
		while (getline(s, tmp)) {
//			std::cout << tmp << std::endl;
			std::cout << findType(tmp) << std::endl;
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
		if (s->d_name[0] != '.') {
			tmp = folder + s->d_name;
			readFile(tmp, _vector);
		}
	}
	closedir(dirptr);
	return (_vector);
}
