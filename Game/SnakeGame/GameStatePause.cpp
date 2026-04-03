#include "GameStatePause.h"

#include <cassert>

namespace SnakeGame
{
	void HandleGameStatePauseWindowEvent(GameStatePauseData& data, Game& game, const sf::Event event)
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
			} else if (!data.isWaiting && event.key.code == sf::Keyboard::Enter)
			{
				if (data.it->text.getString() == "Continue")
				{
					data.delayClock.restart();
					data.isWaiting = true;

				} else
				{
					data.it->callFunc(game);
				}
			}
		}
	}

	void InitGameStatePause(GameStatePauseData& data, Game& game)
	{
		// Init Fonts

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Light.ttf"));

		// Init Texts

		InitText(data.title, "PAUSE", data.font, sf::Color::Yellow, 40);
		SetTextOrigin(data.title, ETextOrigin::Center);

		InitText(data.timer, data.timerText, data.font, sf::Color::Yellow, 50);
		SetTextOrigin(data.timer, ETextOrigin::Center);

		MenuItem<call> exitMenu;
		InitMenuItem<call>(
			exitMenu,
			"Menu",
			data.font,
			30,
			[](Game& game) { SwitchGameState(game, EGameStateType::MainMenu); }
		);
		SetTextOrigin(exitMenu.text, ETextOrigin::Center);

		MenuItem<call> continueGame;

		InitMenuItem<call>(
			continueGame,
			"Continue",
			data.font,
			30,
			[](Game& game) { PopGameState(game); }
		);
		SetTextOrigin(continueGame.text, ETextOrigin::Center);
		
		data.buttons.push_back(exitMenu);
		data.buttons.push_back(continueGame);

		data.it = data.buttons.begin();
	}

	void DrawGameStatePause(GameStatePauseData& data, Game& game, sf::RenderWindow& window)
	{
		data.title.setPosition(SCREEN_WIDTH_GAME / 2.f, 200.f);
		window.draw(data.title);

		if (!data.isWaiting)
		{
			float yCoordinate = 400.f;

			for (auto& button : data.buttons)
			{
				button.text.setPosition(window.getSize().x / 2.f, yCoordinate);
				DrawMenuItem(button, window);
				yCoordinate += 80.f;
			}
		} else
		{
			data.timer.setPosition(SCREEN_WIDTH_GAME / 2.f, 400.f);
			window.draw(data.timer);
		}
	}

	void UpdateGameStatePause(GameStatePauseData& data, Game& game)
	{
		if (!data.isWaiting)
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
		} else
		{
			data.timer.setString(data.timerText + std::to_string(static_cast<int>(data.delayTime + 1 - data.delayClock.getElapsedTime().asSeconds())));

			if (data.delayClock.getElapsedTime().asSeconds() >= data.delayTime)
			{
				data.it->callFunc(game);
			}
		}
	}

	void ShutdownGameStatePause(GameStatePauseData& data, Game& game)
	{
		// Nothing to do
	}
}
