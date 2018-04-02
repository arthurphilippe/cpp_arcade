/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SolarFox
*/

#ifndef SOLARFOX_HPP_
	#define SOLARFOX_HPP_

	#include <memory>
	#include <chrono>
	#include <string>
	#include <cmath>
	#include "Arc.hpp"
	#include "IGame.hpp"
	#include "Error.hpp"
	#include "ItemParser.hpp"
	#define PLAYER_ITEM "Seal"

namespace arc {
	class SolarFox;
	constexpr auto GRID_H = 42;
	constexpr auto GRID_L = 42;
	constexpr auto GRID_STEP = 12;
	constexpr auto FPS = 56;
	constexpr auto W_HEIGHT = 720;
	constexpr auto W_WIDTH = 1280;
	const std::string DEF_BULLETCONF = "tests/SpriteConfigurationFiles/Bullets.conf";
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
	using ItemRef = Item *;
	void createItems();
	class Bullet {
	public:
		Bullet(Interaction direction, ItemRef bullet)
			: _direction(direction) {
				_bullet = bullet;
			}
		~Bullet() {}
		ItemRef getBullet() {return _bullet;}
		Interaction &getDirection() {return _direction;}
	private:
		ItemRef _bullet;
		Interaction _direction;
	};
private:
	std::vector<struct Position> _bulletpos;
	std::string	_name;
	Interaction _keystate;
	ItemList	_items;
	Specs		_info;
	void setItems(const std::string &path);
	void createSprite();
	void changeItemsPositionFromName(const std::string &name, int a, int b);
	std::chrono::high_resolution_clock::time_point _startTime;
	void changeSpritePosition(SpriteList &spritelist,
					int x, int y) noexcept;
	static ItemList defaultItems;
	void _dumpItems() const noexcept;
	SpriteList &getSpriteListFromName(const std::string &name);
	void updateBullets() noexcept;
	// Item Moves
	void _itemMove(const std::string &, Vectori);
	void _itemMove(Item &, Vectori);
	std::vector<class Bullet> _bulletlist;
	bool _vectorIsCollided(Vectori, Vectori);
	Attribute _vectorCollide(Item &, Vectori);
};

#endif /* !SOLARFOX_HPP_ */
