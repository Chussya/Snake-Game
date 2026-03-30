#include "UtilString.h"

namespace SnakeGame
{
	std::string stringFormat(std::string s1, std::string s2, const char sym, const size_t length)
	{
		s1.resize(length - s2.length(), sym);
		return s1.append(s2);
	}

	std::string stringCenter(std::string s, const char sym, const size_t length)
	{
		std::string result = "";

		result.resize(length / 2 - s.length() / 2, sym);
		result.append(s);
		result.resize(length, sym);
		return result;
	}
}