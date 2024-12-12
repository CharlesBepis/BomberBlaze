#include "Pause.h"

sfRectangleShape* dim;
sfText* paused;
sfText* resume;
sfText* quit;

void LoadPause()
{
	dim = sfRectangleShape_create();
	sfRectangleShape_setSize(dim, (sfVector2f) { SCREEN_WIDTH, SCREEN_HEIGHT });
	sfRectangleShape_setFillColor(dim, sfColor_fromRGBA(0, 0, 0, 255 / 2));

	paused = sfText_create();
	sfText_setFont(paused, sfFont_createFromFile("Assets/Font/BloodLust.ttf"));
	sfText_setPosition(paused, (sfVector2f) { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 });
	sfText_setFillColor(paused, sfBlack);
	sfText_setCharacterSize(paused, 128);
	sfText_setString(paused, "PAUSED");
	sfText_setOrigin(paused, (sfVector2f) { sfText_getGlobalBounds(paused).width / 2, sfText_getGlobalBounds(paused).height / 2 });
	sfText_setOutlineColor(paused, sfRed);
	sfText_setOutlineThickness(paused, 2);

	sfFont* fonterino = sfFont_createFromFile("Assets/Font/KarmaFuture.ttf");
	resume = CreateText(resume, fonterino, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 54, sfBlack, "Press ENTER to resume");
	quit = CreateText(quit, fonterino, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + sfText_getGlobalBounds(resume).height * 1.5, 54, sfBlack, "Press ESC to exit");

	sfText_setOutlineColor(resume, sfRed);
	sfText_setOutlineThickness(resume, 2);
	sfText_setOutlineColor(quit, sfRed);
	sfText_setOutlineThickness(quit, 2);
}


void DrawPause(sfRenderWindow* _window)
{
	sfRenderWindow_drawRectangleShape(_window, dim, NULL);
	sfRenderWindow_drawText(_window, paused, NULL);
	sfRenderWindow_drawText(_window, resume, NULL);
	sfRenderWindow_drawText(_window, quit, NULL);
}