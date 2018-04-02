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
	: _name("SolarFox"), _keystate(MOVE_LEFT), _info({GRID_H, GRID_L, GRID_STEP, FPS})
{
	setItems("tests/SpriteConfigurationFiles/Wall.conf");
	setItems("tests/SpriteConfigurationFiles/SealConfigurationFile.conf");
	setItems("sprite/FruitConf.conf");
	setItems("sprite/Pacgum.conf");
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
//		_itemMove(PLAYER_ITEM, move->second);
		_keystate = interact;
	} else {
		switch (interact) {
			case ACTION_1:
				shoot(PLAYER_ITEM);
				break;
			default:
				break;
		}
	}
}

void arc::SolarFox::shoot(const std::string &name)
{
	auto item = getItemFromName(name);
	_items.push_back(ItemParser::createItem(DEF_BULLETCONF, item.x, item.y));
	switch (_keystate) {
		case MOVE_LEFT:
			_items[_items.size() -1].secondattribute = arc::LEFT;
			break;
		case MOVE_RIGHT:
			_items[_items.size() -1].secondattribute = arc::RIGHT;
			break;
		case MOVE_DOWN:
			_items[_items.size() -1].secondattribute = arc::DOWN;
			break;
		case MOVE_UP:
			_items[_items.size() -1].secondattribute = arc::UP;
			break;
		default:
			break;
	}
}

void arc::SolarFox::_updateChar()
{
	auto finish = std::chrono::high_resolution_clock::now();
	millisec elapsed = finish - _startTime;
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->sprites.size() > 1) {
			if (elapsed.count() > 200) {
				if (i->currSpriteIdx >= (int) (i->sprites.size() - 1))
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

void arc::SolarFox::_updateBullets() noexcept
{
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == "Bullet") {
			switch (i->secondattribute) {
			case LEFT:
				i->x -= 1;
				break;
			case RIGHT:
				i->x += 1;
				break;
			case DOWN:
				i->y += 1;
				break;
			case UP:
				i->y -= 1;
				break;
			default:
				break;
			}
		}
	}
}

void arc::SolarFox::_updateRotation(Item &item, int rotation)
{
	for (auto i = item.sprites.begin(); i != item.sprites.end(); i++) {
		i->rotation = rotation;
	}
}

void arc::SolarFox::_updateRotateMain()
{
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == PLAYER_ITEM) {
			switch (_keystate) {
			case MOVE_LEFT:
				_updateRotation(*i, 270);
				break;
			case MOVE_RIGHT:
				_updateRotation(*i, 90);
				break;
			case MOVE_DOWN:
				_updateRotation(*i, 180);
				break;
			case MOVE_UP:
				_updateRotation(*i, 0);
				break;
			default:
				break;
			}
			return;
		}
	}
}

void arc::SolarFox::_updateAutoMoveMain()
{
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == PLAYER_ITEM) {
			switch (_keystate) {
			case MOVE_LEFT:
				i->x -= 1;
				break;
			case MOVE_RIGHT:
				i->x += 1;
				break;
			case MOVE_DOWN:
				i->y += 1;
				break;
			case MOVE_UP:
				i->y -= 1;
				break;
			default:
				break;
			}
		}
	}
}

void arc::SolarFox::envUpdate() noexcept
{
	_updateRotateMain();
	_updateAutoMoveMain();
	_updateChar();
	_updateBullets();
}
