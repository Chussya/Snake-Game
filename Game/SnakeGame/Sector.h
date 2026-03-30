#pragma once

#include <SFML/Graphics.hpp>

#include "Math.h"

namespace SnakeGame
{
	struct Sector
	{
		bool isClear{ false };

		Position2D startPos;
		Position2D center;
		sf::RectangleShape rect;
	};

	void InitSector(Sector& sector, const Position2D& origin);
	void DrawSector(Sector& sector, sf::RenderWindow& window);
	void UpdateSector(Sector& sector, const sf::Color& color, const bool isClear);
	void UpdateSectorByPos(std::vector<std::vector<Sector>>& windowSectors, const Position2D& pos, const bool isClear);

	bool IsWorldSector(std::vector<std::vector<Sector>>& windowSectors, const Position2D& pos);
	Sector* GetAnyClearSector(std::vector<std::vector<Sector>>& windowSectors);
}