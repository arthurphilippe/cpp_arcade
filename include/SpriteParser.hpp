/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** SpriteParser
*/

#ifndef SRPITE_PARSER_H_
	#define SRPITE_PARSER_H_

#include <vector>
#include "Sprite.hpp"

namespace arc {
	class SpriteParser;
};

class arc::SpriteParser {
public:
	SpriteParser() = delete;
	~SpriteParser() = delete;
	static arc::SpriteList parser(const std::string &folder);
	static const std::string &getErrorLine();
	static const int &getErrorLineNb();
private:
	static Sprite createSprite(const std::string &path,
					const char &substitute,
					const std::string &name) noexcept;
	static std::string modifyFolder(std::string foldername);
	static void parseLine();
	static void readFile(const std::string &name);

	static std::string setName();
	static std::string setPath();
	static char setSubstitute();

	static arc::SpriteList _vector;
	static std::string _line;
	static int _nbrline;
};

#endif /* SRPITE_PARSER_H_ */
