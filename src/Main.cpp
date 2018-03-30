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
#include "IDisplay.hpp"
#include "Error.hpp"
#include "Startup.hpp"
#include "GameWraper.hpp"

#include "../games/SolarFox/include/SolarFox.hpp"

int main()
{
	arc::Startup start;
	arc::GameWraper toto(start);
	toto.loop();
}
