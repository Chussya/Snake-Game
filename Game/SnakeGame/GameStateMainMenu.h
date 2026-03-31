#pragma once

#include <functional>

#include "Game.h"
#include "MenuItem.h"

namespace SnakeGame
{
	typedef std::function<void(Game&)> call;
	typedef std::list<MenuItem<call>>::iterator active;

	struct GameStateMainMenuData
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

	void HandleGameStateMainMenuWindowEvent(GameStateMainMenuData& data, Game& game, const sf::Event event);

	void InitGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void DrawGameStateMainMenu(GameStateMainMenuData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStateMainMenu(GameStateMainMenuData& data, Game& game);
	void ShutdownGameStateMainMenu(GameStateMainMenuData& data, Game& game);
}