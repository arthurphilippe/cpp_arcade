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
	: _name("Pacman"),
	_keystate(MOVE_LEFT),
	_info({GRID_H, GRID_L, GRID_STEP, FPS}),
	_isOver(false),
	_score(0)
{
	srandom(time(NULL) * getpid());
	setItems("sprite/solarfox/Wall.conf");
	setItems("sprite/solarfox/Player.conf");
	setItems("sprite/solarfox/Mine.conf");
	setItems("sprite/solarfox/Mine2.conf");
	setItems("sprite/solarfox/Foe.conf");
	_foe = std::chrono::high_resolution_clock::now();
}

void arc::Game::_nextLevel()
{
	_items.clear();
	setItems("sprite/solarfox/Wall.conf");
	setItems("sprite/solarfox/Player.conf");
	setItems("sprite/solarfox/Mine.conf");
	setItems("sprite/solarfox/Mine2.conf");
	setItems("sprite/solarfox/Foe.conf");
	_isOver = false;
	_info.fps += 1;
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
		std::cout << ", " << it->y;
		std::cout << " -- SpritePath: " << it->spritesPath
		<< " -- Attribute: " << it->attribute
		<< " -- SecondAttribute: " << it->secondattribute
		<< " -- currSpriteIDX: " << it->currSpriteIdx << std::endl;
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

bool arc::Game::_itemMove(Item &item, Vectori mod)
{
	Vectori newPos {item.x + mod.v_x, item.y + mod.v_y};

	if (_itemBlock(item, newPos) != BLOCK) {
		item.x = newPos.v_x;
		item.y = newPos.v_y;
		return true;
	} else
		return false;
}

void arc::Game::processInteraction(Interaction &interact) noexcept
{
	auto move = MOVE_BINDS.find(interact);
	if (move != MOVE_BINDS.end()) {
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

void arc::Game::_shootOffSet(int &x, int &y)
{

	switch (_keystate) {
		case MOVE_LEFT:
			x -= 20;
			break;
		case MOVE_RIGHT:
			x += 20;
			break;
		case MOVE_UP:
			y -= 20;
			break;
		case MOVE_DOWN:
			y += 20;
			break;
		default:
			break;
	}
}

void arc::Game::shoot(const std::string &name)
{
	auto item = getItemFromName(name);
	int x = item.x;
	int y = item.y;
	_shootOffSet(x, y);
	_items.push_back(ItemParser::createItem(DEF_BULLETCONF, x, y));
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
				_score += 1;
			} else if (it->attribute == FOE) {
				_isOver = true;
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
			if (i->x < 0 + (24 + MAX_PLACE)
				|| i->x > (906 - 24 - MAX_PLACE)
				|| i->y > (906 - 24 - MAX_PLACE)
				|| i->y < 0 + (24 + MAX_PLACE)) {
					_items.erase(i);
					i = _items.begin();
				}
			switch (i->secondattribute) {
			case LEFT:
				i->x -= 3;
				break;
			case RIGHT:
				i->x += 3;
				break;
			case DOWN:
				i->y += 3;
				break;
			case UP:
				i->y -= 3;
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
				_updateRotation(*i, 180);
				break;
			case MOVE_RIGHT:
				_updateRotation(*i, 0);
				break;
			case MOVE_DOWN:
				_updateRotation(*i, 90);
				break;
			case MOVE_UP:
				_updateRotation(*i, -90);
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


void arc::Game::_dirFoe(Item &item) noexcept
{
	switch (item.secondattribute) {
		case RIGHT:
			item.secondattribute = LEFT;
			break;
		case LEFT:
			item.secondattribute = RIGHT;
			break;
		case UP:
			item.secondattribute = DOWN;
			break;
		case DOWN:
			item.secondattribute = UP;
			break;
		default:
			break;
	}
}

void arc::Game::_moveFoe() noexcept
{
	bool move = true;
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->attribute == FOE) {
			switch (i->secondattribute) {
				case LEFT:
					move = _itemMove(*i, Vectori {-1, 0});
					break;
				case RIGHT:
					move = _itemMove(*i, Vectori {1, 0});
					break;
				case UP:
					move = _itemMove(*i, Vectori {0, -1});
					break;
				case DOWN:
					move = _itemMove(*i, Vectori {0, 1});
					break;
				default:
				break;
			}
			if (!move)
				_dirFoe(*i);
		}
		move = true;
	}
}

void arc::Game::envUpdate() noexcept
{
	_foeShoot();
	_foeMoveShoot();
	_moveFoe();
	_edgeTeleport();
	_updateRotateMain();
	_updateAutoMoveMain();
	_updateSprite();
	_updateBullets();
	_checkItemsContact();
	if (_isCleared())
		_nextLevel();
}

void arc::Game::_foeMoveShoot()
{
	for (auto i = _items.begin(); i != _items.end(); i ++) {
		if (i->name == "FoeMissile") {
			if (i->x < 0 + (24 + MAX_PLACE)
				|| i->x > (906 - 24 - MAX_PLACE)
				|| i->y > (906 - 24 - MAX_PLACE)
				|| i->y < 0 + (24 + MAX_PLACE)) {
					_items.erase(i);
					i = _items.begin();
				}
			switch (i->secondattribute) {
			case LEFT:
				i->x -= 3;
				break;
			case RIGHT:
				i->x += 3;
				break;
			case DOWN:
				i->y += 3;
				break;
			case UP:
				i->y -= 3;
				break;
			default:
				break;
			}
		}
	}
}


void arc::Game::_foeDirShoot(Item &item)
{
	static int i = 0;
	auto finish = std::chrono::high_resolution_clock::now();
	millisec elapsed = finish - _foe;
	if (elapsed.count() < 1500)
		return;
	switch (item.sprites[0].rotation) {
		case 90:
			_items.push_back(ItemParser::createItem(FOE_MUNITION, item.x, item.y + MAX_PLACE));
			_items[_items.size() - 1].sprites[0].rotation = 180;
			_items[_items.size() - 1].secondattribute = DOWN;
			break;
		case 0:
			_items.push_back(ItemParser::createItem(FOE_MUNITION, item.x + MAX_PLACE, item.y));
			_items[_items.size() - 1].sprites[0].rotation = 90;
			_items[_items.size() - 1].secondattribute = RIGHT;
			break;
		case -90:
			_items.push_back(ItemParser::createItem(FOE_MUNITION, item.x, item.y - MAX_PLACE));
			_items[_items.size() - 1].sprites[0].rotation = 0;
			_items[_items.size() - 1].secondattribute = UP;
			break;
		case 180:
			_items.push_back(ItemParser::createItem(FOE_MUNITION, item.x - MAX_PLACE, item.y));
			_items[_items.size() - 1].sprites[0].rotation = -90;
			_items[_items.size() - 1].secondattribute = LEFT;
			break;
		default:
			break;

	}
	i += 1;
	if (i >= 4)
	{
		i = 0;
		_foe = std::chrono::high_resolution_clock::now();
	}
}

void arc::Game::_foeShoot()
{
	auto foe1 = getItemFromName("Foe1");
	auto foe2 = getItemFromName("Foe2");
	auto foe3 = getItemFromName("Foe3");
	auto foe4 = getItemFromName("Foe4");
	_foeDirShoot(foe1);
	_foeDirShoot(foe2);
	_foeDirShoot(foe3);
	_foeDirShoot(foe4);
}

void arc::Game::_edgeTeleport(Item &item)
{
	if (_vectorIsCollided((Vectori) {item.x, item.y},
		(Vectori) {-24, 416}))
		item.x = 906;
	else if (_vectorIsCollided((Vectori) {item.x, item.y},
			(Vectori) {906 + 48, 416}))
		item.x = 24;

}

void arc::Game::_edgeTeleport()
{
	uint count = 0;

	for (auto it = _items.begin(); it != _items.end() && count < 5; it++) {
		if (it->attribute == FOE || it->attribute == PLAYER) {
			_edgeTeleport(*it);
			count += 1;
		}
	}
}

bool arc::Game::_isCleared()
{
	for (auto it = _items.begin(); it != _items.end(); it++) {
		if (it->attribute == DROP) {
			return false;
		}
	}
	return true;
}
