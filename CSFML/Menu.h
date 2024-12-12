#ifndef MENU_H
#define MENU_H

#include "Libraries.h"
#include "SFML.h"
#include "Credits.h"
#include "Screen.h"
#include "GameState.h"
#include "Map.h"
#include "Item.h"
#include "Player.h"
#include "HUD.h"


void LoadMenu();
void UpdateMenu(float dt, sfRenderWindow* window);
void DrawMenu(sfRenderWindow* window);

enum Button
{
	PLAY_BUTTON,
	CREDITS_BUTTON,
	QUIT_BUTTON
};

struct Buttons
{
	sfSprite* sprite;
	sfTexture* texture;
	sfVector2f pos;
	sfVector2u size;
	sfBool isSelected;
};

float timer;
int buttonData;

#endif // !MENU_H