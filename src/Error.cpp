//
// EPITECH PROJECT, 2018
// Aracade
// File description:
// Errors CPP
//

#include "Error.hpp"
#include "ItemParser.hpp"

arc::ParserError::ParserError(const std::string &what)
{
	_what = arc::ERR_CONF + std::to_string(
		arc::ItemParser::getErrorLineNb()) + ": "
		+ arc::ItemParser::getErrorLine()
		+ what;
}
