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
	#include "Arc.hpp"

namespace arc {
	class GameWarper;
}

class arc::GameWarper {
public:
	GameWarper();
	~GameWarper();

	int loop();
protected:
private:
	DynamicFunc<IGame *(*)()>	_gameEntry;
	DynamicFunc<IDisplay *(*)()>	_displayEntry;
	std::unique_ptr<IGame>		_currGame;
	std::unique_ptr<IDisplay>	_currDisplay;

	void _processWarperInter(Interaction &iter);
	void _processInteractions();
	static const std::vector<Interaction> _sysInteractions;
	static void _setItemSprites(Item &item);

	bool _running;
};

#endif /* !GAMEWARPER_HPP_ */
