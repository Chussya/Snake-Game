#include "GameStateMainMenu.h"

#include <cassert>

namespace SnakeGame
{
	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event event)
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
			}
		}
	}

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		// Init Fonts

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Light.ttf"));

		/// Init music
		if (game.music.getStatus() != sf::Music::Playing)
		{
			assert(game.music.openFromFile(RESOURCES_PATH + "Music/menu.ogg"));

			// Music settings
			game.music.setLoop(true);
			game.music.setVolume(game.gameSettings.musicLoud);

			// Play
			game.music.play();
		} else
		{
			game.music.setVolume(game.gameSettings.musicLoud);
		}

		// Init Texts

		InitText(data.title, "SNAKE GAME", data.font, sf::Color::Yellow, 60);
		SetTextOrigin(data.title, ETextOrigin::Center);

		MenuItem<call> startGame;

		InitMenuItem<call>(
			startGame,
			"Start game",
			data.font,
			40,
			[](Game& game) { SwitchGameState(game, EGameStateType::Playing); }
		);
		SetTextOrigin(startGame.text, ETextOrigin::Center);

		MenuItem<call> complexity;

		InitMenuItem<call>(
			complexity,
			"Complexity",
			data.font,
			40,
			[](Game& game) { SwitchGameState(game, EGameStateType::Complexity); }
		);
		SetTextOrigin(complexity.text, ETextOrigin::Center);

		MenuItem<call> leaderboard;

		InitMenuItem<call>(
			leaderboard,
			"Leaderboard",
			data.font,
			40,
			[](Game& game) { SwitchGameState(game, EGameStateType::Leaderboard); }
		);
		SetTextOrigin(leaderboard.text, ETextOrigin::Center);

		MenuItem<call> options;

		InitMenuItem<call>(
			options,
			"Options",
			data.font,
			40,
			[](Game& game) { SwitchGameState(game, EGameStateType::Options); }
		);
		SetTextOrigin(options.text, ETextOrigin::Center);

		MenuItem<call> exit;

		InitMenuItem<call>(
			exit,
			"Exit",
			data.font,
			40,
			[](Game& game) { SwitchGameState(game, EGameStateType::Exit); }
		);
		SetTextOrigin(exit.text, ETextOrigin::Center);

		data.buttons.push_back(startGame);
		data.buttons.push_back(complexity);
		data.buttons.push_back(leaderboard);
		data.buttons.push_back(options);
		data.buttons.push_back(exit);

		data.it = data.buttons.begin();
	}

	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window)
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

	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game)
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

	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game)
	{
		// Nothing to do
	}
}