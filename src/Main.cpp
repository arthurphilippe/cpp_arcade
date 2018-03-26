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
#include "Startup.hpp"
#include "GameWraper.hpp"

int main()
{
	arc::Startup start(".", ".");
	arc::GameWraper toto;
	toto.loop();
}
