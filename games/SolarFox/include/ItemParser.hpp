/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** ItemParser
*/

#ifndef ITEMPARSER_HPP_
	#define ITEMPARSER_HPP_

	#include "SolarFox.hpp"

namespace arc {
	class ItemParser;
}

class arc::ItemParser {
public:
	ItemParser() = delete;
	~ItemParser() = delete;
	using FlagMap = std::unordered_map<std::string, arc::Attribute>;
	using MapColor = std::unordered_map<std::string, arc::Color>;
	static const std::string getAttribute();
	static std::string _line;
	static arc::Item createItem();
	static std::string setName();
	static Sprite createSprite();
	static arc::Item createItem(const std::string &path, int x, int y);
private:
	static int getIndex(const std::string &what);
	static std::string getInfo(const std::string &what);
	static arc::Attribute setFlag();
	static std::string setPath();
	static char setSubstitute();
	static Color setColor();
	static SpriteList _vector;
	static int _nbrline;
	static Color _color;
};

#endif /* !ITEMPARSER_HPP_ */
