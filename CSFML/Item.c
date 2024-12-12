#include "item.h"

struct Rect item[10];
float timerWallCross = 0;
float timerBombCross = 0;
float timerInvincible = 0;

void ResetItem()
{
	for (int i = 0; i < 10; i++)
	{
		item[i].pos = (sfVector2f){ -50, -50 };
		sfSprite_setPosition(item[i].sprite, item[i].pos);
	}
}

void LoadItem()
{
	for (int i = 0; i < 10; i++)
	{
		item[i].sprite = sfSprite_create();
		item[i].texture = sfTexture_createFromFile("Assets/Items/Items.png", NULL);
		sfSprite_setTexture(item[i].sprite, item[i].texture, sfTrue);

		item[i].size = sfTexture_getSize(item[i].texture);
		item[i].size.x = item[i].size.x / 10;
		item[i].origin.x = item[i].size.x / 2;
		item[i].origin.y = item[i].size.y / 2;

		sfSprite_setOrigin(item[i].sprite, item[i].origin);
	}

	ResetItem();
}

void UpdateFrameItem(void)
{
	for (int i = 0; i < 10; i++)
	{
		int frameWidth = (int)item[i].size.x;
		int frameHeight = (int)item[i].size.y;
		sfIntRect rect = { (int)item[i].type * frameWidth, 0 * frameHeight, frameWidth, frameHeight };
		sfSprite_setTextureRect(item[i].sprite, rect);
	}
}

void PlaceItem(int _i, int _j)
{
	sfVector2f playerPos = (sfVector2f){ GetPlayerPos().x - GetPlayerSize().x / 2, GetPlayerPos().y - GetPlayerSize().y / 4 };
	sfVector2u playerSize = GetPlayerSize();
	for (int i = 0; i < 10; i++)
	{
		if (item[i].pos.x == -50)
		{
			int line = _i;
			int column = _j;

			if (GetTilesType(line, column) == BOX && GetTileItemState(line, column) == sfFalse)
			{
				item[i].pos = (sfVector2f){ GetTilesPos(line, column).x + GetTilesSize(line, column).x / 2, GetTilesPos(line, column).y + GetTilesSize(line, column).y / 2 };
				sfSprite_setPosition(item[i].sprite, item[i].pos);
				item[i].type = rand() % 10;
				SetTileItemState(line, column, sfTrue);
			}
		}
	}
}

void UpdatePosItem(float _dt)
{
	sfVector2f playerPos = (sfVector2f){ GetPlayerPos().x - GetPlayerSize().x / 2, GetPlayerPos().y + GetPlayerSize().y / 4 };
	sfVector2u playerSize = (sfVector2u){ GetPlayerSize().x, GetPlayerSize().y / 2 - GetPlayerSize().y / 4 };
	for (int i = 0; i < 10; i++)
	{

		if (IsCollidingRectangleRectangle(playerPos, (sfVector2f) { item[i].pos.x - item[i].size.x / 2, item[i].pos.y - item[i].size.y / 2 }, playerSize, item[i].size) == sfTrue)
		{
			switch (item[i].type)
			{
			case POWER_UP:
				IncreaseBombPower();
				break;

			case ADD_BOMB:
				IncreaseBombAmount();
				break;

			case SPEED_UP:
				IncreasePlayerSpeed();
				break;

			case HEALTH_UP:
				IncreasePlayerHP();
				break;

			case BOMB_CROSS:
				// ne prend pas de dégats des bombes
				SetBombCross(sfTrue);
				timerBombCross = 5;
				break;

			case WALL_CROSS:
				SetWallCross(sfTrue);
				timerWallCross = 5;
				break;

			case INV_PLAYER:
				// ne prends pas de dégats des ennemis
				SetInvincible(sfTrue);
				timerInvincible = 5;
				break;

			case POWER_DOWN:
				DecreaseBombPower();
				break;

			case REMOVE_BOMB:
				DecreaseBombAmount();
				break;

			case SPEED_DOWN:
				DecreasePlayerSpeed();
				break;
			}

			item[i].pos = (sfVector2f){ -100, -100 };
			sfSprite_setPosition(item[i].sprite, item[i].pos);
		}
	}
}
void UpdateTimer(float _dt)
{
	if (timerBombCross > 0)
	{
		timerBombCross -= _dt;
	}
	else
	{
		SetBombCross(sfFalse);
	}

	if (timerWallCross > 0)
	{
		timerWallCross -= _dt;
	}
	else
	{
		SetWallCross(sfFalse);
	}

	if (timerInvincible > 0)
	{
		timerInvincible -= _dt;
	}
	else
	{
		SetInvincible(sfFalse);
	}
}

void UpdateItem(float _dt)
{
	UpdateFrameItem();
	UpdatePosItem(_dt);
	UpdateTimer(_dt);
}

void DrawItem(sfRenderWindow* _window)
{
	for (int i = 0; i < 10; i++)
	{
		sfRenderWindow_drawSprite(_window, item[i].sprite, NULL);
	}
}

void SetInvincibleTimer(float _time)
{
	timerInvincible = _time;
}