/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Pacman
*/

#include <iostream>
#include "Arc.hpp"
#include "Pacman.hpp"

static const arc::Item
DEF_PACMAN = {"pacman",
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

arc::Pacman::Pacman()
	: _name("Pacman"), _info({GRID_H, GRID_L, GRID_STEP, FPS})
{
	_items.push_back(DEF_PACMAN);
	_items.push_back(DEF_GHOSTA);
	_items.push_back(DEF_GHOSTB);
	_items.push_back(DEF_GHOSTC);
	_items.push_back(DEF_GHOSTD);
}

void arc::Pacman::dump() const noexcept
{
	std::cout << "Dumping game " << _name << "." << std::endl;
	std::cout << "Grid size: " << _info.x << "*" << _info.y;
	std::cout << "*" <<_info.pixelStep << std::endl;
	_dumpItems();
}

void arc::Pacman::_dumpItems() const noexcept
{
	for (auto it = _items.begin(); it != _items.end(); ++it) {
		std::cout << "Item: " << it->name << " -- Sprite count:";
		std::cout << it->sprites.size() << " -- Pos: " << it->x;
		std::cout << ", " << it->y << std::endl;
	}
}

void arc::Pacman::putSpritePosition(const Item &item, const std::vector<struct Position> &poslist)
{
	(void) item;
	(void) poslist;
}

void arc::Pacman::proccessIteraction(Interaction &interact) noexcept
{
	switch (interact) {
		case MOVE_UP:
			_items[0].y -= 1;
			break;
		case MOVE_DOWN:
			_items[0].y += 1;
			break;
		case MOVE_LEFT:
			_items[0].x -= 1;
			break;
		case MOVE_RIGHT:
			_items[0].x += 1;
			break;
		case ACTION_1:
			break;
		default:
			break;
	}
}

arc::Item &arc::Pacman::getItemFromName(const std::string &name)
{
	for (auto i = _items.begin(); i != _items.end(); i++) {
		if (i->name == name)
			return *i;
	}
	return _items[0];
}


void arc::Pacman::envUpdate() noexcept
{}
