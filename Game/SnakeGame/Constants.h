#pragma once
#include <string>

namespace SnakeGame
{
	// Path

	const std::string RESOURCES_PATH = "Resources/";

	// Display

	const int SCREEN_WIDTH_GAME = 800;
	const int SCREEN_HEIGHT_GAME = 600;

	// Visual

	const int SECTOR_SIZE = 20;
	const int HUD_ROWS = 4;
	const int OUTLINE_THICKNESS = 1;

	// Game

	const float INITIAL_SPEED = 20.f;			// Sector size speed
	const float BONUS_SPEED = 100.f;
	const float INITIAL_ACCELERATION = 20.f;
	const float DELTA_TIME_CORRECT = 800.f;
	const float PLAYER_SIZE = 20.f;
	const int NUM_APPLES_DEFAULT = 1;
	const int BONUS_PARADISE = 2;
	const int BONUS_EASY = 4;
	const int BONUS_NORMAL = 6;
	const int BONUS_HARD = 8;
	const int BONUS_HELL = 10;
	const float TIME_INTERVAL_PARADISE = 0.15f;
	const float TIME_INTERVAL_EASY = 0.12f;
	const float TIME_INTERVAL_NORMAL = 0.09f;
	const float TIME_INTERVAL_HARD = 0.05f;
	const float TIME_INTERVAL_HELL = 0.03f;
	const float APPLE_SIZE = 20.f;

	// Leaderboard

	const char SYM_SEPARATE = '.';
	const char SYM_TITLE = '=';
	const unsigned int ROW_LENGTH = 50;
	const std::string PLAYER_INDEX = "Player";
}