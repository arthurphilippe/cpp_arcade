/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Game
*/

#include <unistd.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "Arc.hpp"
#include "Game.hpp"

arc::Game::Game()
	: _name("SolarFox"), _keystate(MOVE_LEFT), _info({GRID_H, GRID_L, GRID_STEP, FPS})
{
	setItems("tests/SpriteConfigurationFiles/Wall.conf");
	setItems("tests/SpriteConfigurationFiles/SealConfigurationFile.conf");
	setItems("sprite/FruitConf.conf");
	setItems("sprite/Pacgum.conf");
	setItems("sprite/Foe.conf");
}

void arc::Game::setItems(const std::string &path)
{
	std::ifstream s(path);
	std::string tmp;

	srandom(time(NULL) * getpid());
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

void arc::Game::processInteraction(Interaction &interact) noexcept
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

void arc::Game::shoot(const std::string &name)
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

void arc::Game::_updateSprite()
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
			&& _vectorIsCollided(pos, (Vectori) {it->x, it->y})) {
			if (it->attribute == DROP) {
				_items.erase(it);
				it = _items.begin();
				restart = true;
			} else if (it->attribute == FOE) {
				exit(10);
			}
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

void arc::Game::_updateBullets() noexcept
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

void arc::Game::_updateRotation(Item &item, int rotation)
{
	for (auto i = item.sprites.begin(); i != item.sprites.end(); i++) {
		i->rotation = rotation;
	}
}

void arc::Game::_updateRotateMain()
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

void arc::Game::_updateAutoMoveMain()
{
	auto move = MOVE_BINDS.find(_keystate);

	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == PLAYER_ITEM && move != MOVE_BINDS.end())
			_itemMove(PLAYER_ITEM, move->second);
	}
}

void arc::Game::_updateFoe()
{
	int u = 0;
	int x = 1;
	int y = 1;
	for (auto i = _items.begin(); i != _items.end(); i++) {
		u = random() % 2;
		if (u)
			x = x * (-1);
		u = random() % 2;
			y = y * (-1);
		if (i->attribute == FOE) {
			_itemMove(*i, (Vectori) {x, y});
		}
	}
}

void arc::Game::envUpdate() noexcept
{
	_updateRotateMain();
	_updateAutoMoveMain();
	_updateSprite();
	_updateBullets();
	_updateFoe();
	_checkItemsContact();
}
