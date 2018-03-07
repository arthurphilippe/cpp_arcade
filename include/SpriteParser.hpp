//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// SpriteParser
//

#include <vector>
#include "Sprite.hpp"


class SpriteParser {
public:
	SpriteParser() = delete;
	~SpriteParser() = delete;
	static std::vector<Sprite> parser(const std::string &folder);
private:
	static Sprite createSprite(const std::string &name, const std::string &path,
					const char &substitute,
					std::vector<Sprite> &_vector) noexcept;
	static std::string modifyFolder(std::string foldername);
	static std::string findType(const std::string &line) noexcept;
	static std::string findValue(const std::string &line) noexcept;
	static void readFile(const std::string &name, std::vector<Sprite> &_vector);
	static std::string setName(const std::string &line);
	static std::string setPath(const std::string &line);
	static char setSubstitute(const std::string &line);
};
