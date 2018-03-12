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

std::string arc::SpriteParser::_line;
arc::SpriteList arc::SpriteParser::_vector;
int arc::SpriteParser::_nbrline;
arc::Color _color;

static const arc::SpriteParser::MapColor _mapColor = {
	{"BLUE", arc::Color::BLUE},
	{"RED", arc::Color::RED},
	{"GREEN", arc::Color::GREEN},
	{"BLACK", arc::Color::BLACK},
	{"YELLOW", arc::Color::YELLOW},
	{"CYAN", arc::Color::CYAN},
	{"MAGENTA", arc::Color::MAGENTA},
	{"WHITE", arc::Color::WHITE},
	{"BLACK", arc::Color::BLACK},
	{"UNDEFINED", arc::Color::UNDEFINED},
};


const std::string &arc::SpriteParser::getErrorLine()
{
	return (_line);
}

const int &arc::SpriteParser::getErrorLineNb()
{
	return (_nbrline);
}

arc::Sprite arc::SpriteParser::createSprite(
	const std::string &path, const char &substitute,
	const std::string &name)
{
	Sprite tmp(name, path, substitute);

	tmp.setColor(setColor());
	return tmp;
}

std::string arc::SpriteParser::setName()
{
	std::string tmp = _line;
	size_t tokenplace;

	if ((tokenplace = tmp.find(':')) == std::string::npos)
		throw ParserError(arc::ERR_NAME);
	tmp = tmp.substr(0, tokenplace);
	return tmp;
}

arc::Color arc::SpriteParser::setColor()
{
	std::string tmp = _line;
	arc::Color color = arc::Color::DFT_COLOR_RET_ERROR;

	for (int i = 0; i != 2; i++)
		tmp = tmp.substr(tmp.find_first_of(":") + 1, tmp.find_last_of(":"));
	tmp = tmp.substr(0, tmp.find(":"));
	for (auto i = _mapColor.begin(); i != _mapColor.end(); i++) {
		if (i->first == tmp)
			color = i->second;
	}
	if (color == arc::Color::DFT_COLOR_RET_ERROR)
		throw ParserError(ERR_COLOR);
	return color;
}

std::string arc::SpriteParser::setPath()
{
	std::string tmp = _line;

	tmp = tmp.substr(tmp.find_last_of(":", tmp.length()) + 1, tmp.length());
	if (access(tmp.c_str(), R_OK) == -1 || tmp == _line)
		throw ParserError(arc::ERR_PATH);
	return tmp;
}

char arc::SpriteParser::setSubstitute()
{
	std::string tmp = _line;

	tmp = tmp.substr(tmp.find(":") + 1, tmp.length());
	tmp = tmp.substr(0, tmp.find(":"));
	if (tmp.length() > 1)
		throw ParserError(arc::ERR_SUB);
	return tmp[0];
}

void arc::SpriteParser::parseLine()
{
	if (_line.length() > 0 && _line[0] != '#')
		_vector.push_back(createSprite(setPath(),
						setSubstitute(),
						setName()));
	_nbrline += 1;
}

void arc::SpriteParser::readFile(const std::string &filename)
{
	std::ifstream s(filename);
	std::string tmp;

	if (s.is_open()) {
		while (getline(s, _line)) {
			parseLine();
		}
	} else {
		std::string _s("Error: can't open '");
		_s += filename;
		_s += "'.";
		throw ParserError(_s);
	}
}

arc::SpriteList arc::SpriteParser::parser(const std::string &filename)
{
	_line.clear();
	_vector.clear();
	_nbrline = 1;
	readFile(filename);
	return _vector;
}
