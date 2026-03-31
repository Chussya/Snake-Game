#pragma once

#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	struct GameStateLeaderboardData
	{
		/// Fonts

		sf::Font font;
		sf::Font recordsFont;

		/// Texts

		sf::Text title;
		sf::Text leaderBoardText;
	};

	struct Game;

	void HandleGameStateLeaderboardWindowEvent(GameStateLeaderboardData& data, Game& game, const sf::Event event);

	void InitGameStateLeaderboard(GameStateLeaderboardData& data, Game& game);
	void DrawGameStateLeaderboard(GameStateLeaderboardData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStateLeaderboard(GameStateLeaderboardData& data, Game& game);
	void ShutdownGameStateLeaderboard(GameStateLeaderboardData& data, Game& game);
}