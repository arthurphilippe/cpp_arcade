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

int main(int ac, char **av)
{
	std::cout << "Hi :3" << std::endl;
	arc::DynamicFunc<arc::IGame *(*)()>
		entry("./games/DefaultGame/libDefaultGame.so");

	arc::IGame *test = entry.get()();
	test->dump();
	delete test;

	arc::DynamicFunc<arc::IDisplay *(*)()>
		gfxcaca("./lib/CacaDisplay/libcaca.so");
	auto caca = gfxcaca.get()();
	caca->putstr("kaka");
	caca->waitEvent();
	delete caca;
	
	arc::DynamicFunc<arc::IDisplay *(*)()>
		gfx("./lib/SfmlDisplay/libsfml.so");
	auto sfml = gfx.get()();
	sfml->putstr("kaka");
	sfml->display();
	sfml->waitEvent();
	delete sfml;

	if (ac < 2)
		return 84;
	try {
		arc::SpriteParser::parser(av[1]);
	}
	catch (const arc::ParserError &error)
	{
		error.what();
	};
	return 0;
}
