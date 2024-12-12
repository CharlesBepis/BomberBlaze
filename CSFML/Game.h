#ifndef GAME_H
#define GAME_H

#include "Libraries.h"
#include "SFML.h"
#include "Screen.h"

#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "Bomb.h"
#include "Item.h"
#include "Menu.h"
#include "Credits.h"
#include "Pause.h"
#include "Save.h"
#include "Score.h"
#include "HUD.h"
#include "GameOver.h"
#include "Sounds.h"

#define sfAntoine sfYellow

typedef struct Gamedata
{
	sfRenderWindow* window;
	sfEvent event;
	sfClock* clock;
}GameData;

void Load(GameData*);
void PollEvent(GameData*);
void Update(GameData*, float);
void Draw(const GameData*);

#endif
