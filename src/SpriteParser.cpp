//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// SpriteParser
//

#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include "Error.hpp"
#include "SpriteParser.hpp"

Sprite SpriteParser::createSprite(const std::string &name, const std::string &path,
		     const char &substitute, std::vector<Sprite> &_vector) noexcept
{
	Sprite tmp(name, path, substitute);

	_vector.push_back(tmp);
	return tmp;
}

std::string SpriteParser::setName(const std::string &line)
{
	std::string tmp = line;
        size_t tokenplace;

	if ((tokenplace = tmp.find(":")) == std::string::npos)
		throw ParserError(
			"Error: Configuration File Have a Error On This Line: '",
			line, "'");
	tmp = tmp.substr(0, tokenplace);
	return tmp;
}

std::string SpriteParser::setPath(const std::string &line)
{
	std::string tmp = line;

	tmp = tmp.substr(tmp.find_last_of(":", tmp.length()) + 1, tmp.length());
	if (access(tmp.c_str(), R_OK) == -1 || tmp == line)
		throw ParserError(
			"Error: Configuration File have a Error On This Line: '",
			line, "', can't access to the indicated path");
	return tmp;
}

char SpriteParser::setSubstitute(const std::string &line)
{
	std::string tmp = line;

	tmp = tmp.substr(tmp.find(":") + 1, tmp.length());
	tmp = tmp.substr(0, tmp.find(":"));
	if (tmp.length() > 1)
		throw ParserError(
			"Error: Configuration File have a Error On This Line: '",
			line, "', the substitute character must contain a single char");
	return tmp[0];
}

void SpriteParser::readFile(const std::string &filename, std::vector<Sprite> &_vector)
{
	std::ifstream s(filename);
	std::string tmp;

	std::cout << "File: " << filename << std::endl;
	if (s.is_open()) {
		while (getline(s, tmp)) {
			if (tmp.length() > 0 && tmp[0] != '#')
				createSprite(
					setName(tmp), setPath(tmp),
					setSubstitute(tmp), _vector);
		}
	} else {
		std::string _s("Error: can't open '");
		_s += filename;
		_s += "'.";
		throw ParserError(_s);
	}
}

std::vector<Sprite> SpriteParser::parser(const std::string &filename)
{
	std::vector<Sprite> _vector;
	readFile(filename, _vector);
	return _vector;
}
