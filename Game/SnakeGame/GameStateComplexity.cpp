#include "GameStateComplexity.h"

#include <cassert>

namespace SnakeGame
{
	void HandleGameStateComplexityWindowEvent(GameStateComplexityData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::W)
			{
				if (data.it == data.buttons.begin())
				{
					data.it = data.buttons.end();
				}
				--data.it;
			} else if (event.key.code == sf::Keyboard::S)
			{
				++data.it;

				if (data.it == data.buttons.end())
				{
					data.it = data.buttons.begin();
				}
			} else if (event.key.code == sf::Keyboard::Enter)
			{
				data.it->callFunc(game);
				SwitchGameState(game, EGameStateType::MainMenu);
			} else if (event.key.code == sf::Keyboard::B)
			{
				SwitchGameState(game, EGameStateType::MainMenu);
			}
		}
	}

	void InitGameStateComplexity(GameStateComplexityData& data, Game& game)
	{
		// Init Fonts

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Light.ttf"));

		// Init Texts

		InitText(data.title, "COMPLEXITY", data.font, sf::Color::Yellow, 60);
		SetTextOrigin(data.title, ETextOrigin::Center);

		MenuItem<call> paradise;

		InitMenuItem<call>(
			paradise,
			"Paradise",
			data.font,
			40,
			[](Game& game) { game.gameSettings.appleBonus = BONUS_PARADISE; game.gameSettings.timeInterval = TIME_INTERVAL_PARADISE; }
		);
		SetTextOrigin(paradise.text, ETextOrigin::Center);

		MenuItem<call> easy;

		InitMenuItem<call>(
			easy,
			"Easy",
			data.font,
			40,
			[](Game& game) { game.gameSettings.appleBonus = BONUS_EASY; game.gameSettings.timeInterval = TIME_INTERVAL_EASY; }
		);
		SetTextOrigin(easy.text, ETextOrigin::Center);

		MenuItem<call> normal;

		InitMenuItem<call>(
			normal,
			"Normal",
			data.font,
			40,
			[](Game& game) { game.gameSettings.appleBonus = BONUS_NORMAL; game.gameSettings.timeInterval = TIME_INTERVAL_NORMAL; }
		);
		SetTextOrigin(normal.text, ETextOrigin::Center);

		MenuItem<call> hard;

		InitMenuItem<call>(
			hard,
			"Hard",
			data.font,
			40,
			[](Game& game) { game.gameSettings.appleBonus = BONUS_HARD; game.gameSettings.timeInterval = TIME_INTERVAL_HARD; }
		);
		SetTextOrigin(hard.text, ETextOrigin::Center);

		MenuItem<call> hell;

		InitMenuItem<call>(
			hell,
			"Hell",
			data.font,
			40,
			[](Game& game) { game.gameSettings.appleBonus = BONUS_HELL; game.gameSettings.timeInterval = TIME_INTERVAL_HELL; }
		);
		SetTextOrigin(hell.text, ETextOrigin::Center);

		data.buttons.push_back(paradise);
		data.buttons.push_back(easy);
		data.buttons.push_back(normal);
		data.buttons.push_back(hard);
		data.buttons.push_back(hell);

		data.it = data.buttons.begin();
	}

	void DrawGameStateComplexity(GameStateComplexityData& data, Game& game, sf::RenderWindow& window)
	{
		float yCoordinate = 30.f;

		data.title.setPosition(window.getSize().x / 2.f, yCoordinate);
		window.draw(data.title);

		yCoordinate += 100.f;

		for (auto& button : data.buttons)
		{
			button.text.setPosition(window.getSize().x / 2.f, yCoordinate);
			DrawMenuItem(button, window);
			yCoordinate += 80.f;
		}
	}

	void UpdateGameStateComplexity(GameStateComplexityData& data, Game& game)
	{
		for (auto it = data.buttons.begin(); it != data.buttons.end(); ++it)
		{
			if (*it == *data.it)
			{
				OnFocus(*it);
			} else
			{
				LostFocus(*it);
			}
		}
	}

	void ShutdownGameStateComplexity(GameStateComplexityData& data, Game& game)
	{
		// Nothing to do
	}
}