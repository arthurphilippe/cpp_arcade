/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** GameWarper
*/

#ifndef GAMEWARPER_HPP_
	#define GAMEWARPER_HPP_

	#include <string>
	#include <memory>
	#include "IGame.hpp"
	#include "IDisplay.hpp"
	#include "DynamicFunc.hpp"

namespace arc {
	class GameWarper;
}

class arc::GameWarper {
public:
	GameWarper();
	~GameWarper();
protected:
private:
	DynamicFunc<IGame *(*)()>	_gameEntry;
	DynamicFunc<IDisplay *(*)()>	_displayEntry;
	std::unique_ptr<IGame>		_currGame;
	std::unique_ptr<IDisplay>	_currDisplay;

	static void _setItemSprites(Item &item);
};

#endif /* !GAMEWARPER_HPP_ */
