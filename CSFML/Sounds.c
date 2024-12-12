#include "Sounds.h"


void LoadBuffer()
{
	
	PlayerHurt = sfSoundBuffer_createFromFile("Assets/Sounds/Hurt.wav");
	soundPlayerHurt = sfSound_create();
	sfSound_setBuffer(soundPlayerHurt, PlayerHurt);

	PlaceBombS = sfSoundBuffer_createFromFile("Assets/Sounds/Place.wav");
	soundPlaceBomb = sfSound_create();
	sfSound_setBuffer(soundPlaceBomb, PlaceBombS);

	ExplodeS = sfSoundBuffer_createFromFile("Assets/Sounds/Explode.wav");
	soundExplode = sfSound_create();
	sfSound_setBuffer(soundExplode, ExplodeS);

	EnemyDeath = sfSoundBuffer_createFromFile("Assets/Sounds/EnemyDeath.wav");
	soundEnemyDeath = sfSound_create();
	//sfSound_setBuffer(soundEnemyDeath, EnemyDeath);
}

void LoadMusic()
{
	Menu = sfMusic_createFromFile("Assets/Sounds/MenuTheme.ogg");
	sfMusic_setLoop(Menu, sfTrue);
	
	Main = sfMusic_createFromFile("Assets/Sounds/MainTheme.ogg");
	sfMusic_setLoop(Main, sfTrue);

	Over = sfMusic_createFromFile("Assets/Sounds/GameOver.ogg");
	sfMusic_setLoop(Over, sfTrue);


	VolumeMusic = 10;
}

void LoadSound()
{
	LoadBuffer();
	LoadMusic();
	sfMusic_play(Menu);
	sfMusic_setVolume(Menu, VolumeMusic);
	sfMusic_setVolume(Main, VolumeMusic + 7);
	sfMusic_setVolume(Over, VolumeMusic);
	sfSound_setVolume(soundExplode, 25);
	sfSound_setVolume(soundPlaceBomb, 50);
	sfSound_setVolume(soundPlayerHurt, 80);
}