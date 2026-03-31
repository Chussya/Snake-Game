#include "Math.h"

#include <cassert>
#include <SFML/Graphics.hpp>

namespace SnakeGame
{
	bool operator==(const Position2D& a, const Position2D& b)
	{
		return a.x == b.x && a.y == b.y;
	}

	EPosDirection GetDirection(const Position2D& oldPos, const Position2D& newPos)
	{
		if (newPos.x < oldPos.x)
		{
			return EPosDirection::Left;
		} else if (newPos.x > oldPos.x)
		{
			return EPosDirection::Right;
		} else if (newPos.y < oldPos.y)
		{
			return EPosDirection::Up;
		} else if (newPos.y > oldPos.y)
		{
			return EPosDirection::Down;
		}
		assert(false);
	}

	bool IsRectanglesCollide(Position2D rect1Pos, Vector2D rect1Size, Position2D rect2Pos, Vector2D rect2Size)
	{
		float dx = (float)fabs(rect1Pos.x - rect2Pos.x);
		float dy = (float)fabs(rect1Pos.y - rect2Pos.y);

		return dx <= (rect1Size.x + rect2Size.x) / 2.f
			&& dy <= (rect1Size.y + rect2Size.y) / 2.f;
	}

	bool IsCirclesCollide(Position2D circle1Pos, float circle1Rad, Position2D circle2Pos, float circle2Rad)
	{
		float squareDistance = (circle1Pos.x - circle2Pos.x) * (circle1Pos.x - circle2Pos.x)
			+ (circle1Pos.y - circle2Pos.y) * (circle1Pos.y - circle2Pos.y);
		float squareRadiusSum = (circle1Rad + circle2Rad) * (circle1Rad + circle2Rad);

		return squareDistance <= squareRadiusSum;
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin({ originX * spriteRect.width, originY * spriteRect.height });
	}
}
