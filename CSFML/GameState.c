#include "GameState.h"

enum State state = MENU;

void SetGameState(enum State _state)
{
	state = _state;
}

enum State GetGameState(void)
{
	return state;
}