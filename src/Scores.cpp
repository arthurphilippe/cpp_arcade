/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Scores
*/

#include <iostream>
#include "Scores.hpp"

arc::Scores::Scores(const std::string &gameLibName)
	: _gameName(getGameName(gameLibName)),
	_file(_gameName + ".score", std::ios::in | std::ios::out | std::ios::binary),
	_scoresList(),
	_modified(false)
{
	std::cout << "constructed" << std::endl;
	if (!_file.is_open())
		std::cout << "file aint open\n";

}

arc::Scores::~Scores()
{
	if (_modified)
		_dumpToFile();
}

void arc::Scores::addScore(const std::string &player, int score)
{
	_scoresList.push_back((ScoreEntry) {player, score});
	_modified = true;
}

std::string arc::Scores::getGameName(const std::string &libName) noexcept
{
	auto gameName = libName.substr(libName.find("lib") + 3,
					libName.find(".so"));
	while (gameName.find("lib") != std::string::npos)
		gameName = gameName.substr(gameName.find("lib") + 3,
						gameName.length());
	return gameName;
}

bool arc::Scores::_loadFromFile() noexcept
{
	if (!_file.is_open())
		return false;
	std::string line;
	while (getline(_file ,line)) {
		auto playerName = line.substr(0, line.find(":"));
		auto scoreCount = line.substr(line.find(":"), line.length());
		_scoresList.push_back(
			(ScoreEntry) {playerName, std::stoi(scoreCount)});
	}
	return true;
}

void arc::Scores::_dumpToFile()
{
	_file.seekp(0);
	for (auto it = _scoresList.begin(); it != _scoresList.end(); it++) {
		_file << it->se_playerName << ":" << it->se_scoreCount;
		_file << std::endl;
		std::cout << it->se_playerName << ":" << it->se_scoreCount;
		std::cout << std::endl;
	}
}
