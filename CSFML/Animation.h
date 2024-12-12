#ifndef ANIMATION_H
#define ANIMATION_H

#include "Libraries.h"
#include "SFML.h"

typedef struct Animation
{
	float timer;
	int state;
	int startFrame;
	int idleFrame;
	float framerate;
	sfIntRect rect;
} Animation;

Animation CreateAnimation(int framerate);
void UpdateAnimation(Animation* _animation, sfSprite* _sprite, sfTexture* _texture, sfVector2u _size, unsigned int _yState, float _dt);

#endif