#ifndef ITEM_H
#define ITEM_H

#include"Libraries.h"
#include"SFML.h"
#include"Screen.h"

#include "Collisions.h"
#include "Player.h"
#include "Map.h"

#pragma region enum

enum ItemState
{
	POWER_UP,
	ADD_BOMB,
	SPEED_UP,
	HEALTH_UP,
	BOMB_CROSS,
	WALL_CROSS,
	INV_PLAYER,
	POWER_DOWN,
	REMOVE_BOMB,
	SPEED_DOWN,
	NONE
};

#pragma endregion

struct Rect
{
	sfVector2f pos;
	sfVector2u size;
	sfVector2f origin;
	sfSprite* sprite;
	sfTexture* texture;
	enum ItemState type;
};

void LoadItem(void);
void ResetItem(void);
void DrawItem(sfRenderWindow* _window);
void PlaceItem(int _i, int _j);
void UpdateItem(float _dt);
void SetInvincibleTimer(float time);

#endif // !ITEM_H