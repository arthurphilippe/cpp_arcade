/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Main
*/

#include <iostream>
#include <functional>
#include <memory>
#include "IGame.hpp"
#include "DynamicFunc.hpp"
#include "IDisplay.hpp"
#include "SpriteParser.hpp"
#include "Error.hpp"
#include "GameWraper.hpp"

int main()
{
	arc::GameWraper toto;
	toto.loop();
	// std::cout << "Hi :3" << std::endl;
	// arc::DynamicFunc<arc::IGame *(*)()>
	// 	entry("./games/Pacman/libPacman.so");

	// std::unique_ptr<arc::IGame> test(entry.get()());
	// test->dump();

	// arc::DynamicFunc<arc::IDisplay *(*)()>
	// 	gfxcaca("./lib/CacaDisplay/libcaca.so");
	// auto caca = gfxcaca.get()();
	// caca->putstr("kaka");
	// caca->waitEvent();
	// delete caca;

	// arc::DynamicFunc<arc::IDisplay *(*)()>
	// 	gfx("./lib/SfmlDisplay/libsfml.so");
	// auto sfml = gfx.get()();
	// sfml->putstr("kaka");
	// sfml->refresh();
	// sfml->waitEvent();
	// delete sfml;
}
