#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "ItemParser.hpp"
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


Test(FunctionnalTest, ItemParser) {

	auto kappa = arc::ItemParser::parser(REAL_CONF_FILE);
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

Test(FileNotExists, ItemParser) {
	cr_assert_throw(arc::ItemParser::parser(NOT_EXISTANT_FILE), arc::ParserError);

}

Test(ErrorName, ItemParser) {
	cr_assert_throw(arc::ItemParser::parser(CONF_FILE_ERR_NAME), arc::ParserError);
}

Test(ErrorSub, ItemParser) {
	cr_assert_throw(arc::ItemParser::parser(CONF_FILE_ERR_SUB), arc::ParserError);

}

Test(ErrorPath, ItemParser) {
	cr_assert_throw(arc::ItemParser::parser(CONF_FILE_ERR_PATH), arc::ParserError);
}

Test(ErrorColor, ItemParser) {
	cr_assert_throw(arc::ItemParser::parser(CONF_FILE_ERR_COLOR), arc::ParserError);
}
