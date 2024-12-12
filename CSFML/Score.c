#include "Score.h"

void CapStats()
{
	if (GetBombAmount() > MAX_BOMB_AMOUNT)
	{
		SetBombAmount(MAX_BOMB_AMOUNT);
		//score++
	}

	if (GetBombAmount() < 1)
	{
		SetBombAmount(1);
		//score--
	}

	if (GetPlayerSpeed() <= 100.f)
	{
		SetPlayerSpeed(100.f);
		//score--
	}

	if (GetBombPower() < 1)
	{
		SetBombPower(1);
		//score--
	}

}