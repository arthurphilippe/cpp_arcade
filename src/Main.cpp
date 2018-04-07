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

int main(int ac, char **av)
{
	arc::Startup start(ac, av);
	if (!start.isValid()) {
		std::cout << "There is to few or not enough arguements.";
		std::cout << std::endl;
	} else {
		try {
			arc::GameWraper toto(start);
			toto.loop();
		} catch (std::exception &err) {
			std::cout << err.what() << std::endl;
			return 84;
		}
	}
	return 0;
}
