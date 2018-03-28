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
