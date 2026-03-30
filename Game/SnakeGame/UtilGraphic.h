#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace SnakeGame
{
	struct Player;
	enum class PlayerDirection;

	enum class EGameWindowEvent
	{
		OnFocused = 1 << 0,
		OnClick = 1 << 1,
	};

	enum class TextOrigin
	{
		LeftTop = 0,
		MidTop,
		RightTop,
		Center,
		LeftBottom,
		MidBottom,
		RightBottom,
	};

	void InitText(sf::Text& text, std::string s, sf::Font& font, sf::Color colorText, unsigned int charSize);
	void SetTextOrigin(sf::Text& text, TextOrigin textOrigin);
}