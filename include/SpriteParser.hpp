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
	static std::vector<Sprite> Parser(const std::string &folder);
	void ReadFile(const std::string &name, std::vector<Sprite> &_vector);
	Sprite &createSprite(const std::string &name, const std::string &path,
			     const char substitute);
private:
	static void setName(const std::string &line) noexcept;
	static void setPath(const std::string &line) noexcept;
	static void setSubstitute(const std::string &line) noexcept;
};
