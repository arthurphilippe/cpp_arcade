/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Entry
*/

#include <iostream>
#include <memory>
#include "DefaultGame.hpp"

extern "C" {
	void Entry(const std::string &test)
	{
		std::cout << "kappa, i'm the entry point" << std::endl;
		std::cout << "test is: " << test << std::endl;
	}

	// std::unique_ptr<arc::IGame> GameConstruct()
	// {
	// 	std::unique_ptr<arc::DefaultGame> game(new arc::DefaultGame());
	// 	std::unique_ptr<arc::IGame> ret(std::move(game));
	// 	return game;
	// }
	arc::IGame *GameConstruct()
	{
		return new arc::DefaultGame();
	}
}
