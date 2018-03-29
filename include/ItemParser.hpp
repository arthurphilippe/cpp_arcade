/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** ItemParser
*/

#ifndef SRPITEPARSER_H_
	#define SRPITEPARSER_H_

	#include <unordered_map>
	#include <vector>
	#include "Arc.hpp"

namespace arc {
	class ItemParser;
};

class arc::ItemParser {
public:
	ItemParser() = delete;
	~ItemParser() = delete;
	static arc::SpriteList parser(const std::string &filename);
	static const std::string &getErrorLine();
	static const int &getErrorLineNb();
	using FlagMap = std::unordered_map<std::string, arc::Attribute>;
	using MapColor = std::unordered_map<std::string, arc::Color>;
	static const std::string getAttribute();
private:
	static Sprite createSprite();
	static std::string modifyFolder(std::string foldername);
	static void parseLine();
	static void readFile(const std::string &name);
	static int getIndex(const std::string &what);
	static std::string getInfo(const std::string &what);
	static arc::Attribute setFlag();
	static std::string setName();
	static std::string setPath();
	static char setSubstitute();
	static Color setColor();
	static SpriteList _vector;
	static std::string _line;
	static int _nbrline;
	static Color _color;
};

#endif /* SRPITEPARSER_H_ */
