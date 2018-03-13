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
		"tests/SpriteConfigurationFiles/RealConfigurationFile.conf",
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
		default:
			break;
	}
}
