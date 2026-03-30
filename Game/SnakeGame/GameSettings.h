#pragma once

#include "Constants.h"

namespace SnakeGame
{
	enum class EGameMode
	{
		ApplesInfinity = 1 << 0,	// Num 1 ==> Apples Infinity
		Acceleration = 1 << 1,		// Num 2 ==> Acceleration Boost
		Speed = 1 << 2				// Num 3 ==> Speed Boost
	};

	struct GameSettings
	{
		int numApples{ NUM_APPLES };
		int gameMode = 0;
	};
}
