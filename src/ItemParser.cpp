//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// ItemParser
//

#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include "Error.hpp"
#include "ItemParser.hpp"

std::string arc::ItemParser::_line;
arc::SpriteList arc::ItemParser::_vector;
int arc::ItemParser::_nbrline;
arc::Color arc::ItemParser::_color;

static const std::unordered_map<std::string, int> COREMAP = {
	{"Name", 0},
	{"X", 1},
	{"Y", 2},
	{"Rotation", 3},
	{"Substitute", 4},
	{"Color", 5},
	{"Flag", 6},
	{"Attribute", 7},
	{"Path", 8},
};

static const arc::ItemParser::FlagMap _flagMap = {
	{"BLOCK", arc::Attribute::BLOCK},
	{"FOE", arc::Attribute::FOE},
	{"DROP", arc::Attribute::DROP},
	{"MOVE", arc::Attribute::MOVE},
	{"PLAYER", arc::Attribute::PLAYER},
};

static const arc::ItemParser::MapColor _mapColor = {
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


const std::string &arc::ItemParser::getErrorLine()
{
	return (_line);
}

const int &arc::ItemParser::getErrorLineNb()
{
	return (_nbrline);
}

arc::Sprite arc::ItemParser::createSprite()
{
	Sprite tmp;
	tmp.name = setName();
	tmp.path = setPath();
	tmp.substitute = setSubstitute();
	tmp.x = std::stoi(getInfo("X"));
	tmp.y = std::stoi(getInfo("Y"));
	tmp.rotation = std::stoi(getInfo("Rotation"));
	tmp.color = setColor();
	tmp.flag = setFlag();
	return tmp;
}

arc::Attribute arc::ItemParser::setFlag()
{
	for (auto i = _flagMap.begin() ; i != _flagMap.end() ; i++) {
		if (i->first == getInfo("Flag")) {
			return i->second;
		}
	}
	return arc::Attribute::UNK;
}

std::string arc::ItemParser::setName()
{
	return getInfo("Name");
}

arc::Color arc::ItemParser::setColor()
{
	std::string tmp = getInfo("Color");
	arc::Color color = arc::Color::DFT_COLOR_RET_ERROR;

	for (auto i = _mapColor.begin(); i != _mapColor.end(); i++) {
		if (i->first == tmp)
			color = i->second;
	}
	if (color == arc::Color::DFT_COLOR_RET_ERROR)
		throw ParserError(ERR_COLOR);
	return color;
}

const std::string arc::ItemParser::getAttribute()
{
	return getInfo("Attribute");
}

std::string arc::ItemParser::setPath()
{
	return getInfo("Path");
}

char arc::ItemParser::setSubstitute()
{
	std::string tmp = getInfo("Substitute");

	if (tmp.length() > 1)
		throw ParserError(arc::ERR_SUB);
	return tmp[0];
}

void arc::ItemParser::parseLine()
{
	if (_line.length() > 0 && _line[0] != '#')
		_vector.push_back(createSprite());
	_nbrline += 1;
}

void arc::ItemParser::readFile(const std::string &filename)
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

int arc::ItemParser::getIndex(const std::string &what)
{
	for (auto i = COREMAP.begin(); i != COREMAP.end(); i++) {
		if (what == i->first)
			return i->second;
	}
	return -1;
}

std::string arc::ItemParser::getInfo(const std::string &what)
{
	std::string tmp = _line;

	for (int i = 0; i < getIndex(what); i ++) {
		tmp = tmp.substr(tmp.find(":") + 1, tmp.length());
	}
	tmp = tmp.substr(0, tmp.find(":"));
	return tmp;
}

arc::SpriteList arc::ItemParser::parser(const std::string &filename)
{
	_line.clear();
	_vector.clear();
	_nbrline = 1;
	readFile(filename);
	return _vector;
}
