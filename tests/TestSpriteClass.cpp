/*
** EPITECH PROJECT, 2017
** Arcade
** File description:
** Tests
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include "Sprite.hpp"

Test(getName, SpriteClass) {
	arc::Sprite sprite("DontBlameMe", "/src/", 'c');

	cr_assert_str_eq(sprite.getName().c_str(), "DontBlameMe");
}

Test(getPath, SpriteClass) {
	arc::Sprite sprite("DontBlameMe", "/src/", 'c');

	cr_assert_str_eq(sprite.getPath().c_str(), "/src/");
}

Test(getSubstitute, SpriteClass) {
	arc::Sprite sprite("DontBlameMe", "/src/", 'c');

	cr_assert_eq(sprite.getSubstitute(), 'c');
}

Test(setName, SpriteClass) {
	arc::Sprite sprite("DontBlameMe", "/src/", 'c');

	sprite.setName("LoveMeMakeMeCrazy");
	cr_assert_str_eq(sprite.getName().c_str(), "LoveMeMakeMeCrazy");
}

Test(setPath, SpriteClass) {
	arc::Sprite sprite("DontBlameMe", "/src/", 'c');

	sprite.setPath("/lib/");
	cr_assert_str_eq(sprite.getPath().c_str(), "/lib/");
}

Test(setSubstitute, SpriteClass) {
	arc::Sprite sprite("DontBlameMe", "/src/", 'c');

	sprite.setSubstitute('a');
	cr_assert_eq(sprite.getSubstitute(), 'a');
}

