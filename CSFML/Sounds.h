#ifndef SOUND_H
#define SOUND_H

#include "Libraries.h"
#include<SFML/Audio.h>

sfMusic* Menu;
sfMusic* Main;
sfMusic* Over;

sfSoundBuffer* PlayerHurt;
sfSound* soundPlayerHurt;

sfSoundBuffer* PlaceBombS;
sfSound* soundPlaceBomb;

sfSoundBuffer* ExplodeS;
sfSound* soundExplode;

sfSoundBuffer* EnemyDeath;
sfSound* soundEnemyDeath;

float VolumeMusic;
void LoadSound(void);
void LoadBuffer();
void LoadMusic();

#endif