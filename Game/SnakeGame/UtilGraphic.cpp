#include "UtilGraphic.h"

namespace SnakeGame
{
	void InitText(sf::Text& text, std::string s, sf::Font& font, sf::Color colorText, unsigned int charSize)
	{
		text.setFont(font);
		text.setFillColor(colorText);
		text.setString(s);
		text.setCharacterSize(charSize);
	}

	void SetTextOrigin(sf::Text& text, TextOrigin textOrigin)
	{
		sf::FloatRect localRect = text.getLocalBounds();

		switch (textOrigin)
		{
		case SnakeGame::TextOrigin::LeftTop:
			text.setOrigin(0.f, 0.f);
			break;
		case SnakeGame::TextOrigin::MidTop:
			text.setOrigin(localRect.width / 2.f, 0.f);
			break;
		case SnakeGame::TextOrigin::RightTop:
			text.setOrigin(localRect.width, 0.f);
			break;
		case SnakeGame::TextOrigin::Center:
			text.setOrigin(localRect.width / 2.f, localRect.height / 2.f);
			break;
		case SnakeGame::TextOrigin::LeftBottom:
			text.setOrigin(0.f, localRect.height);
			break;
		case SnakeGame::TextOrigin::MidBottom:
			text.setOrigin(localRect.width / 2.f, localRect.height);
			break;
		case SnakeGame::TextOrigin::RightBottom:
			text.setOrigin(localRect.width, localRect.height);
			break;
		default:
			text.setOrigin(0.f, 0.f);
			break;
		}
	}
}