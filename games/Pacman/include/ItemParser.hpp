/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** ItemParser
*/

#ifndef ITEMPARSER_HPP_
	#define ITEMPARSER_HPP_

	#include "Game.hpp"

namespace arc {
	class ItemParser;
}

class arc::ItemParser {
public:
	ItemParser() = delete;
	~ItemParser() = delete;
	using AttributeMap = std::unordered_map<std::string, arc::Attribute>;
	using MapColor = std::unordered_map<std::string, arc::Color>;
	static const std::string getFlag();
	static std::string _line;
	static arc::Item createItem();
	static std::string setName();
	static Sprite createSprite();
	static arc::Item createItem(const std::string &path, int x, int y);
	static void setSecondAttribute(Item &);
private:
	static int getIndex(const std::string &what);
	static std::string getInfo(const std::string &what);
	static arc::Attribute setAttribute();
	static std::string setPath();
	static char setSubstitute();
	static Color setColor();
	static SpriteList _vector;
	static int _nbrline;
	static Color _color;
};

#endif /* !ITEMPARSER_HPP_ */
