//
// EPITECH PROJECT, 2018
// Aracade
// File description:
// Errors CPP
//

#include "Error.hpp"
#include "SpriteParser.hpp"

arc::ParserError::ParserError(const std::string &what)
{
	_what = arc::ERR_CONF + std::to_string(
		arc::SpriteParser::getErrorLineNb()) + ": "
		+ arc::SpriteParser::getErrorLine()
		+ what;
}
