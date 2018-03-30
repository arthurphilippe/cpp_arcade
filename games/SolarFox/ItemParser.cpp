/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** ItemParser
*/

#include <iostream>
#include <fstream>
#include "SolarFox.hpp"

std::string arc::ItemParser::_line;
arc::SpriteList arc::ItemParser::_vector;
arc::Color arc::ItemParser::_color;
int arc::ItemParser::_nbrline;

static const arc::ItemParser::AttributeMap _attributeMap = {
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

static const std::unordered_map<std::string, int> COREMAP = {
	{"Name", 0},
	{"X", 1},
	{"Y", 2},
	{"Rotation", 3},
	{"Substitute", 4},
	{"Color", 5},
	{"Attribute", 6},
	{"Flag", 7},
	{"Path", 8},
};

arc::Item arc::ItemParser::createItem()
{
	arc::Item tmp;
	tmp.name = setName();
	tmp.sprites.push_back(createSprite());
	tmp.spritesPath = setPath();
	tmp.x = std::stoi(getInfo("X"));
	tmp.y = std::stoi(getInfo("Y"));
	tmp.currSpriteIdx = 0;
	return tmp;
}

arc::Item arc::ItemParser::createItem(const std::string &path, int x, int y)
{
	std::ifstream s(path);
	if (s.is_open()) {
		getline(s, ItemParser::_line);
	} else {
		throw ParserError("Error: can't open '" + path + "'.");
	}
	arc::Item tmp;
	tmp.name = setName();
	tmp.sprites.push_back(createSprite());
	tmp.spritesPath = setPath();
	tmp.x = x;
	tmp.y = y;
	tmp.attribute = setAttribute();
	tmp.currSpriteIdx = 0;
	return tmp;
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
	return tmp;
}

arc::Attribute arc::ItemParser::setAttribute()
{
	for (auto i = _attributeMap.begin() ; i != _attributeMap.end() ; i++) {
		if (i->first == getInfo("Attribute")) {
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

const std::string arc::ItemParser::getFlag()
{
	return getInfo("Flag");
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
