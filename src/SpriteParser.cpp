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
		     const char &substitute, std::vector<Sprite> _vector) noexcept
{
	Sprite tmp(name, path, substitute);

	_vector.push_back(tmp);
	return tmp;
}

void &SpriteParser::setName(const std::string &line) noexcept
{
	std::string tmp = line;

	if (tmp.find(":") == std::string::npos)
		throw ParserError(
			"Error: Configuration File Have a Error On This Line:",
			line, "");
	tmp = tmp(0, 
}

std::string SpriteParser::parseLine(
	const std::string &line, std::vector<Sprite> _vector) noexcept
{
	std::string name = getName(line);
	int place = tmp.find(":") + 1;
	if (place > 1) {
		tmp = tmp.substr(place, tmp.length());
	}
	return tmp;
}

void SpriteParser::readFile(const std::string &filename, std::vector<Sprite> &_vector)
{
	std::ifstream s(filename);
	std::string tmp;

	std::cout << "File: " << filename << std::endl;
	if (s.is_open()) {
		while (getline(s, tmp)) {
			if (tmp[0] != '#')
				parseLine(tmp, _vector);
		}
	} else {
		std::string _s("Error: can't open '");
		_s += filename;
		_s += "'.";
		throw ParserError(_s);
	}
}

std::string SpriteParser::modifyFolder(std::string foldername)
{
	if (foldername.length() > 1 && (foldername[foldername.length() - 1] != '/' ||
					foldername[foldername.length() - 1] != '\\'))
		foldername += '/';
	return foldername;
}

std::vector<Sprite> SpriteParser::Parser(const std::string &folder)
{
	std::vector<Sprite> _vector;
	readFile(folder, _vector);
	return _vector;
}

// std::vector<Sprite> SpriteParser::Parser(const std::string &folder)
// {
// 	struct dirent *s;
// 	std::string tmp;
// 	std::vector<Sprite> _vector;

// 	std::string foldername = modifyFolder(folder);
// 	DIR *dirptr = opendir(foldername.c_str());
// 	if (dirptr == NULL) {
// 		std::string _s("Error: Directory '");
// 		_s += foldername;
// 		_s += "' does not exist";
// 		throw ParserError(_s);
// 	}
// 	while ((s = readdir(dirptr)) != NULL) {
// 		if (s->d_name[0] != '.') {
// 			tmp = foldername + s->d_name;
// 			readFile(tmp, _vector);
// 		}
// 	}
// 	closedir(dirptr);
// 	return (_vector);
// }
