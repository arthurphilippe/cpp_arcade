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
DEF_PACMAN = {"Seal",
		"tests/SpriteConfigurationFiles/SealConfigurationFile.conf",
		arc::SpriteList(), 0, 20, 20};
static const arc::Item
DEF_GHOSTA = {"ghost a", "", arc::SpriteList(), 0, 30, 30};
static const arc::Item
DEF_GHOSTB = {"ghost b", "", arc::SpriteList(), 0, 40, 30};
static const arc::Item
DEF_GHOSTC = {"ghost c", "", arc::SpriteList(), 0, 50, 30};
static const arc::Item
DEF_GHOSTD = {"ghost d", "", arc::SpriteList(), 0, 60, 30};
static const arc::Item
DEF_SHOOT = {"Bullet", "tests/SpriteConfigurationFiles/Bullets.conf", arc::SpriteList(), 0, 20, 20};

arc::SolarFox::SolarFox()
	: _name("SolarFox"), _info({GRID_H, GRID_L, GRID_STEP, FPS})
{
	_items.push_back(DEF_PACMAN);
	_items.push_back(DEF_GHOSTA);
	_items.push_back(DEF_GHOSTB);
	_items.push_back(DEF_GHOSTC);
	_items.push_back(DEF_GHOSTD);
	_items.push_back(DEF_SHOOT);
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


void arc::SolarFox::proccessIteraction(Interaction &interact) noexcept
{
	switch (interact) {
		case MOVE_LEFT:
			changeItemsPositionFromName("Seal", -1, 0);
			break;
		case MOVE_RIGHT:
			changeItemsPositionFromName("Seal", 1, 0);
			break;
		case MOVE_UP:
			changeItemsPositionFromName("Seal", 0, -1);
			break;
		case MOVE_DOWN:
			changeItemsPositionFromName("Seal", 0, 1);
			break;
		case ACTION_1:
			shoot("Seal");
			break;
		default:
			break;
	}
	_keystate = interact;
}

void arc::SolarFox::shoot(const std::string &name)
{
	auto mainchar = getItemFromName(name);
        struct Position tmp;
	for (auto i = _bulletpos.begin(); i != _bulletpos.end(); i++) {
		if (i->x == mainchar.x && i->y == mainchar.y)
			return;
	}
	tmp.x = mainchar.x;
	tmp.y = mainchar.y;
	tmp.interact = _keystate;
	_bulletpos.push_back(tmp);
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
	for (auto i = _bulletpos.begin(); i != _bulletpos.end(); i++) {
		if (i->x > W_WIDTH || i->x < 0 || i->y > W_HEIGHT || i->y < 0) {
			count.push_back(a);
		}
		a += 1;
	}

}
