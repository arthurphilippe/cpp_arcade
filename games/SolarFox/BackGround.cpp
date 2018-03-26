/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** BackGround Source File
*/

#include <unordered_map>
#include <fstream>
#include "Error.hpp"
#include "BackGround.hpp"

/*
**      Name:X:Y:Rotation:Subtitute:Path
*/

static const std::unordered_map<std::string, int> COREMAP = {
        {"Name", 0},
        {"X", 1},
        {"Y", 2},
        {"Rotation", 3},
        {"Substitute", 4},
        {"Color", 5},
        {"Path", 6},
};

arc::BackGround::BackGround(const std::string &filename)
        : _filename(filename)
{
        std::ifstream s(filename);
	std::string tmp;

	if (s.is_open()) {
		while (getline(s, _line)) {
			parseLine();
		}
	} else {
		throw arc::BackGroundError("Error: can't open the following file: "
                + filename);
	}
}

void arc::BackGround::parseLine()
{
        if (_line[0] != '#') {
                std::cout << getInfo("Name") << std::endl;
                std::cout << getInfo("X") << std::endl;
                std::cout << getInfo("Y") << std::endl;
                std::cout << getInfo("Rotation") << std::endl;
                std::cout << getInfo("Substitute") << std::endl;
                std::cout << getInfo("Color") << std::endl;
                std::cout << getInfo("Path") << std::endl;
        }
}

int arc::BackGround::getIndex(const std::string &what)
{
        for (auto i = COREMAP.begin(); i != COREMAP.end(); i++) {
                if (what == i->first)
                        return i->second;
        }
        return -1;
}

std::string arc::BackGround::getInfo(const std::string &what)
{
        std::string tmp = _line;

        for (int i = 0; i < getIndex(what); i ++) {
                tmp = tmp.substr(tmp.find(":") + 1, tmp.length());
        }
        tmp = tmp.substr(0, tmp.find(":"));
        return tmp;
}