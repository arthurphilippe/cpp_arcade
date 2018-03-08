//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// SpriteParser
//

#include <vector>
#include "Sprite.hpp"

namespace arc {
	class SpriteParser;
};

class arc::SpriteParser {
public:
	SpriteParser() = delete;
	~SpriteParser() = delete;
	static std::vector<Sprite> parser(const std::string &folder);
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

	static std::vector<Sprite> _vector;
	static std::string _line;
	static int _nbrline;
};
