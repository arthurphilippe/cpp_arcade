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
	: _gameEntry("./games/SolarFox/libSolarFox.so"),
	_displayEntry("./lib/SfmlDisplay/libsfml.so"),
//	_displayEntry("./lib/CacaDisplay/libcaca.so"),
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
{}

int arc::GameWraper::loop()
{
	while (_running) {
		_startTime = std::chrono::high_resolution_clock::now();
		_processInteractions();
		_currGame->envUpdate();
		_currDisplay->refresh();
		_waitCycle(_currGame->getSpecs().fps);
	}
	return 0;
}

void arc::GameWraper::_waitCycle(unsigned int fps)
{
	auto finish = std::chrono::high_resolution_clock::now();
	millisec elapsed = finish - _startTime;
	millisec tempo(((61 - fps) * 100 / 60) - elapsed.count());
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
		if (find(_sysInteractions.begin(), _sysInteractions.end(),
			 inter.front()) != _sysInteractions.end())
			_processWraperInter(inter.front());
		else {
			_currGame->proccessIteraction(inter.front());
		}
		inter.pop();
	}
	_currDisplay->clear();
	_currDisplay->putItem(_currGame->getItemFromName("Seal"));
	_currDisplay->putSpritePosition(
		_currGame->getItemFromName("Bullet"),
		_currGame->getBulletPos());
	_currDisplay->putSpriteList(_currGame->getSpriteListFromName("Wall"));
	_currGame->envUpdate();
	_currDisplay->refresh();
}

void arc::GameWraper::_setItemSprites(Item &item)
{
	if (item.spritesPath.length())
		item.sprites = SpriteParser::parser(item.spritesPath);
}
