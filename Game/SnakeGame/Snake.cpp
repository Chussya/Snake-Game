#include "Snake.h"

#include <cassert>

#include "Sector.h"
#include "GameSettings.h"

namespace SnakeGame
{
	SnakeSegment* GetHead(Snake& snake)
	{
		if (snake.segments.size() > 0)
		{
			return &snake.segments.front();
		}
		return nullptr;
	}

	SnakeSegment* GetTail(Snake& snake)
	{
		if (snake.segments.size() > 0)
		{
			return &snake.segments.back();
		}
		return nullptr;
	}

	bool IsSnakeCollidedBySelf(Snake& snake)
	{
		Position2D headPos = GetHead(snake)->pos;

		auto it = std::next(snake.segments.begin(), 1);
		auto resIt = std::find_if(it, snake.segments.end(), [&](const SnakeSegment& segment) { return segment.pos == headPos; });

		return resIt != snake.segments.end();
	}

	void InitSnake(Snake& snake, std::vector<std::vector<Sector>>& windowSectors, const Game& game)
	{
		/// Init textures
		snake.textures.resize(14);
		assert(snake.textures[0].loadFromFile(RESOURCES_PATH + "Images/head_up.png"));
		assert(snake.textures[1].loadFromFile(RESOURCES_PATH + "Images/head_down.png"));
		assert(snake.textures[2].loadFromFile(RESOURCES_PATH + "Images/head_left.png"));
		assert(snake.textures[3].loadFromFile(RESOURCES_PATH + "Images/head_right.png"));
		assert(snake.textures[4].loadFromFile(RESOURCES_PATH + "Images/body_bottomleft.png"));
		assert(snake.textures[5].loadFromFile(RESOURCES_PATH + "Images/body_bottomright.png"));
		assert(snake.textures[6].loadFromFile(RESOURCES_PATH + "Images/body_horizontal.png"));
		assert(snake.textures[7].loadFromFile(RESOURCES_PATH + "Images/body_topleft.png"));
		assert(snake.textures[8].loadFromFile(RESOURCES_PATH + "Images/body_topright.png"));
		assert(snake.textures[9].loadFromFile(RESOURCES_PATH + "Images/body_vertical.png"));
		assert(snake.textures[10].loadFromFile(RESOURCES_PATH + "Images/tail_up.png"));
		assert(snake.textures[11].loadFromFile(RESOURCES_PATH + "Images/tail_down.png"));
		assert(snake.textures[12].loadFromFile(RESOURCES_PATH + "Images/tail_left.png"));
		assert(snake.textures[13].loadFromFile(RESOURCES_PATH + "Images/tail_right.png"));

		/// Init snake's segments
		int row = static_cast<int>(windowSectors.size()) / 2;
		int col = static_cast<int>(windowSectors[0].size()) / 2;

		// Head segment
		SnakeSegment head;

		//assert(snake.tt.loadFromFile(RESOURCES_PATH + "Images/head_up.png"));

		windowSectors[row][col].isClear = false;
		head.pos = windowSectors[row][col].startPos;
		//head.sprite.setTexture(snake.tt);
		head.sprite.setTexture(snake.textures[0]);
		SetSpriteSize(head.sprite, SECTOR_SIZE, SECTOR_SIZE);

		// Body segment
		SnakeSegment body;

		windowSectors[++row][col].isClear = false;
		body.pos = windowSectors[row][col].startPos;
		body.sprite.setTexture(snake.textures[9]);
		SetSpriteSize(body.sprite, SECTOR_SIZE, SECTOR_SIZE);

		// Tail segment
		SnakeSegment tail;

		windowSectors[++row][col].isClear = false;
		tail.pos = windowSectors[row][col].startPos;
		tail.sprite.setTexture(snake.textures[11]);
		SetSpriteSize(tail.sprite, SECTOR_SIZE, SECTOR_SIZE);

		/// Init snake
		snake.segments.push_back(head);
		snake.segments.push_back(body);
		snake.segments.push_back(tail);

		snake.speed = INITIAL_SPEED;
		//player.acceleration = game.gameSettings.gameMode & static_cast<int>(EGameMode::Acceleration) ? INITIAL_ACCELERATION : 0.f;
		//player.direction = PlayerDirection::Right;

		//// Init sprite
		//player.sprite.setTexture(texture);
		//SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
		//SetSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
	}

	void DrawSnake(Snake& snake, sf::RenderWindow& window)
	{
		for (auto& snakeSegment : snake.segments)
		{
			snakeSegment.sprite.setPosition(snakeSegment.pos.x, snakeSegment.pos.y);
			window.draw(snakeSegment.sprite);
		}
	}

	void UpdateSnake(Snake& snake, std::vector<std::vector<Sector>>& windowSectors)
	{
		Position2D toPos, prevSegmentPos;;
		// Move other segments:
		for (auto& segment : snake.segments)
		{
			if (snake.segments.front().pos == segment.pos)
			{
				toPos = segment.pos;

				// Move head:
				switch (snake.direction)
				{
				case SnakeDirection::Right: {
					segment.pos.x += snake.speed;
					segment.sprite.setTexture(snake.textures[3]);
					break;
				}
				case SnakeDirection::Up: {
					segment.pos.y -= snake.speed;
					segment.sprite.setTexture(snake.textures[0]);
					break;
				}
				case SnakeDirection::Left: {
					segment.pos.x -= snake.speed;
					segment.sprite.setTexture(snake.textures[2]);
					break;
				}
				case SnakeDirection::Down: {
					segment.pos.y += snake.speed;
					segment.sprite.setTexture(snake.textures[1]);
					break;
				}
				default:
					// Nothing to do...
					break;
				}
			} else
			{
				if (snake.segments.back().pos == segment.pos)
				{
					UpdateSectorByPos(windowSectors, segment.pos, true);

					switch (GetDirection(toPos, prevSegmentPos))
					{
					case EPosDirection::Up:
						segment.sprite.setTexture(snake.textures[11]);
						break;
					case EPosDirection::Down:
						segment.sprite.setTexture(snake.textures[10]);
						break;
					case EPosDirection::Left:
						segment.sprite.setTexture(snake.textures[13]);
						break;
					case EPosDirection::Right:
						segment.sprite.setTexture(snake.textures[12]);
						break;
					default:
						// Nothing to do...
						break;
					}
				}
				else
				{
					EPosDirection firstPosDirection = GetDirection(segment.pos, toPos);
					EPosDirection secondPosDirection = GetDirection(toPos, prevSegmentPos);

					if ((firstPosDirection == EPosDirection::Up || firstPosDirection == EPosDirection::Down)
						&& (secondPosDirection == EPosDirection::Up || secondPosDirection == EPosDirection::Down))
					{
						segment.sprite.setTexture(snake.textures[9]);
					} else if ((firstPosDirection == EPosDirection::Left || firstPosDirection == EPosDirection::Right)
						&& (secondPosDirection == EPosDirection::Left || secondPosDirection == EPosDirection::Right))
					{
						segment.sprite.setTexture(snake.textures[6]);
					} else if ((firstPosDirection == EPosDirection::Down && secondPosDirection == EPosDirection::Left)
						|| (firstPosDirection == EPosDirection::Right && secondPosDirection == EPosDirection::Up))
					{
						segment.sprite.setTexture(snake.textures[7]);
					} else if ((firstPosDirection == EPosDirection::Down && secondPosDirection == EPosDirection::Right)
						|| (firstPosDirection == EPosDirection::Left && secondPosDirection == EPosDirection::Up))
					{
						segment.sprite.setTexture(snake.textures[8]);
					} else if ((firstPosDirection == EPosDirection::Right && secondPosDirection == EPosDirection::Down)
						|| (firstPosDirection == EPosDirection::Up && secondPosDirection == EPosDirection::Left))
					{
						segment.sprite.setTexture(snake.textures[4]);
					} else if ((firstPosDirection == EPosDirection::Left && secondPosDirection == EPosDirection::Down)
						|| (firstPosDirection == EPosDirection::Up && secondPosDirection == EPosDirection::Right))
					{
						segment.sprite.setTexture(snake.textures[5]);
					}
				}
				std::swap(segment.pos, toPos);
			}
			prevSegmentPos = segment.pos;

			UpdateSectorByPos(windowSectors, segment.pos, false);
		}
	}

	void GrewUpSnake(Snake& snake)
	{
		auto oldTail = GetTail(snake);

		SnakeSegment newTail;
		newTail.pos = oldTail->pos;

		switch (GetDirection(std::prev(snake.segments.end(), 2)->pos, oldTail->pos))
		{
		case EPosDirection::Up:
		{
			newTail.pos.y -= SECTOR_SIZE;
			newTail.sprite.setTexture(snake.textures[10]);
			oldTail->sprite.setTexture(snake.textures[9]);
			break;
		}
		case EPosDirection::Down:
		{
			newTail.pos.y += SECTOR_SIZE;
			newTail.sprite.setTexture(snake.textures[11]);
			oldTail->sprite.setTexture(snake.textures[9]);
			break;
		}
		case EPosDirection::Left:
		{
			newTail.pos.x -= SECTOR_SIZE;
			newTail.sprite.setTexture(snake.textures[12]);
			oldTail->sprite.setTexture(snake.textures[6]);
			break;
		}
		case EPosDirection::Right:
		{
			newTail.pos.x += SECTOR_SIZE;
			newTail.sprite.setTexture(snake.textures[13]);
			oldTail->sprite.setTexture(snake.textures[6]);
			break;
		}
		default:
			break;
		}
		SetSpriteSize(newTail.sprite, SECTOR_SIZE, SECTOR_SIZE);
		snake.segments.push_back(newTail);
	}
}