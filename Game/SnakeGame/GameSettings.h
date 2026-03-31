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
		std::string playerName{ "XYZ" };

		int numApples{ NUM_APPLES_DEFAULT };
		int appleBonus{ BONUS_PARADISE };
		float timeInterval{ TIME_INTERVAL_PARADISE };
	};
}
