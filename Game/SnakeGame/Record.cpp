#include "Record.h"

#include <algorithm>

namespace SnakeGame
{
	void InitRecord(std::unordered_map<std::string, int>& records, const std::string playerName)
	{
		int maxScore = 100;

		records = {
			{playerName, 0},
		};
	}

	Records SortByScores(std::unordered_map<std::string, int> records)
	{
		Records vRecords(records.begin(), records.end());

		std::sort(vRecords.begin(), vRecords.end());

		return vRecords;
	}
}