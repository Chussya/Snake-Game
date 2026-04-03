#include "GameStatePlaying.h"

#include <cassert>
#include <functional>

#include "Game.h"
#include "MenuItem.h"
#include "UtilGraphic.h"
#include "UtilBitMask.h"

namespace SnakeGame
{
	void HandleGameStatePlayingWindowEvent(GameStatePlayingData& data, Game& game, const sf::Event event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)
			{
				SwitchGameState(game, EGameStateType::MainMenu);
			} else if (event.key.code == sf::Keyboard::P)
			{
				PushGameState(game, EGameStateType::Pause, false);
			}
			else if (!data.isKeyPressed)
			{
				if (event.key.code == sf::Keyboard::W && data.snake.direction != ESnakeDirection::Down)
				{
					data.snake.direction = ESnakeDirection::Up;
					data.isKeyPressed = true;
				} else if (event.key.code == sf::Keyboard::D && data.snake.direction != ESnakeDirection::Left)
				{
					data.snake.direction = ESnakeDirection::Right;
					data.isKeyPressed = true;
				} else if (event.key.code == sf::Keyboard::S && data.snake.direction != ESnakeDirection::Up)
				{
					data.snake.direction = ESnakeDirection::Down;
					data.isKeyPressed = true;
				} else if (event.key.code == sf::Keyboard::A && data.snake.direction != ESnakeDirection::Right)
				{
					data.snake.direction = ESnakeDirection::Left;
					data.isKeyPressed = true;
				}
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

		InitText(data.pauseNote, "For pause use [P]", data.font, sf::Color::White, 20);
		SetTextOrigin(data.pauseNote, ETextOrigin::RightTop);

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
		data.isKeyPressed = false;
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
		window.draw(data.pauseNote);
		data.pauseNote.setPosition(SCREEN_WIDTH_GAME - 1, 0);
	}

	void UpdateGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// Update player
		UpdateSnake(data.snake, data.windowSectors);

		// Check borders' collision:
		if (IsSnakeCollidedBySelf(data.snake) || !IsWorldSector(data.windowSectors, GetHead(data.snake)->pos))
		{
			PushGameState(game, EGameStateType::GameOver, true);
			return;
		}

		// Check apples' collision
		for (Apple& apple : data.apples)
		{
			if (!apple.isEaten && IsAppleCollidedSnake(apple, GetHead(data.snake)->pos))
			{
				data.numEatenApples += game.gameSettings.appleBonus;

				RespawnApple(apple, data.windowSectors);
				GrewUpSnake(data.snake);
			}
		}

		// Update scores:
		data.scoreText.setString("SCORES: " + std::to_string(data.numEatenApples));
	}

	void ShutdownGameStatePlaying(GameStatePlayingData& data, Game& game)
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void PopUpPause(GameStatePlayingData& data, Game& game)
	{
		sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH_POPUP, SCREEN_HEIGHT_POPUP), "Pause Popup");

		sf::Clock delayClock;
		bool isWaiting = false;
		const float delayTime = 3.0f;

		sf::Text title;

		InitText(title, "PAUSE", data.font, sf::Color::Yellow, 40);
		SetTextOrigin(title, ETextOrigin::Center);
		title.setPosition(SCREEN_WIDTH_POPUP / 2.f, 100);

		sf::Text timer;
		const sf::String timerText = "Return to the game in ";

		InitText(timer, timerText, data.font, sf::Color::Yellow, 40);
		SetTextOrigin(timer, ETextOrigin::Center);
		timer.setPosition(SCREEN_WIDTH_POPUP / 2.f, 200);

		MenuItem<std::function<void(Game&)>> exitMenu;

		InitMenuItem<std::function<void(Game&)>>(
			exitMenu,
			"Menu",
			data.font,
			30,
			[&](Game game) { SwitchGameState(game, EGameStateType::MainMenu); }
		);
		SetTextOrigin(exitMenu.text, ETextOrigin::Center);
		exitMenu.text.setPosition(window.getSize().x / 2.f, 200);
		OnFocus(exitMenu);

		MenuItem<std::function<void()>> continueGame;

		InitMenuItem<std::function<void()>>(
			continueGame,
			"Continue",
			data.font,
			30,
			[](){}	// no need function
		);
		SetTextOrigin(continueGame.text, ETextOrigin::Center);
		continueGame.text.setPosition(window.getSize().x / 2.f, 250);

		window.display();

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::S)
					{
						if (exitMenu.onFocus)
						{
							LostFocus(exitMenu);
							OnFocus(continueGame);
						} else
						{
							LostFocus(continueGame);
							OnFocus(exitMenu);
						}
					} else if (event.key.code == sf::Keyboard::Enter)
					{
						if (continueGame.onFocus)
						{
							if (!isWaiting)
							{
								// Only start if not already waiting
								delayClock.restart();
								isWaiting = true;
							}
						} else
						{
							SwitchGameState(game, EGameStateType::MainMenu);
						}
					}
				}
			}
			 
			if (isWaiting && delayClock.getElapsedTime().asSeconds() >= delayTime)
			{
				window.close();
			} else
			{
				timer.setString(timerText + std::to_string(delayTime - delayClock.getElapsedTime().asSeconds()));
			}

			window.clear();
			window.draw(title);

			if (!isWaiting)
			{
				DrawMenuItem(continueGame, window);
				DrawMenuItem(exitMenu, window);
			}
			else
			{
				window.draw(timer);
			}
			window.display();
		}
	}
}