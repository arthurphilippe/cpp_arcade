/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** GameWraper
*/

#ifndef GAMEWARPER_HPP_
	#define GAMEWARPER_HPP_

	#include <string>
	#include <memory>
	#include <chrono>
	#include <thread>
	#include <functional>
	#include "IGame.hpp"
	#include "IDisplay.hpp"
	#include "DynamicObject.hpp"
	#include "Arc.hpp"
	#include "Startup.hpp"

namespace arc {
	class GameWraper;
	using millisec = std::chrono::duration<double, std::milli>;
}

class arc::GameWraper {
public:
	GameWraper(const Startup &startup);
	~GameWraper();

	int loop();
protected:
private:
	libArray			_games;
	libArray			_libs;
	uint				_currGameIdx;
	uint				_currDisplayIdx;
	DynamicObject<IGame>		_gameEntry;
	DynamicObject<IDisplay>		_displayEntry;
	std::unique_ptr<IGame>		_currGame;
	std::unique_ptr<IDisplay>	_currDisplay;

	void _processWraperInter(Interaction &iter);
	void _processInteractions();
	static const std::vector<Interaction> _sysInteractions;
	static void _setItemSprites(Item &item);
	void _waitCycle(unsigned int fps);
	void _displaySwitch(int mod);
	void _gameSwitch(int mod);

	std::chrono::high_resolution_clock::time_point _startTime;
	bool _running;
};

#endif /* !GAMEWARPER_HPP_ */
