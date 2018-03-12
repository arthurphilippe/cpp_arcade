/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** GameWarper
*/

#include <algorithm>
#include "unistd.h"
#include "GameWarper.hpp"
#include "SpriteParser.hpp"

const std::vector<arc::Interaction> arc::GameWarper::_sysInteractions {
	LIB_NEXT, LIB_PREV, GAME_NEXT, GAME_PREV, QUIT
};

arc::GameWarper::GameWarper()
	: _gameEntry("./games/Pacman/libPacman.so"),
	_displayEntry("./lib/CacaDisplay/libcaca.so"),
	_currGame(_gameEntry.get()()),
	_currDisplay(_displayEntry.get()()),
	_running(true)
{
	for_each(_currGame->getItems().begin(), _currGame->getItems().end(),
			 _setItemSprites);
	_currGame->dump();
	_currDisplay->clear();
	_currDisplay->putstr("kapa", 0, 0);
	_currDisplay->refresh();
}

arc::GameWarper::~GameWarper()
{
	// bool hasExited = false;
	// while (!hasExited) {
	// 	auto inter = _currDisplay->getInteractions();
	// 	while (inter.size() != 0) {
	// 		if (inter.front() == Interaction::QUIT) {
	// 			std::cout << "recived quit" << std::endl;
	// 			hasExited = true;
	// 		} else {
	// 			_currGame->proccessIteraction(inter.front());
	// 			// _currGame->dump();
				// _currDisplay->putItem(_currGame->getItems()[0]);
	// 			_currDisplay->refresh();
	// 		}
	// 		inter.pop();
	// 	}
	// }
}

int arc::GameWarper::loop()
{
	while (_running) {
		_processInteractions();
		_currDisplay->refresh();
		usleep(1000);
	}
	return 0;
}

void arc::GameWarper::_processWarperInter(Interaction &inter)
{
	switch (inter) {
		case QUIT:
			_running = false;
			break;
		default:
			break;
	}
}

void arc::GameWarper::_processInteractions()
{
	auto inter = _currDisplay->getInteractions();
	while (inter.size() != 0) {
		std::cout << inter.front() << std::endl;
		if (find(_sysInteractions.begin(), _sysInteractions.end(),
			inter.front()) != _sysInteractions.end())
			_processWarperInter(inter.front());
		else {
			std::cout << "is not sysinter" << std::endl;
			_currGame->proccessIteraction(inter.front());
			_currDisplay->putItem(_currGame->getItems()[0]);
			_currDisplay->refresh();
		}
		inter.pop();
	}
}

void arc::GameWarper::_setItemSprites(Item &item)
{
	if (item.spritesPath.length())
		item.sprites = SpriteParser::parser(item.spritesPath);
}
