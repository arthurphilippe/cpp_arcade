/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** GameWraper
*/

#include <algorithm>
#include "unistd.h"
#include "GameWraper.hpp"
#include "SpriteParser.hpp"

const std::vector<arc::Interaction> arc::GameWraper::_sysInteractions {
	LIB_NEXT, LIB_PREV, GAME_NEXT, GAME_PREV, QUIT
};

arc::GameWraper::GameWraper()
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

arc::GameWraper::~GameWraper()
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

int arc::GameWraper::loop()
{
	while (_running) {
		_startTime = std::chrono::high_resolution_clock::now();
		_processInteractions();
		_currDisplay->refresh();
		_waitCycle(30);
	}
	return 0;
}

void arc::GameWraper::_waitCycle(size_t fps)
{
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsed = finish - _startTime;
	std::chrono::duration<double, std::milli> tempo(
		((61 - fps) * 1000 / 60) - elapsed.count());
	std::this_thread::sleep_for(tempo);
}

void arc::GameWraper::_processWraperInter(Interaction &inter)
{
	switch (inter) {
		case QUIT:
			_running = false;
			break;
		default:
			break;
	}
}

void arc::GameWraper::_processInteractions()
{
	auto inter = _currDisplay->getInteractions();
	while (inter.size() != 0) {
		std::cout << inter.front() << std::endl;
		if (find(_sysInteractions.begin(), _sysInteractions.end(),
			inter.front()) != _sysInteractions.end())
			_processWraperInter(inter.front());
		else {
			std::cout << "is not sysinter" << std::endl;
			_currGame->proccessIteraction(inter.front());
			_currDisplay->putItem(_currGame->getItems()[0]);
			_currDisplay->refresh();
		}
		inter.pop();
	}
}

void arc::GameWraper::_setItemSprites(Item &item)
{
	if (item.spritesPath.length())
		item.sprites = SpriteParser::parser(item.spritesPath);
}
