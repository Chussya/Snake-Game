#include "Game.h"

int main()
{
	// Init random number generator
	unsigned int seed = (unsigned int)time(nullptr);
	srand(seed);

	// Init window
	sf::RenderWindow window(sf::VideoMode(SnakeGame::SCREEN_WIDTH_GAME, SnakeGame::SCREEN_HEIGHT_GAME), "Snake Game");

	// We now use too much memory for stack, so we need to allocate it on heap
	SnakeGame::Game* game = new SnakeGame::Game();
	InitGame(*game);

	// Init game clock
	sf::Clock game_clock;
	sf::Time lastTime = game_clock.getElapsedTime();

	window.setFramerateLimit(10);

	// Game loop
	while (window.isOpen())
	{
		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		// Calculate time delta
		sf::Time currentTime = game_clock.getElapsedTime();
		float timeDelta = currentTime.asSeconds() - lastTime.asSeconds();
		lastTime = currentTime;
		if (UpdateGame(*game, timeDelta))
		{
			// Draw everything here
			// Clear the window first
			window.clear();

			DrawGame(*game, window);

			// End the current frame, display window contents on screen
			window.display();
		} else
		{
			window.close();
		}
	}

	ShutdownGame(*game);
	delete game;
	game = nullptr;
}
