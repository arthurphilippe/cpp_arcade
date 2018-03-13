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
	#include "IGame.hpp"
	#include "IDisplay.hpp"
	#include "DynamicFunc.hpp"
	#include "Arc.hpp"

namespace arc {
	class GameWraper;
}

class arc::GameWraper {
public:
	GameWraper();
	~GameWraper();

	int loop();
protected:
private:
	DynamicFunc<IGame *(*)()>	_gameEntry;
	DynamicFunc<IDisplay *(*)()>	_displayEntry;
	std::unique_ptr<IGame>		_currGame;
	std::unique_ptr<IDisplay>	_currDisplay;

	void _processWraperInter(Interaction &iter);
	void _processInteractions();
	static const std::vector<Interaction> _sysInteractions;
	static void _setItemSprites(Item &item);
	void _waitCycle(size_t fps);

	std::chrono::high_resolution_clock::time_point _startTime;
	bool _running;
};

#endif /* !GAMEWARPER_HPP_ */
