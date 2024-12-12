#ifndef ENEMY_H
#define ENEMY_H

#define MAX_ENEMIES_AMOUNT 10

#include "Libraries.h"
#include "SFML.h"
#include "Screen.h"
#include "Collisions.h"
#include "Animation.h"

#include "Move.h"
#include "Map.h"

enum EnemiesName
{
    RAT,
    BLOB,
    EYE,
    WORM,
    SHADOW,
    CYCLOPE
};

typedef struct Enemy
{
    int name;
    sfBool alive;
    int HP;
    sfSprite* sprite;
    sfTexture* texture;
    sfVector2f pos;
    sfVector2u textureSize;
    sfVector2u size;
    float speed;
    enum Direction MoveDir;
    Animation animation;
} Enemy;

void LoadEnemies(void);
void LoadEnemiesTextures(void);

void AddEnemy(int num, Enemy enemy);
void CreateEnemiesRoom(int _level);
Enemy CreateEnemy(enum EnemiesName name, sfVector2u size, sfVector2i pos, float speed);
Enemy CreateRat(sfVector2i pos);
Enemy CreateBlob(sfVector2i pos);
Enemy CreateEye(sfVector2i pos);
Enemy CreateWorm(sfVector2i pos);
Enemy CreateShadow(sfVector2i pos);
Enemy CreateCyclope(sfVector2i pos);

void UpdateEnemies(float dt);
void UpdateRats(float dt);
void UpdateBlobs(float dt);
void UpdateEyes(float dt);
void UpdateWorms(float dt);
void UpdateGhosts(float dt);
void UpdateCyclopes(float dt);

void DrawEnemies(sfRenderWindow* window);

sfVector2f GetEnemyPos(void);
sfVector2f GetEnemySize(void);

int CheckIntersection(void);
void FindNewDirection(void);

int GetEmptyObject();
Enemy* GetEnemiesList(void);
sfVector2f GetEnemyPos(unsigned int i);

void DecreaseEnemyHP(unsigned i);
void TriggerHighlightEnemies(void);
float GetHighlightEnemiesTimer(void);

#endif ENEMY_H