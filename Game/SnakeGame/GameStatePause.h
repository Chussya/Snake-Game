#pragma once

#include <functional>

#include "Game.h"
#include "MenuItem.h"

namespace SnakeGame
{
	typedef std::function<void(Game&)> call;
	typedef std::list<MenuItem<call>>::iterator active;

	struct GameStatePauseData
	{
		sf::Clock delayClock;
		bool isWaiting = false;
		const float delayTime = 3.0f;
		const sf::String timerText = "Return to the game in ";

		/// Fonts

		sf::Font font;

		/// Texts

		sf::Text title;
		sf::Text timer;

		/// Buttons

		// Actual (focused) button
		active it;

		// All window buttons
		std::list<MenuItem<call>> buttons;
	};

	struct Game;

	void HandleGameStatePauseWindowEvent(GameStatePauseData& data, Game& game, const sf::Event event);

	void InitGameStatePause(GameStatePauseData& data, Game& game);
	void DrawGameStatePause(GameStatePauseData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStatePause(GameStatePauseData& data, Game& game);
	void ShutdownGameStatePause(GameStatePauseData& data, Game& game);
}