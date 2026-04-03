#include "GameStateGameOver.h"

#include <string>
#include <cassert>

#include "Record.h"
#include "UtilString.h"
#include "UtilGraphic.h"

namespace SnakeGame
{
	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event event)
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

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		// Init fonts
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));
		assert(data.recordsFont.loadFromFile(RESOURCES_PATH + "Fonts/consola.ttf"));

		// Actualize records
		PopUpNewRecord(data, game);

		// Sort records
		Records records = SortByScores(game.records);

		if (records.size() > data.maxRecords)
		{
			records.resize(data.maxRecords);
		}

		// Leaderboard definition
		std::string tableOfLeaders;

		tableOfLeaders = stringCenter("LEADERBOARD", SYM_TITLE, ROW_LENGTH);
		tableOfLeaders.push_back('\n');

		for (auto record : records)
		{
			tableOfLeaders.append(stringFormat(record.first, std::to_string(record.second), SYM_SEPARATE, ROW_LENGTH)).push_back('\n');
		}

		std::string end = "";
		end.resize(ROW_LENGTH, '=');
		tableOfLeaders.append(end);

		// Init texts
		InitText(data.gameOverText, "GAME OVER", data.font, sf::Color::Red, 40);
		SetTextOrigin(data.gameOverText, ETextOrigin::Center);

		InitText(data.leaderBoardText, tableOfLeaders, data.recordsFont, sf::Color::White, 25);
		SetTextOrigin(data.leaderBoardText, ETextOrigin::Center);

		// Init menu items

		MenuItem<call> continueGame;

		InitMenuItem<call>(
			continueGame,
			"Continue",
			data.font,
			30,
			[](Game& game) { SwitchGameState(game, EGameStateType::Playing); }
		);
		SetTextOrigin(continueGame.text, ETextOrigin::Center);

		MenuItem<call> exitMenu;

		InitMenuItem<call>(
			exitMenu,
			"Menu",
			data.font,
			30,
			[](Game& game) { SwitchGameState(game, EGameStateType::MainMenu); }
		);
		SetTextOrigin(exitMenu.text, ETextOrigin::Center);

		data.buttons.push_back(continueGame);
		data.buttons.push_back(exitMenu);

		data.it = data.buttons.begin();
	}

	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window)
	{
		float yCoordinate = 30.f;

		// Set position
		data.gameOverText.setPosition(SCREEN_WIDTH_GAME / 2, yCoordinate);
		data.leaderBoardText.setPosition(SCREEN_WIDTH_GAME / 2, SCREEN_HEIGHT_GAME / 2);

		yCoordinate = 500.f;

		for (auto& button : data.buttons)
		{
			button.text.setPosition(window.getSize().x / 2.f, yCoordinate);
			DrawMenuItem(button, window);
			yCoordinate += 60.f;
		}

		// Draw game over window
		window.draw(data.gameOverText);
		window.draw(data.leaderBoardText);
	}

	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game)
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

	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game)
	{
		// Nothing to do
	}

	void PopUpNewRecord(GameStateGameOverData& data, Game& game)
	{
		sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH_POPUP, SCREEN_HEIGHT_POPUP), "Save record window");

		// Init texts and menu items

		sf::Text title;

		InitText(title, "Save new record as new?", data.font, sf::Color::White, 40);
		SetTextOrigin(title, ETextOrigin::Center);
		title.setPosition(SCREEN_WIDTH_POPUP / 2.f, 100);

		MenuItem<std::function<void()>> no;

		InitMenuItem<std::function<void()>>(
			no,
			"No",
			data.font,
			30,
			[](){}	// no need function
		);
		SetTextOrigin(no.text, ETextOrigin::Center);
		no.text.setPosition(window.getSize().x / 2.f, 200);
		OnFocus(no);

		MenuItem<std::function<void()>> yes;

		InitMenuItem<std::function<void()>>(
			yes,
			"Yes",
			data.font,
			30,
			[]() {}	// no need function
		);
		SetTextOrigin(yes.text, ETextOrigin::Center);
		yes.text.setPosition(window.getSize().x / 2.f, 250);

		window.display();

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
					{
						if (yes.onFocus)
						{
							LostFocus(yes);
							OnFocus(no);
						} else
						{
							LostFocus(no);
							OnFocus(yes);
						}
					} else if (event.key.code == sf::Keyboard::Enter)
					{
						if (yes.onFocus)
						{
							std::string playerName = DEFAULT_PLAYER_NAME;

							EditElement(playerName, data.font);

							if (game.records.size() == 1 && game.records.begin()->second == 0)
							{
								game.records.clear();
								game.records.insert({ playerName, *game.ptrPlayerScores });
							}
							else if (game.records.find(playerName) != game.records.end())
							{
								game.records[playerName] = *game.ptrPlayerScores;
							}
							else
							{
								game.records.insert({ playerName, *game.ptrPlayerScores });
							}
							window.close();
						} else
						{
							game.records[game.gameSettings.playerName] = *game.ptrPlayerScores;
							window.close();
						}
					}
				}
			}
			window.clear();

			window.draw(title);
			DrawMenuItem(no, window);
			DrawMenuItem(yes, window);

			window.display();
		}
	}
}