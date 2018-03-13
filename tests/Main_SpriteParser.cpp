#include <iostream>
#include <functional>
#include <memory>
#include "IGame.hpp"
#include "DynamicFunc.hpp"
#include "IDisplay.hpp"
#include "SpriteParser.hpp"
#include "Error.hpp"
#include "GameWarper.hpp"


int main(int ac, char **av)
{
	if (ac > 1) {
		try {
			arc::SpriteParser::parser(av[1]);
		}
		catch (const arc::ParserError &error)
		{
			error.what();
			return (0);
		};
	}
	else
		std::cout << "BITCH U BETTER HAD MY MONNEY" << std::endl;
	return 0;
}