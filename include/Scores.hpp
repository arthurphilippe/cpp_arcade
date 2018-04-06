/*
** EPITECH PROJECT, 2018
** cpp_arcade
** File description:
** Scores
*/

#ifndef SCORES_HPP_
	#define SCORES_HPP_

	#include <string>
	#include <list>
	#include <iostream>
	#include <fstream>

namespace arc {
	class Scores;

	struct ScoreEntry {
		std::string	se_playerName;
		int		se_scoreCount;
	};
}

class arc::Scores {
public:
	Scores(const std::string &game);
	~Scores();
	void addScore(const std::string &player, int score);
	int getHighscore() const noexcept
	{
		if (_scoresList.begin() == _scoresList.end())
			return 0;
		return _scoresList.begin()->se_scoreCount;
	}
	std::string getBestPlayer() const noexcept
	{
		if (_scoresList.begin() == _scoresList.end())
			return "nobody";
		return _scoresList.begin()->se_playerName;
	}
private:
	std::string		_gameName;
	std::fstream		_file;
	std::list<ScoreEntry>	_scoresList;
	bool			_modified;

	static bool _scoreCmp(const ScoreEntry &a,
				const ScoreEntry &b) noexcept
	{
		return (a.se_scoreCount > b.se_scoreCount);
	}
	void _sortScoreEntries() noexcept
	{
		_scoresList.sort(_scoreCmp);
	}
	static std::string getGameName(const std::string &libName) noexcept;
	bool _loadFromFile() noexcept;
	void _dumpToFile();
};

#endif /* !SCORES_HPP_ */
