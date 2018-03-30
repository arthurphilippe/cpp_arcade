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
		while (getline(s, ItemParser::_line))
			createItems();
	} else {
		throw ParserError("Error: can't open '" + path + "'.");
	}
}

void arc::SolarFox::createItems()
{
	if (ItemParser::_line.length() > 0 && ItemParser::_line[0] != '#') {
		if (ItemParser::getFlag() == "UNIQUE")
			_items.push_back(ItemParser::createItem());
		else if (ItemParser::getFlag() == "APPEND")
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
	_line.clear();
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

arc::Attribute arc::SolarFox::_vectorCollide(Item &item, Vectori pos)
{
	for (auto it = _items.begin(); it != _items.end(); it++) {
		if (it->name != item.name &&
			_vectorIsCollided(pos, (Vectori) {it->x, it->y}))
			return BLOCK;
	}
	return UNK;
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
		_itemMove(PLAYER_ITEM, move->second);
	} else {
	switch (interact) {
		case ACTION_1:
			_keystate = interact;
			shoot("Seal");
			break;
		default:
			break;
	}
	}
}

void arc::SolarFox::shoot(const std::string &name)
{
	auto item = getItemFromName(name);
	std::cout << _keystate << std::endl;
	auto bullet = Bullet(_keystate, item.x, item.y);
	std::cout << bullet.getDirection() << std::endl;
	//std::cout << "kek " << std::endl;
//	_bulletlist.push_back(bullet);
//	std::cout << _bulletlist.size() - 1 << std::endl;
//	_items.push_back(_bulletlist[_bulletlist.size() - 1].getBullet());
	// _items.push_back(ItemParser::createItem(DEF_BULLETCONF, item.x, item.y));
	// if (_keystate == MOVE_DOWN)
	// 	_bulletDown.push_back(&_items[_items.size() - 1]);
	// if (_keystate == MOVE_UP)
	// 	_bulletUp.push_back(&_items[_items.size() - 1]);
	// if (_keystate == MOVE_LEFT)
	// 	_bulletLeft.push_back(&_items[_items.size() - 1]);
	// if (_keystate == MOVE_RIGHT)
	// 	_bulletRight.push_back(&_items[_items.size() - 1]);
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
	for (auto i = _bulletlist.begin(); i != _bulletlist.end(); i ++) {
		switch (i->getDirection()) {
			case MOVE_UP:
				i->getBullet().y -= 1;
				break;
			case MOVE_DOWN:
				i->getBullet().y += 1;
				break;
			default:
				break;

		}
	}
}
