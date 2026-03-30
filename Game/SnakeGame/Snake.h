#pragma once
#include <SFML/Graphics.hpp>

#include <list>

#include "Math.h"
#include "Constants.h"

namespace SnakeGame
{
	enum class SnakeDirection
	{
		Right = 90,
		Up = 0,
		Left = 270,
		Down = 180
	};

	struct SnakeSegment
	{
		Position2D pos;
		sf::Sprite sprite;
	};

	struct Snake
	{
		float speed;

		sf::Texture tt;
		std::list<SnakeSegment> segments;
		std::vector<sf::Texture> textures;
		SnakeDirection direction;
	};

	struct Game;
	struct Sector;

	SnakeSegment* GetHead(Snake& snake);
	SnakeSegment* GetTail(Snake& snake);

	bool IsSnakeCollidedBySelf(Snake& snake);

	void InitSnake(Snake& snake, std::vector<std::vector<Sector>>& windowSectors, const Game& game);
	void DrawSnake(Snake& snake, sf::RenderWindow& window);
	void UpdateSnake(Snake& snake, std::vector<std::vector<Sector>>& windowSectors);

	void GrewUpSnake(Snake& snake);
}