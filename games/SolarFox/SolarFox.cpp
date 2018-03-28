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

std::string arc::SolarFox::ItemParser::_line;
arc::SpriteList arc::SolarFox::ItemParser::_vector;
arc::Color arc::SolarFox::ItemParser::_color;
int arc::SolarFox::ItemParser::_nbrline;

arc::SolarFox::SolarFox()
	: _name("SolarFox"), _info({GRID_H, GRID_L, GRID_STEP, FPS})
{
	setItems("tests/SpriteConfigurationFiles/Wall.conf");
	setItems("tests/SpriteConfigurationFiles/Bullets.conf");
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
	std::cout << tmp.name << std::endl;
	tmp.sprites.push_back(createSprite());
	tmp.spritesPath = setPath();
	tmp.x = std::stoi(getInfo("X"));
	tmp.y = std::stoi(getInfo("Y"));
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

arc::Action arc::SolarFox::canMoveDirectionY(const Sprite &sprite, const int &y,const std::string &name)
{
	if (y == 1)
	{
		for (auto i = _items.begin(); i != _items.end(); i++) {
			for (auto z = i->sprites.begin(); z != i->sprites.end(); z++) {
				if ((z->x >= sprite.x - GRID_STEP / 2
					&& z->x <= sprite.x + GRID_STEP / 2)
					&& z->y - sprite.y <= (GRID_STEP) && z->y - sprite.y >= 0
				&& z->name != name) {
					 return arc::Action::BLOCK;
				 }
			}
		}
	}
	if (y == -1)
	{
		for (auto i = _items.begin(); i != _items.end(); i++) {
			for (auto z = i->sprites.begin(); z != i->sprites.end(); z++) {
				if ((z->x >= sprite.x - GRID_STEP / 2
				&& z->x <= sprite.x + GRID_STEP / 2)
				&& z->y - sprite.y >= (0 - GRID_STEP) && z->y - sprite.y <= 0
				&& z->name != name) {
					 return arc::Action::BLOCK;
				}
			}
		}
	}
	return arc::Action::MOVE;
}


arc::Action arc::SolarFox::canMoveDirectionX(const Sprite &sprite, const int &x, const std::string &name)
{
	if (x == 1)
	{
		for (auto i = _items.begin(); i != _items.end(); i++) {
			for (auto z = i->sprites.begin(); z != i->sprites.end(); z++) {
				if ((z->y >= sprite.y - GRID_STEP / 2
				&& z->y <= sprite.y + GRID_STEP / 2)
				&& z->x - sprite.x <= (GRID_STEP) && z->x - sprite.x >= 0
				&& z->name != name) {
					 return arc::Action::BLOCK;
				}
			}
		}
	}
	if (x == -1)
	{
		for (auto i = _items.begin(); i != _items.end(); i++) {
			for (auto z = i->sprites.begin(); z != i->sprites.end(); z++) {
				if ((z->y >= sprite.y - GRID_STEP / 2
				&& z->y <= sprite.y + GRID_STEP / 2)
				&& z->x - sprite.x >= (0 - GRID_STEP) && z->x - sprite.x <= 0
				&& z->name != name) {
					 return arc::Action::BLOCK;
				}
			}
		}
	}
	return arc::Action::MOVE;
}

arc::Action arc::SolarFox::moveDirectionPars(arc::Item item, const struct Position &pos, const std::string &name)
{
	if (pos.x != 0)
		return canMoveDirectionX(item.sprites[0], pos.x, name);
	else if (pos.y != 0)
		return canMoveDirectionY(item.sprites[0], pos.y, name);
	return arc::Action::MOVE;
}

arc::Action arc::SolarFox::canMove(const std::string &name, int x, int y)
{
	auto item = getItemFromName(name);
	struct Position pos;
	pos.x = x;
	pos.y = y;
	return moveDirectionPars(item, pos, name);
}

void arc::SolarFox::proccessIteraction(Interaction &interact) noexcept
{
	switch (interact) {
	case MOVE_LEFT:
		if (canMove("Seal", -1, 0) != arc::Action::BLOCK)
		changeItemsPositionFromName("Seal", -1, 0);
		break;
	case MOVE_RIGHT:
		if (canMove("Seal", 1, 0) != arc::Action::BLOCK)
			changeItemsPositionFromName("Seal", 1, 0);
		break;
	case MOVE_UP:
		if (canMove("Seal", 0, -1) != arc::Action::BLOCK)
		changeItemsPositionFromName("Seal", 0, -1);
		break;
	case MOVE_DOWN:
		if (canMove("Seal", 0, 1) != arc::Action::BLOCK)
		changeItemsPositionFromName("Seal", 0, 1);
		break;
	case ACTION_1:
		shoot("Seal");
		break;
	default:
		break;
	}
	if (interact == MOVE_LEFT || interact == MOVE_RIGHT || interact == MOVE_UP || interact == MOVE_DOWN)
		_keystate = interact;
}

void arc::SolarFox::shoot(const std::string &name)
{
	auto mainchar = getItemFromName(name);
	auto splist = mainchar.sprites;
        struct Position tmp;
	for (auto i = _bulletpos.begin(); i != _bulletpos.end(); i++) {
		if (i->x == mainchar.x && i->y == mainchar.y)
			return;
	}
	tmp.x = splist[0].x;
	tmp.y = splist[0].y;
	tmp.interact = _keystate;
	_bulletpos.push_back(tmp);
}

void arc::SolarFox::changeSpritePosition(SpriteList &spritelist, int x, int y) noexcept
{
	for (auto i = spritelist.begin(); i != spritelist.end(); i++) {
		i->x = i->x + x;
		i->y = i->y + y;
	}
}

void arc::SolarFox::changeItemsPositionFromName(const std::string &name, int x, int y)
{
	auto finish = std::chrono::high_resolution_clock::now();
	millisec elapsed = finish - _startTime;
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == name) {
			changeSpritePosition(i->sprites, x, y);
			i->x += x;
			i->y += y;
			changeSpritePosition(i->sprites, x, y);
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
	std::vector<int> count;
	int a = 0;

	for (auto i = _bulletpos.begin(); i != _bulletpos.end(); i++) {
		switch (i->interact) {
		case MOVE_UP:
			i->y -= 1;
			break;
		case MOVE_DOWN:
			i->y += 1;
			break;
		case MOVE_LEFT:
			i->x -= 1;
			break;
		case MOVE_RIGHT:
			i->x += 1;
			break;
		default:
			break;
		}
	}
	/*
	**	a => emplecement dans le vecteur de la valeur à supprimer.
	*/
	for (auto i = _bulletpos.begin(); i != _bulletpos.end(); i++) {
		if (i->x > W_WIDTH || i->x < 0 || i->y > W_HEIGHT || i->y < 0) {
			count.push_back(a);
		}
		a += 1;
	}
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


const std::string &arc::SolarFox::ItemParser::getErrorLine()
{
	return (_line);
}

const int &arc::SolarFox::ItemParser::getErrorLineNb()
{
	return (_nbrline);
}

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

void arc::SolarFox::ItemParser::parseLine()
{
	// if (_line.length() > 0 && _line[0] != '#') {
	// 	std::cout << getAttribute() << std::endl;
	// 	if (getAttribute() == "UNIQUE")
	// 		getItems().push_back(createUnique());
	// 	else if (getAttribute() == "APPEND")

	// }
}

void arc::SolarFox::ItemParser::readFile(const std::string &filename)
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

arc::SpriteList arc::SolarFox::ItemParser::parser(const std::string &filename)
{
	_line.clear();
	_vector.clear();
	_nbrline = 1;
	readFile(filename);
	return _vector;
}
