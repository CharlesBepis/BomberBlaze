#ifndef HUD_H
#define HUD_H

#include "Libraries.h"
#include "SFML.h"
#include "Player.h"
#include "Bomb.h"
#include "Save.h"

void LoadHUD();

sfText* CreateTextHUD(sfText* _text, float _x, float _y, unsigned int _sizeFont, sfColor _color);
void DrawText(sfRenderWindow* window, sfText* _text);

void DrawHUD(sfRenderWindow* window);

int UpdateHighScore(int score);
void UpdateTimerDisplay(float _dt);
void UpdateHUD(float _dt);
void PlayHUDLevel(void);

void ResetTimerCount();

float timerCount;
sfText* textScore;
sfText* textHighScore;
sfText* textLevel;
sfText* bombCount;
sfText* timerHUD;
sfText* bombPower;
sfText* lifePoints;
sfColor sfScarlet;
sfSprite* bombSprite;
sfTexture* bombTexture;
sfSprite* hudSprite;
sfTexture* hudTexture;
sfSprite* getBombCrossSprite;
sfTexture* getBombCrossTexture;
sfSprite* getWallCrossSprite;
sfTexture* getWallCrossTexture;
sfSprite* getInvincibilitySprite;
sfTexture* getInvincibilityTexture;
sfFont* fontHUD;

float xLevelHUD;
float yLevelHUD;

#endif