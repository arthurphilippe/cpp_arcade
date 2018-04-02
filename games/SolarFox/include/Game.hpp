/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Game
*/

#ifndef SOLARFOX_HPP_
	#define SOLARFOX_HPP_

	#include <chrono>
	#include <string>
	#include <cmath>
	#include <functional>
	#include "Arc.hpp"
	#include "IGame.hpp"
	#include "Error.hpp"
	#include "ItemParser.hpp"
	#define PLAYER_ITEM "Seal"

namespace arc {
	class Game;
	constexpr auto GRID_H = 42;
	constexpr auto GRID_L = 42;
	constexpr auto GRID_STEP = 12;
	constexpr auto FPS = 56;
	constexpr auto W_HEIGHT = 720;
	constexpr auto W_WIDTH = 1280;
}

class arc::Game : public arc::IGame {
public:
	Game();
	~Game() {
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
	void createItems();
private:
	Interaction _keystate;
	std::vector<struct Position> _bulletpos;
	std::string	_name;
	ItemList	_items;
	ItemList	_todraw;
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

	// Item Moves
	void _itemMove(const std::string &, Vectori);
	void _itemMove(Item &, Vectori);
	bool _vectorIsCollided(Vectori, Vectori);
	bool _itemBlock(Item &, Vectori);

	// Item Collisions on update
	bool _playerActionContact(Item &drop);
	bool _checkPlayerContact(Item &player);
	void _checkItemsContact();
};

#endif /* !SOLARFOX_HPP_ */
