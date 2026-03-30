#pragma once

#include <vector>
#include <random>

namespace sf
{
	class Sprite;
}

namespace SnakeGame
{
	enum class EPosDirection
	{
		Up = 0,
		Left,
		Right,
		Down,
	};

	struct Vector2D
	{
		float x{ 0 };
		float y{ 0 };
	};

	typedef Vector2D Position2D;

	bool operator==(const Position2D& a, const Position2D& b);

	template<class T, class Predicate>
	std::vector<T> GetRangeByPredicate(std::vector<std::vector<T>> vec2D, Predicate predicate)
	{
		std::vector<T> vec;

		for (auto vecRow : vec2D)
		{
			std::copy_if(vecRow.begin(), vecRow.end(), std::back_inserter(vec), predicate);
		}
		return vec;
	}

	EPosDirection GetDirection(const Position2D& oldPos, const Position2D& newPos);

	bool IsRectanglesCollide(Position2D rect1Pos, Vector2D rect1Size, Position2D rect2Pos, Vector2D rect2Size);

	bool IsCirclesCollide(Position2D circle1Pos, float circle1Rad, Position2D circle2Pos, float circle2Rad);

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
}