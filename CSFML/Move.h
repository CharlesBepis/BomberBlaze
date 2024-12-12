#ifndef MOVE_H
#define MOVE_H

#include "Libraries.h"
#include "SFML.h"

#include"Map.h"

enum Direction
{
	RIGHT,
	LEFT,
	UP,
	DOWN
};

int checkCloseY(sfVector2f pos);
int checkCloseX(sfVector2f pos);

sfVector2f BasicIA(enum Direction* dir, sfVector2f pos, sfVector2u _size, float speed, int name, float dt);

sfVector2f MoveUp(enum Direction dir, sfVector2f pos, sfVector2u _size, float speed, int name, float dt);
sfVector2f MoveDown(enum Direction dir, sfVector2f pos, sfVector2u _size, float speed, int name, float dt);
sfVector2f MoveLeft(enum Direction dir, sfVector2f pos, sfVector2u _size, float speed, int name, float dt);
sfVector2f MoveRight(enum Direction dir, sfVector2f pos, sfVector2u _size, float speed, int name, float dt);

#endif