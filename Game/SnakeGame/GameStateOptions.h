#pragma once

#include <functional>

#include "Game.h"
#include "MenuItem.h"

namespace SnakeGame
{
	typedef std::function<void(Game&, bool)> optionsCall;
	typedef std::list<std::pair<MenuItem<optionsCall>, sf::RectangleShape>>::iterator activeRow;

	struct GameStateOptionsData
	{
		/// Fonts

		sf::Font font;

		/// Texts

		sf::Text title;

		/// Buttons

		// Actual (focused) button
		activeRow it;

		// All window buttons
		std::list<std::pair<MenuItem<optionsCall>, sf::RectangleShape>> buttons;
	};

	struct Game;

	void HandleGameStateOptionsWindowEvent(GameStateOptionsData& data, Game& game, const sf::Event event);

	void InitGameStateOptions(GameStateOptionsData& data, Game& game);
	void DrawGameStateOptions(GameStateOptionsData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStateOptions(GameStateOptionsData& data, Game& game);
	void ShutdownGameStateOptions(GameStateOptionsData& data, Game& game);
}