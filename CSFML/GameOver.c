#include "GameOver.h"

sfText* gameover;
sfText* retry;
sfText* quit;
sfSprite* backgroundGO;
sfTexture* bgtexture;


void LoadGameOver()
{
	sfVector2f pos;
	backgroundGO = sfSprite_create();
	bgtexture = sfTexture_createFromFile("Assets/Menu/GameOver/GameOver.png", NULL);
	sfSprite_setTexture(backgroundGO, bgtexture, NULL);
	pos.x = 0;
	pos.y = 0;
	sfSprite_setPosition(backgroundGO, pos);


	sfFont* font = sfFont_createFromFile("Assets/Font/BloodLust.ttf");
	gameover = CreateText(gameover, font, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, 128, sfBlack, "GAME OVER");
	sfText_setOrigin(gameover, (sfVector2f) { sfText_getGlobalBounds(gameover).width / 2, sfText_getGlobalBounds(gameover).height / 2 });
	sfText_setOutlineColor(gameover, sfRed);
	sfText_setOutlineThickness(gameover, 2);

	sfFont* fonterino = sfFont_createFromFile("Assets/Font/KarmaFuture.ttf");
	retry = CreateText(retry, fonterino, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 54, sfBlack, "Press ENTER to retry");
	quit = CreateText(quit, fonterino, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + sfText_getGlobalBounds(retry).height * 1.5, 54, sfBlack, "Press ESC to exit");

	sfText_setOutlineColor(retry, sfRed);
	sfText_setOutlineThickness(retry, 2);
	sfText_setOutlineColor(quit, sfRed);
	sfText_setOutlineThickness(quit, 2);
}


void DrawGameOver(sfRenderWindow* _window)
{
	sfRenderWindow_drawSprite(_window, backgroundGO, NULL);
	sfRenderWindow_drawText(_window, gameover, NULL);
	sfRenderWindow_drawText(_window, retry, NULL);
	sfRenderWindow_drawText(_window, quit, NULL);
}