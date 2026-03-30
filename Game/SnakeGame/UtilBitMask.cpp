#include "UtilBitMask.h"

namespace SnakeGame
{
	void TurnOnMask(int& mask, int flag)
	{
		mask |= flag;
	}

	void TurnOffMask(int& mask, int flag)
	{
		mask &= ~flag;
	}

	void UpdateBitMask(int& oldMask, int newMask)
	{
		oldMask& newMask ?
			oldMask &= ~newMask :
			oldMask |= newMask;
	}

	bool IsBitMaskOn(int actualMask, int checkMask)
	{
		return actualMask & checkMask;
	}
}
