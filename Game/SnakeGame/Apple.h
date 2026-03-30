#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
	struct Apple
	{
		bool isEaten{ false };
		Position2D pos;
		sf::Sprite sprite;
	};

	struct Game;
	struct Sector;

	void InitApple(Apple& apple, std::vector<std::vector<Sector>>& windowSectors, const Game& game, const sf::Texture& texture);
	void DrawApple(Apple& apple, sf::RenderWindow& window);
	void RespawnApple(Apple& apple, std::vector<std::vector<Sector>>& windowSectors);
	void RemoveApple(Apple& apple);
	bool IsAppleCollidedSnake(Apple& apple, const Position2D& headSnakePos);
}