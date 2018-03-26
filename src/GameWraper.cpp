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

arc::GameWraper::GameWraper(const Startup &startup)
	: _games(startup.getGameLibs()),
	_libs(startup.getGfxLibs()),
	_currGameIdx(0),
	_currDisplayIdx(0),
	_gameEntry(_games[0]),
	_displayEntry(_libs[0]),
	_currGame(_gameEntry.get()),
	_currDisplay(_displayEntry.get()),
	_running(true)
{
	for_each(_currGame->getItems().begin(), _currGame->getItems().end(),
			 _setItemSprites);
	_currGame->dump();
	_currDisplay->clear();
	_currDisplay->putstr("kapa", 0, 0);
	_currDisplay->refresh();
	_currDisplay->setStep(_currGame->getSpecs().pixelStep);
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
		case LIB_NEXT:
			_displaySwitch(1);
			break;
		case LIB_PREV:
			_displaySwitch(-1);
			break;
		case GAME_NEXT:
			_gameSwitch(1);
			break;
		case GAME_PREV:
			_gameSwitch(-1);
			break;
		default:
			break;
	}
}

void arc::GameWraper::_processInteractions()
{
	auto inter = _currDisplay->getInteractions();
	while (inter.size() != 0) {
		bool had_action_1 = false;
		if (had_action_1 && inter.front() == ACTION_1) {
			inter.pop();
			continue;
		}
		if (find(_sysInteractions.begin(), _sysInteractions.end(),
			 inter.front()) != _sysInteractions.end())
			_processWraperInter(inter.front());
		else {
			had_action_1 = (inter.front() == ACTION_1) ? true : false;
			_currGame->proccessIteraction(inter.front());
		}
		inter.pop();
	}
	_currDisplay->clear();
	_currDisplay->putItem(_currGame->getItemFromName("Seal"));
	_currDisplay->putItem(_currGame->getItemFromName("Fruit"));
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

void arc::GameWraper::_displaySwitch(int mod)
{
	if (mod >= 0) {
		_currDisplayIdx += mod;
		if (_currDisplayIdx >= _libs.size())
			_currDisplayIdx = 0;
	} else if (_currDisplayIdx == 0) {
		_currDisplayIdx = _libs.size() - 1;
	} else {
		_currDisplayIdx += mod;
	}
	_currDisplay->~IDisplay();
	_currDisplay.release();
	_currDisplay.reset(_displayEntry.reset(_libs[_currDisplayIdx]));
	_currDisplay->setStep(_currGame->getSpecs().pixelStep);
}

void arc::GameWraper::_gameSwitch(int mod)
{
	if (mod >= 0) {
		_currGameIdx += mod;
		if (_currGameIdx >= _libs.size())
			_currGameIdx = 0;
	} else if (_currGameIdx == 0) {
		_currGameIdx = _libs.size() - 1;
	} else {
		_currGameIdx += mod;
	}
	_currGame->~IGame();
	_currGame.release();
	_currGame.reset(_gameEntry.reset(_games[_currGameIdx]));
	for_each(_currGame->getItems().begin(), _currGame->getItems().end(),
			 _setItemSprites);
	_currDisplay->setStep(_currGame->getSpecs().pixelStep);
}
