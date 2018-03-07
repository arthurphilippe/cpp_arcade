#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "SpriteParser.hpp"
#include "Error.hpp"

constexpr auto REAL_CONF_FILE("tests/SpriteConfigurationFiles/RealConfigurationFile.conf");
constexpr auto NOT_EXISTANT_FILE("nothere");
	

Test(FunctionnalTest, SpriteParser) {
	cr_assert_none_throw(SpriteParser::parser(REAL_CONF_FILE));	
}

Test(FileNotExists, SpriteParser) {
	cr_assert_throw(SpriteParser::parser(NOT_EXISTANT_FILE), ParserError);
	
}
