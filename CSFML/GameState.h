#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Libraries.h"
#include "SFML.h"

enum State
{
	MENU,
	GAME,
	PAUSE,
	GAME_OVER,
	CREDITS,
	SETTINGS,
	VERSUS
};

void SetGameState(enum State _state);
enum State GetGameState(void);

#endif