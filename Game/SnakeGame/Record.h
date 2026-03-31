#pragma once
#include <string>
#include <unordered_map>

namespace SnakeGame
{
	typedef std::vector<std::pair<std::string, int>> Records;

	struct Record
	{
		std::string name;
		int score;
	};

	void InitRecord(std::unordered_map<std::string, int>& records, const std::string playerName);
	Records SortByScores(std::unordered_map<std::string, int> records);
}