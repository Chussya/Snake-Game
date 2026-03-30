#include "Apple.h"

#include "Sector.h"
#include "Game.h"

namespace SnakeGame
{
	void InitApple(Apple& apple, std::vector<std::vector<Sector>>& windowSectors, const Game& game, const sf::Texture& texture)
	{
		auto ptrSector = GetAnyClearSector(windowSectors);
		ptrSector->isClear = false;
		apple.pos = ptrSector->startPos;

		// Init sprite
		apple.sprite.setTexture(texture);
		SetSpriteSize(apple.sprite, SECTOR_SIZE, SECTOR_SIZE);
	}

	void DrawApple(Apple& apple, sf::RenderWindow& window)
	{
		if (apple.isEaten)
		{
			return;
		}
		apple.sprite.setPosition(apple.pos.x, apple.pos.y);
		window.draw(apple.sprite);
	}

	void RespawnApple(Apple& apple, std::vector<std::vector<Sector>>& windowSectors)
	{
		UpdateSectorByPos(windowSectors, apple.pos, false);

		auto ptrSector = GetAnyClearSector(windowSectors);
		ptrSector->isClear = false;
		apple.pos = ptrSector->startPos;
	}

	void RemoveApple(Apple& apple)
	{
		apple.isEaten = true;
	}

	bool IsAppleCollidedSnake(Apple& apple, const Position2D& headSnakePos)
	{
		return apple.pos == headSnakePos;
	}
}
