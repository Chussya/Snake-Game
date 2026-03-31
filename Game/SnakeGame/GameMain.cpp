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
	sf::Clock clock;
	float accumulator = 0.0f;

	// Game loop
	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		accumulator += elapsed.asSeconds();

		HandleWindowEvents(*game, window);

		if (!window.isOpen())
		{
			break;
		}

		// Calculate time delta

		while (accumulator >= game->gameSettings.timeInterval)
		{
			if (UpdateGame(*game))
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
			accumulator -= game->gameSettings.timeInterval; // Consume time
		}
	}

	ShutdownGame(*game);
	delete game;
	game = nullptr;
}
