/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Game
*/

#include <iostream>
#include <fstream>
#include "Arc.hpp"
#include "Game.hpp"

const std::string
DEF_BULLETCONF = "tests/SpriteConfigurationFiles/Bullets.conf";

arc::Game::Game()
	: _name("Game"), _info({GRID_H, GRID_L, GRID_STEP, FPS})
{
	setItems("tests/SpriteConfigurationFiles/Wall.conf");
	setItems("tests/SpriteConfigurationFiles/SealConfigurationFile.conf");
	setItems("sprite/FruitConf.conf");
}

void arc::Game::setItems(const std::string &path)
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

void arc::Game::createItems()
{
	if (ItemParser::_line.length() > 0 && ItemParser::_line[0] != '#') {
		if (ItemParser::getFlag() == "UNIQUE")
			_items.push_back(ItemParser::createItem());
		else if (ItemParser::getFlag() == "APPEND")
			createSprite();
	}
}

void arc::Game::createSprite()
{
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == ItemParser::setName()) {
			i->sprites.push_back(ItemParser::createSprite());
			return;
		}
	}
	_items.push_back(ItemParser::createItem());
}

void arc::Game::dump() const noexcept
{
	std::cout << "Dumping game " << _name << "." << std::endl;
	std::cout << "Grid size: " << _info.x << "*" << _info.y;
	std::cout << "*" <<_info.pixelStep << std::endl;
	_dumpItems();
}

void arc::Game::_dumpItems() const noexcept
{
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		std::cout << "Item: " << it->name << " -- Sprite count:";
		std::cout << it->sprites.size() << " -- Pos: " << it->x;
		std::cout << ", " << it->y << std::endl;
	}
}

using millisec = std::chrono::duration<double, std::milli>;

bool arc::Game::_vectorIsCollided(Vectori a, Vectori b)
{
	int diffx = a.v_x - b.v_x;
	int diffy = a.v_y - b.v_y;

	diffx = std::abs(diffx);
	diffy = std::abs(diffy);
	if (diffx < GRID_STEP && diffy < GRID_STEP)
		return true;
	return false;
}

bool arc::Game::_itemBlock(Item &item, Vectori pos)
{
	bool coll;

	for (auto it = _items.begin(); it != _items.end(); it++) {
		coll = _vectorIsCollided(pos, (Vectori) {it->x, it->y});
		if (coll && it->name != item.name && it->attribute == BLOCK)
			return true;
		// if (it->attribute == BLOCK && ret != FOE)
		// 	ret = it->attribute;
		// else if (it->attribute == FOE)
		// 	ret = it->attribute;
	}
	return false;
}

void arc::Game::_itemMove(const std::string &name, Vectori mod)
{
	for (auto it = _items.begin(); it != _items.end(); it++) {
		if (it->name == name)
			_itemMove(*it, mod);
	}
}

void arc::Game::_itemMove(Item &item, Vectori mod)
{
	Vectori newPos {item.x + mod.v_x, item.y + mod.v_y};

	if (_itemBlock(item, newPos) != BLOCK) {
		item.x = newPos.v_x;
		item.y = newPos.v_y;
	}
}

void arc::Game::proccessIteraction(Interaction &interact) noexcept
{
	auto move = MOVE_BINDS.find(interact);
	if (move != MOVE_BINDS.end()) {
		_itemMove(PLAYER_ITEM, move->second);
	} else {
	switch (interact)
	{
		case ACTION_1:
			shoot(PLAYER_ITEM);
			break;
		default:
			break;
	}
	}
	if (interact == MOVE_LEFT || interact == MOVE_RIGHT || interact == MOVE_UP || interact == MOVE_DOWN)
		_keystate = interact;
}

void arc::Game::shoot(const std::string &name)
{
	auto item = getItemFromName(name);
	ItemParser::createItem(DEF_BULLETCONF, item.x, item.y);
}

void arc::Game::changeItemsPositionFromName(const std::string &name, int x, int y)
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

arc::Item &arc::Game::getItemFromName(const std::string &name)
{
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == name)
			return *i;
	}
	return _items[0];
}

arc::SpriteList &arc::Game::getSpriteListFromName(const std::string &name)
{

	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == name)
			return i->sprites;
	}
	return _items[0].sprites;
}

bool arc::Game::_checkPlayerContact(Item &player)
{
	Vectori pos {player.x, player.y};
	bool restart = false;

	for (auto it = _items.begin(); it != _items.end(); it++) {
		if (it->name != player.name
			&& _vectorIsCollided(pos, (Vectori) {it->x, it->y})
			&& it->attribute == DROP) {
			_items.erase(it);
			it = _items.begin();
			restart = true;
		}
	}
	return restart;
}

void arc::Game::_checkItemsContact()
{
	for (auto it = _items.begin(); it != _items.end(); it++) {
		if (it->attribute == PLAYER) {
			if (_checkPlayerContact(*it))
				it = _items.begin();
		}
	}
}

void arc::Game::envUpdate() noexcept
{
	_checkItemsContact();
}
