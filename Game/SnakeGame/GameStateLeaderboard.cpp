#include "GameStateLeaderboard.h"

#include <cassert>

#include "Game.h"
#include "Constants.h"
#include "UtilString.h"
#include "UtilGraphic.h"

namespace SnakeGame
{
	void HandleGameStateLeaderboardWindowEvent(GameStateLeaderboardData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				SwitchGameState(game, EGameStateType::MainMenu);
			}
		}
	}

	void InitGameStateLeaderboard(GameStateLeaderboardData& data, Game& game)
	{
		// Init fonts
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));
		assert(data.recordsFont.loadFromFile(RESOURCES_PATH + "Fonts/consola.ttf"));

		// Actualize records
		if (game.records[game.gameSettings.playerName] < *game.ptrPlayerScores)
		{
			game.records[game.gameSettings.playerName] = *game.ptrPlayerScores;
		}

		// Sort records
		Records records = SortByScores(game.records);

		// Leaderboard definition
		std::string tableOfLeaders = "";
		tableOfLeaders.resize(ROW_LENGTH, '=');
		tableOfLeaders.push_back('\n');

		for (auto record : records)
		{
			tableOfLeaders.append(stringFormat(record.first, std::to_string(record.second), SYM_SEPARATE, ROW_LENGTH)).push_back('\n');
		}

		std::string end = "";
		end.resize(ROW_LENGTH, '=');
		tableOfLeaders.append(end);

		// Init texts
		InitText(data.title, "LEADERBOARD", data.font, sf::Color::Blue, 40);
		SetTextOrigin(data.title, ETextOrigin::Center);

		InitText(data.leaderBoardText, tableOfLeaders, data.recordsFont, sf::Color::White, 25);
		SetTextOrigin(data.leaderBoardText, ETextOrigin::Center);
	}

	void DrawGameStateLeaderboard(GameStateLeaderboardData& data, Game& game, sf::RenderWindow& window)
	{
		// Set position
		data.title.setPosition(SCREEN_WIDTH_GAME / 2, 100);
		data.leaderBoardText.setPosition(SCREEN_WIDTH_GAME / 2, SCREEN_HEIGHT_GAME / 2);

		// Draw game over window
		window.draw(data.title);
		window.draw(data.leaderBoardText);
	}

	void UpdateGameStateLeaderboard(GameStateLeaderboardData& data, Game& game)
	{
		// Nothing to do
	}

	void ShutdownGameStateLeaderboard(GameStateLeaderboardData& data, Game& game)
	{
		// Nothing to do
	}
}