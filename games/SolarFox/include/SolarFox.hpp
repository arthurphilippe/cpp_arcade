/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SolarFox
*/

#ifndef SOLARFOX_HPP_
	#define SOLARFOX_HPP_

	#include <chrono>
	#include <string>
	#include "Arc.hpp"
	#include "IGame.hpp"

namespace arc {
	class SolarFox;
	constexpr auto GRID_H = 42;
	constexpr auto GRID_L = 42;
	constexpr auto GRID_STEP = 12;
	constexpr auto FPS = 56;
	constexpr auto W_HEIGHT = 720;
	constexpr auto W_WIDTH = 1280;
}

class arc::SolarFox : public arc::IGame {
public:
	SolarFox();
	~SolarFox() {
		_startTime = std::chrono::high_resolution_clock::now();
	};
	void dump() const noexcept override;
	ItemList &getItems() noexcept override
	{
		return _items;
	}
	Item &getItemFromName(const std::string &name);
	const Specs &getSpecs() const noexcept override
	{
		return _info;
	}
	void proccessIteraction(Interaction &) noexcept;
	void envUpdate() noexcept;
	void shoot(const std::string &name);
	const std::vector<struct Position> &getBulletPos() {return _bulletpos;}
	arc::ACTION_LIST canMove(const std::string &name, int x, int y);
	arc::ACTION_LIST moveDirectionPars(arc::Item, const struct Position &pos, const std::string &name);
	arc::ACTION_LIST canMoveDirectionX(const arc::Sprite &, const int &x, const std::string &name);
	arc::ACTION_LIST canMoveDirectionY(const arc::Sprite &, const int &y, const std::string &name);
private:
	Interaction _keystate;
	std::vector<struct Position> _bulletpos;
	std::string	_name;
	ItemList	_items;
	ItemList	_todraw;
	Specs		_info;
	void changeItemsPositionFromName(const std::string &name, int a, int b);
	std::chrono::high_resolution_clock::time_point _startTime;
	void changeSpritePosition(SpriteList &spritelist, int x, int y) noexcept;
	static ItemList defaultItems;
	void printBackground() const noexcept;
	void _dumpItems() const noexcept;
	SpriteList &getSpriteListFromName(const std::string &name);
};

#endif /* !SOLARFOX_HPP_ */
