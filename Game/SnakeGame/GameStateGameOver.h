#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "Game.h"
#include "MenuItem.h"

namespace SnakeGame
{
	typedef std::function<void(Game&)> call;
	typedef std::list<MenuItem<call>>::iterator active;

	struct GameStateGameOverData
	{
		const int maxRecords{ 5 };

		/// Font

		sf::Font font;
		sf::Font recordsFont;

		/// Text

		sf::Text leaderBoardText;
		sf::Text gameOverText;

		/// Buttons

		// Actual (focused) button
		active it;

		// All window buttons
		std::list<MenuItem<call>> buttons;
	};

	struct Game;

	void HandleGameStateGameOverWindowEvent(GameStateGameOverData& data, Game& game, const sf::Event event);

	void InitGameStateGameOver(GameStateGameOverData& data, Game& game);
	void DrawGameStateGameOver(GameStateGameOverData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStateGameOver(GameStateGameOverData& data, Game& game);
	void ShutdownGameStateGameOver(GameStateGameOverData& data, Game& game);

	void PopUpNewRecord(GameStateGameOverData& data, Game& game);
}