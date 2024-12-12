#include "Enemy.h"
#include "Sounds.h"

sfTexture* enemiesTexturess[6];
Enemy enemies[MAX_ENEMIES_AMOUNT];

struct Animation ratAnimation;
struct Animation blobAnimation;
struct Animation eyeAnimation;
struct Animation wormAnimation;
struct Animation shadowAnimation;
struct Animation cyclopeAnimation;

float highlightEnemiesTimer;

void LoadEnemies(void)
{
	LoadEnemiesTextures();
	highlightEnemiesTimer = 2.f;
}

void ClearEnemy(unsigned int _i)
{
	enemies[_i].alive = sfFalse;

	switch (enemies[_i].name)
	{
	case (RAT):
		*GetPlayerScore() += 100;
		break;
	case (BLOB):
		*GetPlayerScore() += 200;
		break;
	case (EYE):
		*GetPlayerScore() += 400;
		break;
	case (WORM):
		*GetPlayerScore() += 2000;
		break;
	case (SHADOW):
		*GetPlayerScore() += 4000;
		break;
	case (CYCLOPE):
		*GetPlayerScore() += 1000;
		break;
	default:
		*GetPlayerScore() += 100;
		break;
	}
}

void ClearEnemiesList()
{
	for (int i = 0; i < MAX_ENEMIES_AMOUNT; i++)
	{
		enemies[i] = (Enemy){ NULL };
	}
}

void CreateEnemiesRoom(int _level)
{
	ClearEnemiesList();

	for (int i = 0; i < 2 * _level; i++)
	{
		if (i == MAX_ENEMIES_AMOUNT + 1)
		{
			return;
		}
		else
		{
			int prob = rand() % 80 + (_level * 4);
			sfVector2i pos;
			do
			{
				pos = (sfVector2i){ 2 + rand() % (LINE - 2), 2 + rand() % (COLUMN - 2) };
			} while (GetTilesType(pos.x, pos.y) != GROUND);

			if (prob < 25)
			{
				CreateRat(pos);
			}
			else if (prob < 50)
			{
				CreateBlob(pos);
			}
			else if (prob < 70)
			{
				CreateWorm(pos);
			}
			else if (prob < 80)
			{
				CreateEye(pos);
			}
			else if (prob < 90)
			{
				CreateCyclope(pos);
			}
			else if (prob < 100)
			{
				CreateShadow(pos);
			}
			else
			{
				CreateRat(pos);
				break;
			}
		}
	}
}

void LoadEnemiesTextures(void)
{
	enemiesTexturess[RAT] = sfTexture_createFromFile("Assets/Enemies/EnemyRat.png", NULL);
	enemiesTexturess[BLOB] = sfTexture_createFromFile("Assets/Enemies/EnemyBloodyBlob.png", NULL);
	enemiesTexturess[EYE] = sfTexture_createFromFile("Assets/Enemies/EnemyEye.png", NULL);
	enemiesTexturess[WORM] = sfTexture_createFromFile("Assets/Enemies/EnemyLarve.png", NULL);
	enemiesTexturess[SHADOW] = sfTexture_createFromFile("Assets/Enemies/EnemyShadow.png", NULL);
	enemiesTexturess[CYCLOPE] = sfTexture_createFromFile("Assets/Enemies/EnemyCyclope.png", NULL);
}

int GetEmptyObject()
{
	for (int i = 0; i < MAX_ENEMIES_AMOUNT; i++)
	{
		if (!enemies[i].alive)
		{
			return i;
		}
	}

	return -1;
}

void AddEnemy(Enemy* _enemyList, Enemy _enemy)
{
	*_enemyList = _enemy;
}

Enemy CreateRat(sfVector2i _pos)
{
	int num = GetEmptyObject();

	if (num != -1)
	{
		AddEnemy(&enemies[num], CreateEnemy(RAT, (sfVector2u) { 59, 50 }, _pos, 66.0f));
	}
}

Enemy CreateBlob(sfVector2i _pos)
{
	int num = GetEmptyObject();

	if (num != -1)
	{
		AddEnemy(&enemies[num], CreateEnemy(BLOB, (sfVector2u) { 56, 50 }, _pos, 50.0f));
	}
}

Enemy CreateEye(sfVector2i _pos)
{
	int num = GetEmptyObject();

	if (num != -1)
	{
		AddEnemy(&enemies[num], CreateEnemy(EYE, (sfVector2u) { 35, 54 }, _pos, 50.0f));
	}
}

Enemy CreateWorm(sfVector2i _pos)
{
	int num = GetEmptyObject();

	if (num != -1)
	{
		AddEnemy(&enemies[num], CreateEnemy(WORM, (sfVector2u) { 30, 49 }, _pos, 50.0f));
	}
}

Enemy CreateShadow(sfVector2i _pos)
{
	int num = GetEmptyObject();

	if (num != -1)
	{
		AddEnemy(&enemies[num], CreateEnemy(SHADOW, (sfVector2u) { 40, 62 }, _pos, 50.0f));
	}
}

Enemy CreateCyclope(sfVector2i _pos)
{
	int num = GetEmptyObject();

	if (num != -1)
	{
		AddEnemy(&enemies[num], CreateEnemy(CYCLOPE, (sfVector2u) { 48, 50 }, _pos, 50.0f));
	}
}

Enemy CreateEnemy(enum EnemiesName _name, sfVector2u _size, sfVector2i _pos, float _speed)
{
	Enemy enemy;

	enemy.name = _name;
	enemy.HP = 1;
	enemy.alive = sfTrue;
	enemy.MoveDir = DOWN;
	enemy.speed = _speed;

	enemy.sprite = sfSprite_create();
	enemy.texture = enemiesTexturess[enemy.name];
	sfSprite_setTexture(enemy.sprite, enemy.texture, sfTrue);
	enemy.textureSize = sfTexture_getSize(enemy.texture);
	sfIntRect rectTexture = (sfIntRect){ 0, 0, _size.x, _size.y };
	sfSprite_setTextureRect(enemy.sprite, rectTexture);

	enemy.textureSize = sfTexture_getSize(enemy.texture);
	enemy.size = _size;

	sfSprite_setOrigin(enemy.sprite, (sfVector2f) { _size.x / 2, _size.y / 2 });

	sfVector2f tilePos = GetTilesPos(_pos.x, _pos.y);
	enemy.pos = (sfVector2f){ tilePos.x + 64 / 2, tilePos.y + 64 / 2 };
	sfSprite_setPosition(enemy.sprite, enemy.pos);

	enemy.animation = CreateAnimation(3);

	return enemy;
}

void HighlightEnemies(float _dt)
{
	for (int i = 0; i < MAX_ENEMIES_AMOUNT; i++)
	{
		if (enemies[i].alive)
		{
			if (highlightEnemiesTimer < 2.f)
			{
				highlightEnemiesTimer += _dt;
				sfSprite_setColor(enemies[i].sprite, sfColor_fromRGB(128 + (255-128) * highlightEnemiesTimer / 2, 128 + (255 - 128) * highlightEnemiesTimer / 2, 255));
				if (highlightEnemiesTimer > 2.f)
				{
					highlightEnemiesTimer = 2.f;
					sfSprite_setColor(enemies[i].sprite, sfColor_fromRGB(255, 255, 255));
				}
			}
		}
	}
}

void UpdateEnemies(float _dt)
{
	for (int i = 0; i < MAX_ENEMIES_AMOUNT; i++)
	{
		if (enemies[i].alive)
		{
			enemies[i].pos = BasicIA(&enemies[i].MoveDir, enemies[i].pos, enemies[i].size, enemies[i].speed, enemies[i].name, _dt);

			if (enemies[i].HP <= 0)
			{
				ClearEnemy(i);
			}

			UpdateAnimation(&enemies[i].animation, enemies[i].sprite, enemies[i].texture, enemies[i].size, 0, _dt);

			switch (enemies[i].MoveDir)
			{
			case RIGHT:
				sfSprite_setScale(enemies[i].sprite, (sfVector2f) { 1, 1 });
				break;

			case LEFT:
				sfSprite_setScale(enemies[i].sprite, (sfVector2f) { -1, 1 });
				break;

			default:
				break;
			}

			HighlightEnemies(_dt);
		}
	}
}

void DrawEnemies(sfRenderWindow* _window)
{
	for (int i = 0; i < MAX_ENEMIES_AMOUNT; i++)
	{
		if (enemies[i].alive)
		{
			sfSprite_setPosition(enemies[i].sprite, enemies[i].pos);
			sfRenderWindow_drawSprite(_window, enemies[i].sprite, NULL);
		}
	}
}

Enemy* GetEnemiesList(void)
{
	return &enemies;
}

sfVector2f GetEnemyPos(unsigned int _i)
{
	return enemies[_i].pos;
}

void DecreaseEnemyHP(unsigned _i)
{
	enemies[_i].HP--;
	sfSound_play(soundEnemyDeath);
}

void TriggerHighlightEnemies()
{
	highlightEnemiesTimer = 0.f;
}

float GetHighlightEnemiesTimer()
{
	return highlightEnemiesTimer;
}