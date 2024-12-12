#ifndef PLAYER_H
#define PLAYER_H

#include"Libraries.h"
#include"SFML.h"
#include"Screen.h"
#include"Collisions.h"
#include"Animation.h"
#include"GameState.h"
#include "Save.h"
#include "Sounds.h"

#include"Move.h"
#include"Map.h"
#include"Bomb.h"
#include"HUD.h"

void ResetPlayer(void);
void ReplacePlayer(void);
void LoadPlayer(void);
void UpdatePlayer(float dt);
void DrawPlayer(sfRenderWindow* window);

sfVector2f GetPlayerPos();
sfVector2u GetPlayerSize();
unsigned char GetBombAmount(void);
float GetPlayerSpeed(void);
int GetPlayerHP(void);

void SetBombAmount(unsigned char bombAmount);
void SetPlayerSpeed(float speed);
void SetPlayerHP(int HP);

void IncreaseBombAmount(void);
void DecreaseBombAmount(void);
void IncreasePlayerSpeed(void);
void DecreasePlayerSpeed(void);
void IncreasePlayerHP(void);
void DecreasePlayerHP(void);

void PlayerTakeHit(void);

void IncreaseLevel(void);
void ResetLevel(void);
void ResetScore(void);

void AddScore(int addition);
int* GetPlayerScore(void);
int GetPlayerLevel(void);

sfBool GetWallCross(void);
sfBool GetBombCross(void);
sfBool GetInvincible(void);
void SetWallCross(sfBool _bool);
void SetBombCross(sfBool _bool);
void SetInvincible(sfBool _bool);

struct Inventory
{
	unsigned char bomb;
};

struct Player
{
	sfSprite* sprite;
	sfTexture* texture;
	sfVector2f pos;
	sfVector2u textureSize;
	sfVector2u size;
	float speed;
	int HP;
	enum Direction MoveDir;
	enum Direction direction;
	sfVector2f isMoving;
	struct Inventory inventory;

	sfBool wallCross;
	sfBool bombCross;
	sfBool invincible;

	int level;
	int score;
};

#endif