#include "GameStateOptions.h"

#include <cassert>

namespace SnakeGame
{
	void HandleGameStateOptionsWindowEvent(GameStateOptionsData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::B || event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, EGameStateType::MainMenu);
			} else if (event.key.code == sf::Keyboard::W)
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
				if (data.it->second.getFillColor() == sf::Color::Green)
				{
					data.it->second.setFillColor(sf::Color::Black);
					data.it->first.callFunc(game, false);
				} else
				{
					data.it->second.setFillColor(sf::Color::Green);
					data.it->first.callFunc(game, true);
				}
			}
		}
	}

	void InitGameStateOptions(GameStateOptionsData & data, Game & game)
	{
		// Init Fonts

		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Light.ttf"));

		// Init Texts

		InitText(data.title, "OPTIONS", data.font, sf::Color::Yellow, 60);
		SetTextOrigin(data.title, ETextOrigin::Center);

		MenuItem<optionsCall> Sound;

		InitMenuItem<optionsCall>(
			Sound,
			"Sound",
			data.font,
			40,
			[](Game& game, bool isTurnOn) { isTurnOn ? game.gameSettings.soundLoud = 20.f : game.gameSettings.soundLoud = 0.f; }
		);
		SetTextOrigin(Sound.text, ETextOrigin::LeftTop);

		sf::RectangleShape soundCheckbox;
		soundCheckbox.setSize({ 40.f, 40.f });
		soundCheckbox.setOutlineColor(sf::Color::White);
		soundCheckbox.setOutlineThickness(2.f);
		soundCheckbox.setFillColor(game.gameSettings.soundLoud > 0.f ? sf::Color::Green : sf::Color::Black);

		MenuItem<optionsCall> Music;

		InitMenuItem<optionsCall>(
			Music,
			"Music",
			data.font,
			40,
			[](Game& game, bool isTurnOn) { isTurnOn ? game.gameSettings.musicLoud = 20.f : game.gameSettings.musicLoud = 0.f; }
		);
		SetTextOrigin(Music.text, ETextOrigin::LeftTop);

		sf::RectangleShape musicCheckbox;
		musicCheckbox.setSize({ 40.f, 40.f });
		musicCheckbox.setOutlineColor(sf::Color::White);
		musicCheckbox.setOutlineThickness(2.f);
		musicCheckbox.setFillColor(game.gameSettings.musicLoud > 0.f ? sf::Color::Green : sf::Color::Black);

		data.buttons.push_back({ Sound, soundCheckbox });
		data.buttons.push_back({ Music, musicCheckbox });

		data.it = data.buttons.begin();
	}

	void DrawGameStateOptions(GameStateOptionsData & data, Game & game, sf::RenderWindow & window)
	{
		float yCoordinate = 30.f;

		data.title.setPosition(window.getSize().x / 2.f, yCoordinate);
		window.draw(data.title);

		yCoordinate += 100.f;

		for (auto& button : data.buttons)
		{
			button.second.setPosition(500.f, yCoordinate);
			window.draw(button.second);

			button.first.text.setPosition(300.f, yCoordinate);
			DrawMenuItem(button.first, window);
			yCoordinate += 80.f;
		}
	}

	void UpdateGameStateOptions(GameStateOptionsData & data, Game & game)
	{
		for (auto it = data.buttons.begin(); it != data.buttons.end(); ++it)
		{
			if (it->first == data.it->first)
			{
				OnFocus(it->first);
			} else
			{
				LostFocus(it->first);
			}
		}
	}

	void ShutdownGameStateOptions(GameStateOptionsData & data, Game & game)
	{
		// Nothing to do
	}
}