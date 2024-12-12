#include "HUD.h"

char tabLevel[30];
sfFloatRect textLevelBounds;
int highScore;

sfText* CreateTextHUD(sfText* _text, float _x, float _y, unsigned int _sizeFont, sfColor _color, char* string)
{
	_text = sfText_create();
	sfFont* font = sfFont_createFromFile("Assets/Font/RetroGaming.ttf");
	sfText_setFont(_text, font);
	sfText_setCharacterSize(_text, _sizeFont);
	sfText_setColor(_text, _color);
	sfText_setPosition(_text, (sfVector2f) { _x, _y });
	sfText_setString(_text, string);
	return _text;
}

void DrawText(sfRenderWindow* window, sfText* _text)
{
	sfRenderWindow_drawText(window, _text, NULL);
}

int UpdateScore(int score, int mode)
{
	score += mode;
	return score;
}

int UpdateHighScore(int highScore, int score)
{
	highScore = score;
	return highScore;
}

void LoadHUDLevel()
{
	textLevel = CreateTextHUD(textLevel, xLevelHUD, yLevelHUD, 120, sfBlack, "");
	PlayHUDLevel();
}

void LoadHUD()
{
	fontHUD = sfFont_createFromFile("Assets/Font/RetroGaming.ttf");

	textScore = CreateTextHUD(textScore, 450 + 144, 62, 30, sfWhite, "0");
	textHighScore = CreateTextHUD(textHighScore, 450 + 910, 62, 30, sfWhite, "0");
	bombCount = CreateTextHUD(bombCount, 450 + 640, 63, 30, sfWhite, "1");
	timerHUD = CreateTextHUD(timerHUD, 450 + 378, 63, 30, sfWhite, "10:00");
	lifePoints = CreateTextHUD(lifePoints, 450 + 532, 63, 30, sfWhite, "1");
	bombPower = CreateTextHUD(bombPower, 450 + 754, 63, 30, sfWhite, "1");

	hudSprite = sfSprite_create();
	getBombCrossSprite = sfSprite_create();
	getWallCrossSprite = sfSprite_create();
	getInvincibilitySprite = sfSprite_create();

	hudTexture = sfTexture_createFromFile("Assets/HUD/BackgroundHUD.png", NULL);
	getBombCrossTexture = sfTexture_createFromFile("Assets/Bomb/GetBombCross.png", NULL);
	getWallCrossTexture = sfTexture_createFromFile("Assets/Bomb/GetWallCross.png", NULL);
	getInvincibilityTexture = sfTexture_createFromFile("Assets/Bomb/GetInvincibility.png", NULL);

	sfSprite_setTexture(hudSprite, hudTexture, 0);
	sfSprite_setTexture(getBombCrossSprite, getBombCrossTexture, 0);
	sfSprite_setTexture(getWallCrossSprite, getWallCrossTexture, sfTrue);
	sfSprite_setTexture(getInvincibilitySprite, getInvincibilityTexture, sfTrue);

	sfSprite_setPosition(hudSprite, (sfVector2f) { 450, 0 });
	sfSprite_setPosition(getBombCrossSprite, (sfVector2f) { 450 + sfTexture_getSize(hudTexture).x + 4, 8 });
	sfSprite_setPosition(getWallCrossSprite, (sfVector2f) { 450 + sfTexture_getSize(hudTexture).x + 4, sfTexture_getSize(hudTexture).y / 2 });
	sfSprite_setPosition(getInvincibilitySprite, (sfVector2f) { 450 + sfTexture_getSize(hudTexture).x + 4, sfTexture_getSize(hudTexture).y - 32 - 8 });

	sfSprite_setOrigin(getWallCrossSprite, (sfVector2f) { 0, 16 });

	timerCount = 10.0f;

	ReadHiscore(&highScore);

	LoadHUDLevel();
}

void DrawBackground(sfRenderWindow* window)
{
	sfRenderWindow_drawSprite(window, hudSprite, NULL);
}

void PlayHUDLevel()
{
	sprintf_s(tabLevel, 10, " level %d", GetPlayerLevel());
	sfText_setString(textLevel, tabLevel);
	sfText_setOutlineColor(textLevel, sfColor_fromRGB(128, 128, 128));
	sfText_setOutlineThickness(textLevel, 4.0f);

	textLevelBounds = sfText_getGlobalBounds(textLevel);
	sfText_setOrigin(textLevel, (sfVector2f) { textLevelBounds.width / 2, textLevelBounds.height / 2 });
	xLevelHUD = 0 - textLevelBounds.width / 2;
	yLevelHUD = SCREEN_HEIGHT / 2 - textLevelBounds.height / 2;
}

void UpdateHUDLevel(float _dt)
{
	if (xLevelHUD < SCREEN_WIDTH + textLevelBounds.width / 2)
	{
		xLevelHUD += _dt * 600;
	}
	else
		xLevelHUD = SCREEN_WIDTH + textLevelBounds.width / 2;
}

void UpdateTimerDisplay(float _dt)
{
	//protection contre de potentiels speedhacks    
	if (_dt > 1)
	{
		_dt = 0.1f;
	}

	char timerChar[10];
	sprintf_s(timerChar, 10, "%d:%d", (int)timerCount / 60, (int)timerCount % 60);
	sfText_setString(timerHUD, timerChar);

	timerCount -= _dt;

	if (timerCount <= 0)
	{
		DecreasePlayerHP();
		ReplacePlayer();
		ResetTimerCount();
	}
}

void UpdateHUD(float _dt)
{
	UpdateTimerDisplay(_dt);
	char lifeTab[10];
	char scoreTab[10];
	char highScoreTab[10];
	char CountBomb[10];
	char BombPowerHUD[10];

	sprintf_s(lifeTab, 10, " %d", GetPlayerHP());
	sprintf_s(scoreTab, 10, " %d", *GetPlayerScore());
	sprintf_s(highScoreTab, 10, " %d", highScore);
	sprintf_s(CountBomb, 10, "%d", GetBombAmount());
	sprintf_s(BombPowerHUD, 10, "%d", GetBombPower());

	sfText_setString(lifePoints, lifeTab);
	sfText_setString(textScore, scoreTab);
	sfText_setString(textHighScore, highScoreTab);
	sfText_setString(bombCount, CountBomb);
	sfText_setString(bombPower, BombPowerHUD);

	sfText_setOrigin(textScore, (sfVector2f) { sfText_getGlobalBounds(textHighScore).width / 2 + 5, sfText_getGlobalBounds(textHighScore).height / 2 + 7 });
	sfText_setOrigin(textHighScore, (sfVector2f) { sfText_getGlobalBounds(textHighScore).width / 2 + 5, sfText_getGlobalBounds(textHighScore).height / 2 + 7 });
	sfText_setOrigin(bombCount, (sfVector2f) { sfText_getGlobalBounds(bombCount).width / 2 + 5, sfText_getGlobalBounds(bombCount).height / 2 + 7 });
	sfText_setOrigin(timerHUD, (sfVector2f) { sfText_getGlobalBounds(timerHUD).width / 2, sfText_getGlobalBounds(timerHUD).height / 2 + 7 });
	sfText_setOrigin(lifePoints, (sfVector2f) { sfText_getGlobalBounds(lifePoints).width / 2 + 5, sfText_getGlobalBounds(lifePoints).height / 2 + 7 });
	sfText_setOrigin(bombPower, (sfVector2f) { sfText_getGlobalBounds(bombPower).width / 2 + 5, sfText_getGlobalBounds(bombPower).height / 2 + 7 });

	UpdateHUDLevel(_dt);

	if (highScore < *GetPlayerScore())
	{
		highScore = UpdateHighScore(highScore, *GetPlayerScore());
	}
}

void DrawBonus(sfRenderWindow* _window)
{
	if (GetWallCross() == sfTrue)
	{
		sfRenderWindow_drawSprite(_window, getWallCrossSprite, NULL);
	}
	if (GetBombCross() == sfTrue)
	{
		sfRenderWindow_drawSprite(_window, getBombCrossSprite, NULL);
	}
	if (GetInvincible() == sfTrue)
	{
		sfRenderWindow_drawSprite(_window, getInvincibilitySprite, NULL);
	}
}

void DrawHUDLevel(sfRenderWindow* _window)
{
	sfText_setPosition(textLevel, (sfVector2f) { xLevelHUD, yLevelHUD });
	sfRenderWindow_drawText(_window, textLevel, NULL);
}

void DrawHUD(sfRenderWindow* _window)
{
	DrawBackground(_window);
	DrawText(_window, textScore);
	DrawText(_window, textHighScore);
	DrawText(_window, bombCount);
	DrawText(_window, timerHUD);
	DrawText(_window, lifePoints);
	DrawText(_window, bombPower);
	DrawBonus(_window);
	DrawHUDLevel(_window);
}

void ResetTimerCount()
{
	timerCount = 180.0f;
}