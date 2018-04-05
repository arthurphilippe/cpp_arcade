/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** GameWraper
*/

#include <iostream>
#include <algorithm>
#include "unistd.h"
#include "GameWraper.hpp"

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
		if (_currGame->isOver()) {
			_running = false;
		}
	}
	std::cout << "score " << _currGame->getScore() << std::endl;
	return 0;
}

void arc::GameWraper::_waitCycle(unsigned int fps)
{
	if (fps > 60)
		fps = 60;
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
	bool had_action_1 = false;

	while (inter.size() != 0) {
		_currGame->envUpdate();
		if (had_action_1 && inter.front() == ACTION_1) {
			inter.pop();
			continue;
		}
		if (find(_sysInteractions.begin(), _sysInteractions.end(),
			inter.front()) != _sysInteractions.end())
			_processWraperInter(inter.front());
		else {
			had_action_1 = (inter.front() == ACTION_1) ? true : false;
			_currGame->processInteraction(inter.front());
		}
		inter.pop();
	}
	_currGame->envUpdate();
	_currDisplay->clear();
	for (auto i = _currGame->getItems().begin();
		i != _currGame->getItems().end(); i++)
		_currDisplay->putItem(*i);
	_currDisplay->refresh();
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
	_currDisplay->setStep(_currGame->getSpecs().pixelStep);
}
