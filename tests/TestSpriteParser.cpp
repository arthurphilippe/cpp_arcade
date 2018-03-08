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
	

Test(FunctionnalTest, SpriteParser) {
	cr_assert_none_throw(arc::SpriteParser::parser(REAL_CONF_FILE));	
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
