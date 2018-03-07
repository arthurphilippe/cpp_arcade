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
	if (ac < 2)
		return 84;
	try {
		SpriteParser::parser(av[1]);
	}
	catch (const ParserError &error)
	{
		error.what();
	};
	return 0;
}
