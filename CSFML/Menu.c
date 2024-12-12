#include "Menu.h"
#include "Sounds.h"

struct Buttons button[3];
struct Buttons background;

void LoadMenu()
{
	background.sprite = sfSprite_create();
	background.texture = sfTexture_createFromFile("Assets/Menu/MainMenu/Background.png", NULL);
	sfSprite_setTexture(background.sprite, background.texture, sfTrue);

	sfTexture* texture = sfTexture_createFromFile("Assets/Menu/MainMenu/Buttons.png", NULL);
	for (unsigned int i = 0; i < 3; i++)
	{
		button[i].sprite = sfSprite_create();
		button[i].texture = texture;
		button[i].size = (sfVector2u){ 300, 70 };
		button[i].isSelected = sfFalse;

		sfSprite_setTexture(button[i].sprite, button[i].texture, sfTrue);
		sfSprite_setTextureRect(button[i].sprite, (sfIntRect) { i* button[i].size.x, button[i].isSelected* button[i].size.y, button[i].size.x, button[i].size.y });
		sfSprite_setOrigin(button[i].sprite, (sfVector2f) { button[i].size.x / 2, button[i].size.y / 2 });
	}

	sfSprite_setPosition(button[CREDITS_BUTTON].sprite, (sfVector2f) { SCREEN_WIDTH - button[0].size.y - button[0].size.x, SCREEN_HEIGHT - button[0].size.y * 3 - button[0].size.y });
	sfSprite_setPosition(button[QUIT_BUTTON].sprite, (sfVector2f) { SCREEN_WIDTH - button[0].size.y - button[0].size.x - button[0].size.x / 2, SCREEN_HEIGHT - button[0].size.y - button[0].size.y / 2 - button[0].size.y });
	sfSprite_setPosition(button[PLAY_BUTTON].sprite, (sfVector2f) { SCREEN_WIDTH - button[0].size.y - button[0].size.x - button[0].size.x / 4 - button[0].size.x / 2, SCREEN_HEIGHT - button[0].size.y * 4 - button[0].size.y / 2 - button[0].size.y });

	buttonData = 0;
	timer = 0.00;
}

void UpdateMenu(float _dt, sfRenderWindow* _window)
{
	if (timer > 0)
		timer = timer - _dt;

	button[buttonData].isSelected = sfTrue;

	for (unsigned int i = 0; i < 3; i++)
	{
		sfSprite_setTextureRect(button[i].sprite, (sfIntRect) { i* button[i].size.x, button[i].isSelected* button[i].size.y, button[i].size.x, button[i].size.y });
	}

	if ((sfKeyboard_isKeyPressed(sfKeyDown) || sfKeyboard_isKeyPressed(sfKeyS)) && timer <= 0)
	{
		buttonData++;
		button[buttonData - 1].isSelected = sfFalse;
		timer = 0.20;
	}
	if ((sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) && timer <= 0)
	{
		buttonData--;
		button[buttonData + 1].isSelected = sfFalse;
		timer = 0.20;
	}

	if (buttonData < 0)
		buttonData = 2;
	if (buttonData > 2)
		buttonData = 0;

	if (sfKeyboard_isKeyPressed(sfKeyEnter))
		switch (buttonData)
		{
		case PLAY_BUTTON:
			SetGameState(GAME);
			CreateMap();
			ResetPlayer();
			ResetLevel();
			ResetScore();
			ResetItem();
			ResetBomb();
			ResetTimerCount();
			CreateEnemiesRoom(GetPlayerLevel());
			PlayHUDLevel();
			timer = 0;
			sfMusic_stop(Menu);
			sfMusic_play(Main);
			break;

		case CREDITS_BUTTON:
			SetGameState(CREDITS);
			timer = 0;
			break;

		case QUIT_BUTTON:
			sfRenderWindow_close(_window);
			timer = 0;
			break;

		default:
			break;
		}
}

void DrawMenu(sfRenderWindow* _window)
{
	sfRenderWindow_drawSprite(_window, background.sprite, NULL);

	for (unsigned i = 0; i < 3; i++)
	{
		sfRenderWindow_drawSprite(_window, button[i].sprite, NULL);
	}

}