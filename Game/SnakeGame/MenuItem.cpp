#include "MenuItem.h"

namespace SnakeGame
{
	void EditElement(std::string& playerName, sf::Font& font)
	{
		sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH_EDIT, SCREEN_HEIGHT_EDIT), "Name editor");

		sf::Text text;
		InitText(text, playerName, font, sf::Color::White, 20);
		sf::String s = text.getString();

		SetTextOrigin(text, ETextOrigin::Center);
		text.setPosition(SCREEN_WIDTH_EDIT / 2.f, SCREEN_HEIGHT_EDIT / 2.f);

		window.display();

		bool isFinished{ false };

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
				{
					window.close();
				}
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128)
					{
						if (event.text.unicode == '\b')
						{
							if (!s.isEmpty())
								s.erase(s.getSize() - 1);
						} else if (event.text.unicode == 13)
						{
							if (s.isEmpty())
							{
								playerName = DEFAULT_PLAYER_NAME;
							}
							else
							{
								playerName = s;
							}
						} else
						{
							if (s.getSize() < PLAYER_NAME_LENGTH)
							{
								s += event.text.unicode;
							}
						}
						text.setString(s);
					}
					SetTextOrigin(text, ETextOrigin::Center);
					text.setPosition(SCREEN_WIDTH_EDIT / 2.f, SCREEN_HEIGHT_EDIT / 2.f);
				}
			}
			window.clear();
			window.draw(text);
			window.display();
		}
	}
}
