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
	_file(_gameName + ".score"),
	_scoresList(),
	_modified(false)
{
	_loadFromFile();
}

arc::Scores::~Scores()
{
	if (_modified) {
		_sortScoreEntries();
		_dumpToFile();
	}
}

void arc::Scores::addScore(const std::string &player, int score)
{
	_scoresList.push_back((ScoreEntry) {player, score});
	_modified = true;
}

std::string arc::Scores::getGameName(const std::string &libName) noexcept
{
	auto gameName = libName.substr(libName.find("lib") + 3,
					libName.find(".so") - 3);
	while (gameName.find("lib") != std::string::npos)
		gameName = gameName.substr(gameName.find("lib") + 3,
						gameName.length() - 3);
	return gameName;
}

bool arc::Scores::_loadFromFile() noexcept
{
	// if (!_file.is_open())
	// 	return false;
	std::string line;
	while (getline(_file ,line)) {
		std::cout << "lol " << line << std::endl;
		auto playerName = line.substr(0, line.find(":"));
		auto scoreCount = line.substr(line.find(":") + 1, line.length() - 1);
		std::cout << "lol " << playerName << "--" << scoreCount << std::endl;
		_scoresList.push_back(
			(ScoreEntry) {playerName, std::stoi(scoreCount)});
	}
	return true;
}

void arc::Scores::_dumpToFile()
{
	std::ofstream file(_gameName + ".score");
	for (auto it = _scoresList.begin(); it != _scoresList.end(); it++) {
		file << it->se_playerName << ":" << it->se_scoreCount;
		file << std::endl;
		std::cout << it->se_playerName << ":" << it->se_scoreCount;
		std::cout << std::endl;
	}
}
