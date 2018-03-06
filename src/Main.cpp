/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Main
*/

#include <iostream>
#include "SpriteParser.hpp"
#include "Error.hpp"

int main(int ac, char **av)
{
	try {
		SpriteParser::Parser(av[1]);
	}
	catch (const ParserError &error)
	{
		error.printError();
	};
}
