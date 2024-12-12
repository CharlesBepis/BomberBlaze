#ifndef BOMB_H
#define BOMB_H

#define MAX_BOMB_AMOUNT 5

#include "Libraries.h"
#include "SFML.h"
#include "Player.h"
#include "Enemy.h"
#include "Animation.h"

struct Effects
{
	sfTexture* texture;
	sfSprite* sprite;
	sfVector2f pos;
	sfVector2u size;
	sfIntRect rect;
	unsigned int yState;
};

struct Bomb
{
	sfSprite* sprite;
	sfVector2f pos;
	sfVector2u size;
	sfIntRect rect;

	float timer;
	sfBool isPlaced;
	int power;

	struct Animation effectLeftAnimation;
	struct Animation effectUpAnimation;
	struct Animation effectDownAnimation;
	struct Animation effectRightAnimation;
	struct Animation effectCenterAnimation;
	struct Effects effectCenter;
	struct Effects effectRight[13];
	struct Effects effectUp[11];
	struct Effects effectDown[11];
	struct Effects effectLeft[13];
};

struct Encounter
{
	sfBool up;
	sfBool right;
	sfBool left;
	sfBool down;
};

void LoadBomb(void);
void ResetBomb(void);
void ReloadBomb(void);
void PlaceBomb(void);
void UpdateBomb(float _dt);
void DrawBomb(sfRenderWindow* _window);

struct Bomb* GetBombs(void);

int GetBombPower(void);
void SetBombPower(int _power);

void IncreaseBombPower();
void DecreaseBombPower();

#endif