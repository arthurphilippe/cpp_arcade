/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Main
*/

#include <iostream>
#include <dlfcn.h>
#include <functional>
#include <memory>
#include "IGame.hpp"
#include "DynamicFunc.hpp"
#include "IDisplay.hpp"
#include "SpriteParser.hpp"
#include "Error.hpp"

int main()
{
	std::cout << "Hi :3" << std::endl;
	arc::DynamicFunc<arc::IGame *(*)()>
		entry("./games/Pacman/libPacman.so");

	arc::IGame *test = entry.get()();
	test->dump();
	delete test;

	// arc::DynamicFunc<arc::IDisplay *(*)()>
	// 	gfxcaca("./lib/CacaDisplay/libcaca.so");
	// auto caca = gfxcaca.get()();
	// caca->putstr("kaka");
	// caca->waitEvent();
	// delete caca;

	arc::DynamicFunc<arc::IDisplay *(*)()>
		gfx("./lib/SfmlDisplay/libsfml.so");
	auto sfml = gfx.get()();
	sfml->putstr("kaka");
	sfml->refresh();
	sfml->waitEvent();
	delete sfml;
}
