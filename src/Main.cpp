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

int main()
{
	std::cout << "Hi :3" << std::endl;
	arc::DynamicFunc<arc::IGame *(*)()>
		entry("./games/DefaultGame/libDefaultGame.so");

	arc::IGame *test = entry.get()();
	test->dump();
	delete test;
}
