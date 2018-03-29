/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SolarFox
*/

#include <iostream>
#include "Arc.hpp"
#include "SolarFox.hpp"

static const arc::Item
DEF_PACMAN = {PLAYER_ITEM,
		"tests/SpriteConfigurationFiles/SealConfigurationFile.conf",
		arc::SpriteList(), 0, 100, 220};
static const arc::Item
DEF_GHOSTA = {"ghost a", "", arc::SpriteList(), 0, 30, 30};
static const arc::Item
DEF_SHOOT = {"Bullet", "tests/SpriteConfigurationFiles/Bullets.conf", arc::SpriteList(), 0, 20, 20};
static const arc::Item
DEF_WALL = {"Wall",
"tests/SpriteConfigurationFiles/Wall.conf", arc::SpriteList(), 0, 20, 20};
static const arc::Item
DEF_FRUIT = {"Fruit",
"sprite/FruitConf.conf", arc::SpriteList(), 0, 200, 200};

arc::SolarFox::SolarFox()
	: _name("SolarFox"), _info({GRID_H, GRID_L, GRID_STEP, FPS})
{
	_items.push_back(DEF_PACMAN);
	_items.push_back(DEF_SHOOT);
	_items.push_back(DEF_WALL);
	_items.push_back(DEF_FRUIT);
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
			_vectorIsCollided(pos, (Vectori) {it->x, it->y}))
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
