#pragma once
#include <string>

namespace SnakeGame
{
	std::string stringFormat(std::string s1, std::string s2, const char sym, const size_t length);
	std::string stringCenter(std::string s, const char sym, const size_t length);
}