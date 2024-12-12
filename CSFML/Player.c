#include "Player.h"

struct Player player;
struct Animation playerAnimation;

int r, g, b;

void ReplacePlayer()
{
	player.pos = (sfVector2f){ GetTilesPos(0, 0).x + GetTilesSize(0, 0).x / 2, GetTilesPos(0, 0).y + GetTilesSize(0, 0).y / 2 - player.size.y / 4 };
	player.wallCross = sfFalse;
	player.bombCross = sfFalse;
	player.invincible = sfFalse;

	r = 255;
	g = 255;
	b = 255;
	sfSprite_setColor(player.sprite, sfColor_fromRGBA(r, g, b, 255));
}

void ResetPlayer()
{
	player.pos = (sfVector2f){ GetTilesPos(0, 0).x + GetTilesSize(0, 0).x / 2, GetTilesPos(0, 0).y + GetTilesSize(0, 0).y / 2 - player.size.y / 4 };

	player.speed = 150.f;
	player.HP = 3;
	player.inventory.bomb = 1;

	player.wallCross = sfFalse;
	player.bombCross = sfFalse;
	player.invincible = sfFalse;

	r = 255;
	g = 255;
	b = 255;
	sfSprite_setColor(player.sprite, sfColor_fromRGBA(r, g, b, 255));
}

void LoadPlayer()
{
	player.sprite = sfSprite_create();
	player.texture = sfTexture_createFromFile("Assets/Player/Player.png", NULL);
	player.direction = DOWN;
	sfSprite_setTexture(player.sprite, player.texture, sfTrue);

	player.textureSize = sfTexture_getSize(player.texture);
	player.size = (sfVector2u){ player.textureSize.x / 4, player.textureSize.y / 4 };
	sfSprite_setOrigin(player.sprite, (sfVector2f) { player.size.x / 2, player.size.y / 2 });

	ResetPlayer();
	ResetScore();
	ResetLevel();

	playerAnimation = CreateAnimation(player.speed / 37.5);
}

void CheckPlayerGameAreaCollision()
{
	if (player.pos.x - player.size.x / 2 < GetTilesPos(0, 0).x)
		player.pos.x = GetTilesPos(0, 0).x + player.size.x / 2;

	if (player.pos.x + player.size.x / 2 > GetTilesPos(0, COLUMN - 1).x + GetTilesSize(0, COLUMN - 1).x)
		player.pos.x = GetTilesPos(0, COLUMN - 1).x + GetTilesSize(0, COLUMN - 1).x - player.size.x / 2;

	if (player.pos.y < GetTilesPos(0, 0).y)
		player.pos.y = GetTilesPos(0, 0).y;

	if (player.pos.y + player.size.y / 2 > GetTilesPos(LINE - 1, 0).y + GetTilesSize(LINE - 1, 0).y)
		player.pos.y = GetTilesPos(LINE - 1, 0).y + GetTilesSize(LINE - 1, 0).y - player.size.y / 2;
}

void CheckPlayerWallCollision()
{
	for (unsigned int i = 0; i < LINE; i++)
	{
		for (unsigned int j = 0; j < COLUMN; j++)
		{
			if ((GetTilesType(i, j) == WALL) || ((GetTilesType(i, j) == BOX) && !GetWallCross()))
			{
				if (IsCollidingRectangleRectangle((sfVector2f) { player.pos.x - player.size.x / 2, player.pos.y + player.size.y / 4 }, GetTilesPos(i, j), (sfVector2u) { player.size.x, player.size.y / 2 - player.size.y / 4 }, GetTilesSize(i, j)))
				{
					switch (player.direction)
					{
					case UP:
						player.pos.y = GetTilesPos(i, j).y + GetTilesSize(i, j).y - player.size.y / 4;
						break;

					case LEFT:
						player.pos.x = GetTilesPos(i, j).x + GetTilesSize(i, j).x + player.size.x / 2;
						break;

					case DOWN:
						player.pos.y = GetTilesPos(i, j).y - player.size.y / 2;
						break;

					case RIGHT:
						player.pos.x = GetTilesPos(i, j).x - player.size.x / 2 - 1;
						break;
					}
				}
			}
		}
	}
}

void CheckPlayerExitCollision()
{
	if (GetTilesType(GetLine(player.pos.y), GetColumn(player.pos.x)) == EXIT)
	{
		// check if all enemies are dead
		Enemy* enemiesList = GetEnemiesList();
		for (int e = 0; e < MAX_ENEMIES_AMOUNT; e++)
		{
			if (enemiesList[e].alive)
			{
				if (GetHighlightEnemiesTimer() == 2.f)
				{
					TriggerHighlightEnemies();
				}
				return;
			}
		}
		player.level++;
		ReplacePlayer();

		// Load new level
		CreateMap();
		ResetItem();
		ReloadBomb();
		ResetTimerCount();
		CreateEnemiesRoom(player.level);
		PlayHUDLevel();
	}
}

void CheckPlayerEnemiesCollision()
{
	sfVector2f playerPos = (sfVector2f){ GetPlayerPos().x - GetPlayerSize().x / 2, GetPlayerPos().y + GetPlayerSize().y / 4 };
	sfVector2u playerSize = (sfVector2u){ GetPlayerSize().x, GetPlayerSize().y / 2 - GetPlayerSize().y / 4 };
	Enemy* enemiesList = GetEnemiesList();
	sfVector2f enemiesPos[MAX_ENEMIES_AMOUNT];
	sfVector2u enemiesSize[MAX_ENEMIES_AMOUNT];

	for (int e = 0; e < MAX_ENEMIES_AMOUNT; e++)
	{
		enemiesPos[e] = (sfVector2f){ enemiesList[e].pos.x - enemiesList[e].size.x / 2, enemiesList[e].pos.y - enemiesList[e].size.y / 2 };
		enemiesSize[e] = enemiesList[e].size;

		if ((!player.invincible) && (enemiesList[e].alive))
		{
			if (IsCollidingRectangleRectangle(playerPos, enemiesPos[e], playerSize, enemiesSize[e]))
			{
				PlayerTakeHit();
			}
		}
	}
}

void PlayerTakeHit()
{
	SetInvincibleTimer(1.f);
	player.invincible = sfTrue;
	DecreasePlayerHP();
	g = 0;
	b = 0;
}

void CheckGameOver()
{
	if (player.HP <= 0)
	{
		SetGameState(GAME_OVER);
		sfMusic_stop(Main);
		sfMusic_play(Over);

		if (player.score > GetHiscore())
		{
			SaveHiscore(player.score);
		}
	}
}

void PlayInvincibleAnimation(float _dt)
{
	if (player.invincible)
	{
		g += _dt * 500;
		b += _dt * 500;

		if (g >= 255)
		{
			g = 255;
			b = 255;
		}

		sfSprite_setColor(player.sprite, sfColor_fromRGBA(r, g, b, 255));
	}
}

void UpdatePlayer(float _dt)
{
	if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyUp))
	{
		if (!GetWallCross())
		{
			player.pos = MoveUp(player.MoveDir, player.pos, (sfVector2u) { 0, 119 }, player.speed, -1, _dt);
		}
		else
		{
			player.pos = MoveUp(player.MoveDir, player.pos, (sfVector2u) { 0, 119 }, player.speed, 4, _dt);
		}
		player.direction = UP;
		player.MoveDir = player.direction;
	}

	else if (sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(sfKeyDown))
	{
		if (!GetWallCross())
		{
			player.pos = MoveDown(player.MoveDir, player.pos, (sfVector2u) { 0, 9 }, player.speed, -1, _dt);
		}
		else
		{
			player.pos = MoveDown(player.MoveDir, player.pos, (sfVector2u) { 0, 9 }, player.speed, 4, _dt);
		}
		player.direction = DOWN;
		player.MoveDir = player.direction;
	}

	else if (sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyLeft))
	{
		if (!GetWallCross())
		{
			player.pos = MoveLeft(player.MoveDir, player.pos, (sfVector2u) { 64, 0 }, player.speed, -1, _dt);
		}
		else
		{
			player.pos = MoveLeft(player.MoveDir, player.pos, (sfVector2u) { 64, 0 }, player.speed, 4, _dt);
		}
		player.direction = LEFT;
		player.MoveDir = player.direction;
	}

	else if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight))
	{
		if (!GetWallCross())
		{
			player.pos = MoveRight(player.MoveDir, player.pos, (sfVector2u) { 64, 0 }, player.speed, -1, _dt);
		}
		else
		{
			player.pos = MoveRight(player.MoveDir, player.pos, (sfVector2u) { 64, 0 }, player.speed, 4, _dt);
		}
		player.direction = RIGHT;
		player.MoveDir = player.direction;
	}
	else
	{
		player.direction = DOWN;
	}

	UpdateAnimation(&playerAnimation, player.sprite, player.texture, player.size, player.direction, _dt);

	CheckPlayerGameAreaCollision();

	CheckPlayerWallCollision();

	CheckPlayerEnemiesCollision();
	CheckPlayerExitCollision();
	CheckGameOver();

	PlayInvincibleAnimation(_dt);
}

void DrawPlayer(sfRenderWindow* _window)
{
	sfSprite_setPosition(player.sprite, player.pos);
	sfRenderWindow_drawSprite(_window, player.sprite, NULL);
}

sfVector2f GetPlayerPos()
{
	return player.pos;
}
sfVector2u GetPlayerSize()
{
	return player.size;
}

float GetPlayerSpeed()
{
	return player.speed;
}
void SetPlayerSpeed(float _speed)
{
	player.speed = _speed;
}
void IncreasePlayerSpeed()
{
	player.speed += 25;
}
void DecreasePlayerSpeed()
{
	player.speed -= 25;
}

unsigned char GetBombAmount()
{
	return player.inventory.bomb;
}
void SetBombAmount(unsigned char _bombAmount)
{
	player.inventory.bomb = _bombAmount;
}
void IncreaseBombAmount()
{
	player.inventory.bomb++;
}
void DecreaseBombAmount()
{
	player.inventory.bomb--;
}

int GetPlayerHP()
{
	return player.HP;
}
void SetPlayerHP(int _HP)
{
	player.HP = _HP;
}
void IncreasePlayerHP()
{
	player.HP++;
}
void DecreasePlayerHP()
{
	player.HP--;
	sfSound_play(soundPlayerHurt);
}

sfBool GetWallCross(void)
{
	return player.wallCross;
}
sfBool GetBombCross(void)
{
	return player.bombCross;
}
sfBool GetInvincible(void)
{
	return player.invincible;
}

void SetWallCross(sfBool _bool)
{
	player.wallCross = _bool;
}
void SetBombCross(sfBool _bool)
{
	player.bombCross = _bool;
}
void SetInvincible(sfBool _bool)
{
	player.invincible = _bool;
}

int* GetPlayerScore()
{
	return &player.score;
}

void AddScore(int _addition)
{
	player.score += _addition;
}

int GetPlayerLevel()
{
	return player.level;
}

void ResetScore()
{
	player.score = 0;
}

void IncreaseLevel()
{
	player.level++;
}

void ResetLevel()
{
	player.level = 1;
}