#include "Sector.h"

#include "Constants.h"

namespace SnakeGame
{
	void InitSector(Sector& sector, const Position2D& origin)
	{
		// Init coordinates
		sector.isClear = true;
		sector.startPos = origin;
		sector.center = { origin.x + SECTOR_SIZE / 2, origin.y + SECTOR_SIZE / 2 };

		// Init rectangle of sector
		sector.rect.setSize(sf::Vector2f(SECTOR_SIZE, SECTOR_SIZE));
		sector.rect.setFillColor(sf::Color::Black);
		sector.rect.setPosition(origin.x, origin.y);
	}

	void DrawSector(Sector& sector, sf::RenderWindow& window)
	{
		window.draw(sector.rect);
	}

	void UpdateSector(Sector& sector, const sf::Color& color, const bool isClear)
	{
		sector.isClear = isClear;
		sector.rect.setFillColor(color);
	}

	void UpdateSectorByPos(std::vector<std::vector<Sector>>& windowSectors, const Position2D& pos, const bool isClear)
	{
		windowSectors[static_cast<int>(pos.y) / SECTOR_SIZE][static_cast<int>(pos.x) / SECTOR_SIZE].isClear = isClear;
	}

	bool IsWorldSector(std::vector<std::vector<Sector>>& windowSectors, const Position2D& pos)
	{
		return windowSectors[static_cast<int>(pos.y) / SECTOR_SIZE][static_cast<int>(pos.x) / SECTOR_SIZE].rect.getFillColor() == sf::Color::Black;
	}

	Sector* GetAnyClearSector(std::vector<std::vector<Sector>>& windowSectors)
	{
		std::vector<Sector> sectors = GetRangeByPredicate(windowSectors, [](Sector x) { return x.isClear == true; });

		int index = rand() % sectors.size();

		return &windowSectors[static_cast<int>(sectors[index].startPos.y) / SECTOR_SIZE][static_cast<int>(sectors[index].startPos.x) / SECTOR_SIZE];
	}

}