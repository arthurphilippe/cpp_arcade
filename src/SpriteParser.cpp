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

static const std::unordered_map<std::string, int> COREMAP = {
        {"Name", 0},
        {"X", 1},
        {"Y", 2},
        {"Rotation", 3},
        {"Substitute", 4},
        {"Color", 5},
        {"Path", 6},
};

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

arc::Sprite arc::SpriteParser::createSprite()
{
	Sprite tmp(setName(), setPath(), setSubstitute());
	tmp.setX(std::stoi(getInfo("X")));
	tmp.setY(std::stoi(getInfo("Y")));
	tmp.setRotation(std::stoi(getInfo("Rotation")));
	tmp.setColor(setColor());
	return tmp;
}

std::string arc::SpriteParser::setName()
{
	return getInfo("Name");
}

arc::Color arc::SpriteParser::setColor()
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

std::string arc::SpriteParser::setPath()
{
	return getInfo("Path");
}

char arc::SpriteParser::setSubstitute()
{
	std::string tmp = getInfo("Substitute");

	if (tmp.length() > 1)
		throw ParserError(arc::ERR_SUB);
	return tmp[0];
}

void arc::SpriteParser::parseLine()
{
	if (_line.length() > 0 && _line[0] != '#')
		_vector.push_back(createSprite());
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


int arc::SpriteParser::getIndex(const std::string &what)
{
        for (auto i = COREMAP.begin(); i != COREMAP.end(); i++) {
                if (what == i->first)
                        return i->second;
        }
        return -1;
}

std::string arc::SpriteParser::getInfo(const std::string &what)
{
        std::string tmp = _line;

        for (int i = 0; i < getIndex(what); i ++) {
                tmp = tmp.substr(tmp.find(":") + 1, tmp.length());
        }
        tmp = tmp.substr(0, tmp.find(":"));
        return tmp;
}

arc::SpriteList arc::SpriteParser::parser(const std::string &filename)
{
	_line.clear();
	_vector.clear();
	_nbrline = 1;
	readFile(filename);
	return _vector;
}
