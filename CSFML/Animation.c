#include "Animation.h"

Animation CreateAnimation(int _framerate)
{
	Animation animation;
	animation.state = 0;
	animation.startFrame = 0;
	animation.framerate = _framerate;
	animation.timer = 1.f / animation.framerate;
	return animation;
}

void UpdateAnimation(Animation* _animation, sfSprite* _sprite, sfTexture* _texture, sfVector2u _size, unsigned int _yState, float _dt)
{
	_animation->timer -= _dt;

	if (_animation->timer <= 0.f)
	{
		_animation->state++;
		_animation->timer = 1 / _animation->framerate;
	}

	if (_animation->state >= (int)(sfTexture_getSize(_texture).x / _size.x))
		_animation->state = 0;

	_animation->rect = (sfIntRect){ _animation->state * _size.x, _yState * _size.y, _size.x, _size.y };
	sfSprite_setTextureRect(_sprite, _animation->rect);
}