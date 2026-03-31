#include "UtilGraphic.h"

namespace SnakeGame
{
	void InitText(sf::Text& text, std::string s, const sf::Font& font, const sf::Color colorText, const unsigned int charSize)
	{
		text.setFont(font);
		text.setFillColor(colorText);
		text.setString(s);
		text.setCharacterSize(charSize);
	}

	void InitText(sf::Text& text, std::string s, const sf::Font& font, const sf::Color colorText, const unsigned int charSize, const Position2D pos)
	{
		text.setFont(font);
		text.setFillColor(colorText);
		text.setString(s);
		text.setCharacterSize(charSize);
		text.setPosition({ pos.x, pos.y });
	}

	void SetTextOrigin(sf::Text& text, ETextOrigin textOrigin)
	{
		sf::FloatRect localRect = text.getLocalBounds();

		switch (textOrigin)
		{
		case SnakeGame::ETextOrigin::LeftTop:
			text.setOrigin(0.f, 0.f);
			break;
		case SnakeGame::ETextOrigin::MidTop:
			text.setOrigin(localRect.width / 2.f, 0.f);
			break;
		case SnakeGame::ETextOrigin::RightTop:
			text.setOrigin(localRect.width, 0.f);
			break;
		case SnakeGame::ETextOrigin::Center:
			text.setOrigin(localRect.width / 2.f, localRect.height / 2.f);
			break;
		case SnakeGame::ETextOrigin::LeftBottom:
			text.setOrigin(0.f, localRect.height);
			break;
		case SnakeGame::ETextOrigin::MidBottom:
			text.setOrigin(localRect.width / 2.f, localRect.height);
			break;
		case SnakeGame::ETextOrigin::RightBottom:
			text.setOrigin(localRect.width, localRect.height);
			break;
		default:
			text.setOrigin(0.f, 0.f);
			break;
		}
	}
}