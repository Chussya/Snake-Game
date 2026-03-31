#pragma once

#include <functional>

#include "Game.h"
#include "MenuItem.h"

namespace SnakeGame
{
	typedef std::function<void(Game&)> call;
	typedef std::list<MenuItem<call>>::iterator active;

	struct GameStateComplexityData
	{
		/// Fonts

		sf::Font font;

		/// Texts

		sf::Text title;

		/// Buttons

		// Actual (focused) button
		active it;

		// All window buttons
		std::list<MenuItem<call>> buttons;
	};

	struct Game;

	void HandleGameStateComplexityWindowEvent(GameStateComplexityData& data, Game& game, const sf::Event event);

	void InitGameStateComplexity(GameStateComplexityData& data, Game& game);
	void DrawGameStateComplexity(GameStateComplexityData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStateComplexity(GameStateComplexityData& data, Game& game);
	void ShutdownGameStateComplexity(GameStateComplexityData& data, Game& game);
}