/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Game
*/

#ifndef SOLARFOX_HPP_
	#define SOLARFOX_HPP_

	#include <memory>
	#include <chrono>
	#include <string>
	#include <cmath>
	#include <functional>
	#include "Arc.hpp"
	#include "IGame.hpp"
	#include "Error.hpp"
	#include "ItemParser.hpp"
	#define PLAYER_ITEM "Pacman"

namespace arc {
	class Game;
	constexpr auto GRID_H = 42;
	constexpr auto GRID_L = 42;
	constexpr auto GRID_STEP = 48;
	constexpr auto FPS = 55;
	constexpr auto W_HEIGHT = 1200;
	constexpr auto W_WIDTH = 1550;
	constexpr auto DEF_BULLETCONF = "tests/SpriteConfigurationFiles/Bullets.conf";
	constexpr auto BLUE_GHOST1 = "sprite/pacman/BlueGhost1.png";
	constexpr auto BLUE_GHOST2 = "sprite/pacman/BlueGhost2.png";
	constexpr auto RED_GHOST1 = "sprite/pacman/Ghost1.png";
	constexpr auto RED_GHOST2 = "sprite/pacman/Ghost2.png";
}

class arc::Game : public arc::IGame {
public:
	Game();
	~Game() {};
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
	void processInteraction(Interaction &) noexcept;
	void envUpdate() noexcept;
	bool isOver() const noexcept
	{
		return _isOver;
	}
	int getScore() const noexcept
	{
		return _score;
	}
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
	void changeSpritePosition(SpriteList &spritelist,
					int x, int y) noexcept;
	static ItemList defaultItems;
	void _dumpItems() const noexcept;
	SpriteList &getSpriteListFromName(const std::string &name);

	void _nextLevel();

	//update for Foe
	void _moveFoe() noexcept;
	void _dirFoe(Item &) noexcept;
	void _horizontalDir(Item &) noexcept;
	void _verticalDir(Item &) noexcept;
	void _chooseDir(Item &) noexcept;

	//update
	void _updateBullets() noexcept;
	void _updateSprite();
	void _updateAutoMoveMain();
	void _updateRotateMain();
	void _updateRotation(Item &item, int rotation);

	std::chrono::high_resolution_clock::time_point _startTime;
	// Item Moves
	bool _itemMove(const std::string &, Vectori);
	bool _itemMove(Item &, Vectori);
	std::vector<class Bullet> _bulletlist;
	bool _vectorIsCollided(Vectori, Vectori);
	bool _itemBlock(Item &, Vectori);
	bool _movedThisTurn;

	// Item Collisions on update
	bool _playerActionContact(Item &drop);
	bool _checkPlayerContact(Item &player);
	void _checkItemsContact();
	void _edgeTeleport();
	void _edgeTeleport(Item &);

	// Manage fever mode
	void _setBlueGhost(bool b);
	void _setFever();
	void _manageFever();
	std::chrono::high_resolution_clock::time_point _startFever;
	void _makeGhostBlue(SpriteList &list);
	void _makeGhostRed(SpriteList &list);


	// Game status
	bool _isCleared();
	bool _isOver;
	bool _fever;
	int _score;
};

#endif /* !SOLARFOX_HPP_ */
