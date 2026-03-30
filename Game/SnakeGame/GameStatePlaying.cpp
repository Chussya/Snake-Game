#include "GameStatePlaying.h"

#include <cassert>

#include "Game.h"
#include "UtilGraphic.h"
#include "UtilBitMask.h"

namespace SnakeGame
{
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				PushGameState(game, GameStateType::ExitDialog, true);
			} else if (event.key.code == sf::Keyboard::P)
			{
				PushGameState(game, GameStateType::Pause, true);
			}
		}
	}

	void InitGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Init fonts
		assert(data.font.loadFromFile(RESOURCES_PATH + "Fonts/arial.ttf"));

		/// Init textures
		assert(data.appleTexture.loadFromFile(RESOURCES_PATH + "Images/apple.png"));

		/// Init sounds
		//InitSounds(data.sfx);

		// Init texts
		InitText(data.scoreText, "SCORES:", data.font, sf::Color::White, 20);

		InitText(data.movementNote, "Use arrows keys for move", data.font, sf::Color::White, 20);
		SetTextOrigin(data.movementNote, TextOrigin::RightTop);

		/// Init window sectors
		data.windowSectors.resize(SCREEN_HEIGHT_GAME / SECTOR_SIZE);

		for (int row = 0; row < data.windowSectors.size(); ++row)
		{
			data.windowSectors[row].resize(SCREEN_WIDTH_GAME / SECTOR_SIZE);

			for (int col = 0; col < data.windowSectors[row].size(); ++col)
			{
				InitSector(data.windowSectors[row][col], { static_cast<float>(col * SECTOR_SIZE), static_cast<float>(row * SECTOR_SIZE) });
			}
		}

		// Set hud interface
		sf::Color clr = sf::Color(101, 171, 103);
		for (int row = 0; row < HUD_ROWS; ++row)
		{
			for (int col = 0; col < data.windowSectors[row].size(); ++col)
			{
				UpdateSector(data.windowSectors[row][col], clr, false);
			}
		}

		// Set game borders
		clr = sf::Color(203, 89, 69);
		for (int row = HUD_ROWS; row < data.windowSectors.size(); ++row)
		{
			for (int col = 0; col < data.windowSectors[row].size(); ++col)
			{
				if (row > 4 && row < data.windowSectors.size() - 1)
				{
					UpdateSector(data.windowSectors[row][0], clr, false);
					UpdateSector(data.windowSectors[row][data.windowSectors[row].size() - 1], clr, false);
					break;
				} else
				{
					UpdateSector(data.windowSectors[row][col], clr, false);
				}
			}
		}

		/// Init snake

		InitSnake(data.snake, data.windowSectors, game);

		/// Init apples:

		data.apples.resize(game.gameSettings.numApples);
		for (Apple& apple : data.apples)
		{
			InitApple(apple, data.windowSectors, game, data.appleTexture);
		}

		data.numEatenApples = 0;
		game.ptrPlayerScores = &data.numEatenApples;
	}

	void DrawGameStatePlaying(GameStatePlayingData& data, Game& game, sf::RenderWindow& window)
	{
		// Sectors
		for (auto rows : data.windowSectors)
		{
			for (auto sector : rows)
			{
				window.draw(sector.rect);
			}
		}

		// Snake
		DrawSnake(data.snake, window);

		// apples
		for (Apple& apple : data.apples)
		{
			DrawApple(apple, window);
		}

		// Texts
		window.draw(data.scoreText);
		data.scoreText.setPosition(0, 0);
		window.draw(data.movementNote);
		data.movementNote.setPosition(SCREEN_WIDTH_GAME - 1, 0);
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game, float timeDelta)
	{
		// Check player's direction
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && data.snake.direction != SnakeDirection::Down)
		{
			data.snake.direction = SnakeDirection::Up;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && data.snake.direction != SnakeDirection::Left)
		{
			data.snake.direction = SnakeDirection::Right;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && data.snake.direction != SnakeDirection::Up)
		{
			data.snake.direction = SnakeDirection::Down;
		} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && data.snake.direction != SnakeDirection::Right)
		{
			data.snake.direction = SnakeDirection::Left;
		}

		// Update player
		UpdateSnake(data.snake, data.windowSectors);

		// Check borders' collision:
		if (IsSnakeCollidedBySelf(data.snake) || !IsWorldSector(data.windowSectors, GetHead(data.snake)->pos))
		{
			PushGameState(game, GameStateType::GameOver, true);
			return;
		}

		// Check apples' collision
		for (Apple& apple : data.apples)
		{
			if (!apple.isEaten && IsAppleCollidedSnake(apple, GetHead(data.snake)->pos))
			{
				++data.numEatenApples;
				//data.sfx.eatSound.play();

				// If not infinity mode - finish game
				//if (!IsBitMaskOn(game.gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity))
				//	&& game.gameSettings.numApples == data.numEatenApples)
				//{
				//	PushGameState(game, GameStateType::GameOver, true);
				//	return;
				//}

				// Respawn apple
				//if (IsBitMaskOn(game.gameSettings.gameMode, static_cast<int>(EGameMode::ApplesInfinity)))
				//{
					RespawnApple(apple, data.windowSectors);
					GrewUpSnake(data.snake);
				//}
				//// Mark apple as eaten
				//else
				//{
				//	RemoveApple(apple);
				//}

				//// Speed up player
				//if (IsBitMaskOn(game.gameSettings.gameMode, static_cast<int>(EGameMode::Acceleration)))
				//{
				//	SpeedUpPlayer(data.player, timeDelta);
				//}
			}
		}

		// Update scores:
		data.scoreText.setString("SCORES: " + std::to_string(data.numEatenApples));
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}
}