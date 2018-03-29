/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SolarFox
*/

#include <iostream>
#include <fstream>
#include "Arc.hpp"
#include "SolarFox.hpp"

const std::string
DEF_BULLETCONF = "tests/SpriteConfigurationFiles/Bullets.conf";

std::string arc::SolarFox::ItemParser::_line;
arc::SpriteList arc::SolarFox::ItemParser::_vector;
arc::Color arc::SolarFox::ItemParser::_color;
int arc::SolarFox::ItemParser::_nbrline;

arc::SolarFox::SolarFox()
	: _name("SolarFox"), _info({GRID_H, GRID_L, GRID_STEP, FPS})
{
	setItems("tests/SpriteConfigurationFiles/Wall.conf");
	setItems("tests/SpriteConfigurationFiles/SealConfigurationFile.conf");
	setItems("sprite/FruitConf.conf");
}

void arc::SolarFox::setItems(const std::string &path)
{
	std::ifstream s(path);
	std::string tmp;

	if (s.is_open()) {
		while (getline(s, SolarFox::ItemParser::_line))
			createItems();
	} else {
		throw ParserError("Error: can't open '" + path + "'.");
	}
}

void arc::SolarFox::createItems()
{
	if (ItemParser::_line.length() > 0 && ItemParser::_line[0] != '#') {
		if (ItemParser::getAttribute() == "UNIQUE")
			_items.push_back(ItemParser::createItem());
		else if (ItemParser::getAttribute() == "APPEND")
			createSprite();
	}
}

void arc::SolarFox::createSprite()
{
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == ItemParser::setName()) {
			i->sprites.push_back(ItemParser::createSprite());
			return;
		}
	}
	_items.push_back(ItemParser::createItem());
}

arc::Item arc::SolarFox::ItemParser::createItem()
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

arc::Item arc::SolarFox::ItemParser::createItem(const std::string &path, int x, int y)
{
	std::ifstream s(path);
	if (s.is_open()) {
		getline(s, SolarFox::ItemParser::_line);
	} else {
		throw ParserError("Error: can't open '" + path + "'.");
	}
	arc::Item tmp;
	tmp.name = setName();
	tmp.sprites.push_back(createSprite());
	tmp.spritesPath = setPath();
	tmp.x = x;
	tmp.y = y;
	tmp.currSpriteIdx = 0;
	return tmp;
}

void arc::SolarFox::dump() const noexcept
{
	std::cout << "Dumping game " << _name << "." << std::endl;
	std::cout << "Grid size: " << _info.x << "*" << _info.y;
	std::cout << "*" <<_info.pixelStep << std::endl;
	_dumpItems();
}

void arc::SolarFox::_dumpItems() const noexcept
{
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		std::cout << "Item: " << it->name << " -- Sprite count:";
		std::cout << it->sprites.size() << " -- Pos: " << it->x;
		std::cout << ", " << it->y << std::endl;
	}
}

using millisec = std::chrono::duration<double, std::milli>;

bool arc::SolarFox::_vectorIsCollided(Vectori a, Vectori b)
{
	int diffx = a.v_x - b.v_x;
	int diffy = a.v_y - b.v_y;

	diffx = std::abs(diffx);
	diffy = std::abs(diffy);
	if (diffx < GRID_STEP && diffy < GRID_STEP)
		return true;
	return false;
}

arc::Action arc::SolarFox::_vectorCollide(Item &item, Vectori pos)
{
	for (auto it = _items.begin(); it != _items.end(); it++) {
		if (it->name != item.name &&
			_vectorIsCollided(pos, (Vectori){it->x, it->y}))
			return BLOCK;
	}
	return DFT;
}

void arc::SolarFox::_itemMove(const std::string &name, Vectori mod)
{
	for (auto it = _items.begin(); it != _items.end(); it++) {
		if (it->name == name)
			_itemMove(*it, mod);
	}
}

void arc::SolarFox::_itemMove(Item &item, Vectori mod)
{
	Vectori newPos {item.x + mod.v_x, item.y + mod.v_y};

	if (_vectorCollide(item, newPos) != BLOCK) {
		item.x = newPos.v_x;
		item.y = newPos.v_y;
	}
}

void arc::SolarFox::proccessIteraction(Interaction &interact) noexcept
{
	auto move = MOVE_BINDS.find(interact);
	if (move != MOVE_BINDS.end()) {
		_itemMove("Seal" , move->second);
	} else {
	switch (interact)
	{
		case ACTION_1:
			shoot("Seal");
			break;
		default:
			break;
	}
	}
	if (interact == MOVE_LEFT || interact == MOVE_RIGHT || interact == MOVE_UP || interact == MOVE_DOWN)
		_keystate = interact;
}

void arc::SolarFox::shoot(const std::string &name)
{
	auto item = getItemFromName(name);
	ItemParser::createItem(DEF_BULLETCONF, item.x, item.y);
}

void arc::SolarFox::changeItemsPositionFromName(const std::string &name, int x, int y)
{
	auto finish = std::chrono::high_resolution_clock::now();
	millisec elapsed = finish - _startTime;
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == name) {
			i->x += x;
			i->y += y;
			if (elapsed.count() > 200) {
				if (i->currSpriteIdx > 4)
					i->currSpriteIdx = 0;
				else
				i->currSpriteIdx += 1;
				_startTime = std::chrono::high_resolution_clock::now();
			}
		}
	}
}

arc::Item &arc::SolarFox::getItemFromName(const std::string &name)
{
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == name)
			return *i;
	}
	return _items[0];
}

arc::SpriteList &arc::SolarFox::getSpriteListFromName(const std::string &name)
{

	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == name)
			return i->sprites;
	}
	return _items[0].sprites;
}

void arc::SolarFox::envUpdate() noexcept
{
}

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

static const arc::SolarFox::ItemParser::FlagMap _flagMap = {
	{"BLOCK", arc::Action::BLOCK},
	{"DIE", arc::Action::DIE},
	{"EAT", arc::Action::EAT},
	{"MOVE", arc::Action::MOVE},
	{"PLAYER", arc::Action::PLAYER},
};

static const arc::SolarFox::ItemParser::MapColor _mapColor = {
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

arc::Sprite arc::SolarFox::ItemParser::createSprite()
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

arc::Action arc::SolarFox::ItemParser::setFlag()
{
	for (auto i = _flagMap.begin() ; i != _flagMap.end() ; i++) {
		if (i->first == getInfo("Flag")) {
			return i->second;
		}
	}
	return arc::Action::DFT;
}

std::string arc::SolarFox::ItemParser::setName()
{
	return getInfo("Name");
}

arc::Color arc::SolarFox::ItemParser::setColor()
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

const std::string arc::SolarFox::ItemParser::getAttribute()
{
	return getInfo("Attribute");
}

std::string arc::SolarFox::ItemParser::setPath()
{
	return getInfo("Path");
}

char arc::SolarFox::ItemParser::setSubstitute()
{
	std::string tmp = getInfo("Substitute");

	if (tmp.length() > 1)
		throw ParserError(arc::ERR_SUB);
	return tmp[0];
}

int arc::SolarFox::ItemParser::getIndex(const std::string &what)
{
	for (auto i = COREMAP.begin(); i != COREMAP.end(); i++) {
		if (what == i->first)
			return i->second;
	}
	return -1;
}

std::string arc::SolarFox::ItemParser::getInfo(const std::string &what)
{
	std::string tmp = _line;

	for (int i = 0; i < getIndex(what); i ++) {
		tmp = tmp.substr(tmp.find(":") + 1, tmp.length());
	}
	tmp = tmp.substr(0, tmp.find(":"));
	return tmp;
}
