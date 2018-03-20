/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** IGame
*/

#ifndef IGAME_HPP_
	#define IGAME_HPP_

	#include <vector>
	#include "Arc.hpp"
	#include "Sprite.hpp"
	#include "SpriteParser.hpp"
	#include "IDisplay.hpp"

namespace arc {
	class IGame;
}

class arc::IGame {
public:
	struct Specs {
		int x;
		int y;
		unsigned int pixelStep;
		unsigned int fps;
	};

	virtual ~IGame() = default;
	virtual void dump() const noexcept = 0;
	virtual ItemList &getItems() noexcept = 0;
	virtual Item &getItemFromName(const std::string &) = 0;
	virtual const Specs &getSpecs() const noexcept = 0;
	virtual void proccessIteraction(Interaction &) noexcept = 0;
	virtual void envUpdate() noexcept = 0;
	virtual const std::vector<struct Position> &getBulletPos() = 0;
};

#endif /* !IGAME_HPP_ */
