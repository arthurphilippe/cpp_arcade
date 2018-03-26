#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "SpriteParser.hpp"
#include "Error.hpp"

constexpr auto REAL_CONF_FILE("tests/SpriteConfigurationFiles/RealConfigurationFile.conf");
constexpr auto NOT_EXISTANT_FILE("nothere");
constexpr auto CONF_FILE_ERR_NAME(
	"tests/SpriteConfigurationFiles/ErrorName.conf");
constexpr auto CONF_FILE_ERR_SUB(
	"tests/SpriteConfigurationFiles/ErrorSub.conf");
constexpr auto CONF_FILE_ERR_PATH(
	"tests/SpriteConfigurationFiles/ErrorPath.conf");
constexpr auto CONF_FILE_ERR_COLOR(
	"tests/SpriteConfigurationFiles/ErrorColor.conf");


Test(FunctionnalTest, SpriteParser) {

	auto kappa = arc::SpriteParser::parser(REAL_CONF_FILE);
        cr_assert(kappa[0].color() == arc::Color::WHITE);
	cr_assert(kappa[1].color() == arc::Color::BLUE);

	cr_assert(kappa[0].name == "Pacman");
	cr_assert(kappa[1].name == "Pacman");

	cr_assert(kappa[0].substitute == 'a');
	cr_assert(kappa[1].substitute == 'b');

	cr_assert(kappa[0].path() == "sprite/pacman/potiti");
	cr_assert(kappa[1].path() == "sprite/pacman/potiti");

	cr_assert(kappa.size() == 2);
}

Test(FileNotExists, SpriteParser) {
	cr_assert_throw(arc::SpriteParser::parser(NOT_EXISTANT_FILE), arc::ParserError);

}

Test(ErrorName, SpriteParser) {
	cr_assert_throw(arc::SpriteParser::parser(CONF_FILE_ERR_NAME), arc::ParserError);
}

Test(ErrorSub, SpriteParser) {
	cr_assert_throw(arc::SpriteParser::parser(CONF_FILE_ERR_SUB), arc::ParserError);

}

Test(ErrorPath, SpriteParser) {
	cr_assert_throw(arc::SpriteParser::parser(CONF_FILE_ERR_PATH), arc::ParserError);
}

Test(ErrorColor, SpriteParser) {
	cr_assert_throw(arc::SpriteParser::parser(CONF_FILE_ERR_COLOR), arc::ParserError);
}
