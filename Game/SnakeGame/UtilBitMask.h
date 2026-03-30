#pragma once
#pragma once

namespace SnakeGame
{
	void TurnOnMask(int& mask, int flag);
	void TurnOffMask(int& mask, int flag);
	void UpdateBitMask(int& oldMask, int newMask);
	bool IsBitMaskOn(int actualMask, int checkMask);
}