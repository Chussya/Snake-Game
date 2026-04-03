#pragma once

#include <SFML/Graphics.hpp>

#include "Snake.h"
#include "Apple.h"
#include "Sector.h"

namespace SnakeGame
{
	struct Game;

	struct GameStatePlayingData
	{
		// State data

		bool isKeyPressed{ false };
		int numEatenApples{ 0 };
		Snake snake;
		std::vector<Apple> apples;
		std::vector<std::vector<Sector>> windowSectors;

		// Resources

		sf::Texture appleTexture;

		// Font

		sf::Font font;

		// Text

		sf::Text scoreText;
		sf::Text pauseNote;
	};

	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event);

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game);
	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window);
	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game);
	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game);

	void PopUpPause(GameStatePlayingData& data, Game& game);
}