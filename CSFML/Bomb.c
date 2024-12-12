#include "Bomb.h"
#include "Sounds.h"

struct Bomb bomb[MAX_BOMB_AMOUNT];
sfTexture* ExplosionBombTexture;

struct Animation bombAnimation[MAX_BOMB_AMOUNT];
struct Animation effectLeftAnimation;
struct Animation effectUpAnimation;
struct Animation effectDownAnimation;
struct Animation effectRightAnimation;
struct Animation effectCenterAnimation;

struct Effects effectCenter;
struct Effects effectRight[COLUMN];
struct Effects effectUp[LINE];
struct Effects effectDown[LINE];
struct Effects effectLeft[COLUMN];
struct Encounter encounter;

void ResetBomb()
{
	for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
	{
		bomb[i].rect = (sfIntRect){ 0 * bomb[i].size.x, 0, bomb[i].size.x, bomb[i].size.y };
		bomb[i].isPlaced = sfFalse;
		bomb[i].timer = 2.f;
		bomb[i].power = 1;
		sfSprite_setTextureRect(bomb[i].sprite, bomb[i].rect);

		bomb[i].effectUpAnimation.state = 6;
		bomb[i].effectDownAnimation.state = 6;
		bomb[i].effectRightAnimation.state = 6;
		bomb[i].effectLeftAnimation.state = 6;
		bomb[i].effectCenterAnimation.state = 6;
	}
}

void ReloadBomb()
{
	for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
	{
		bomb[i].rect = (sfIntRect){ 0 * bomb[i].size.x, 0, bomb[i].size.x, bomb[i].size.y };
		bomb[i].isPlaced = sfFalse;
		bomb[i].timer = 2.f;
		sfSprite_setTextureRect(bomb[i].sprite, bomb[i].rect);

		bomb[i].effectUpAnimation.state = 6;
		bomb[i].effectDownAnimation.state = 6;
		bomb[i].effectRightAnimation.state = 6;
		bomb[i].effectLeftAnimation.state = 6;
		bomb[i].effectCenterAnimation.state = 6;
	}
}

void LoadEffects(unsigned char _i)
{
	for (unsigned char i = 0; i < COLUMN; i++)
	{
		bomb[_i].effectRight[i].sprite = sfSprite_create();
		bomb[_i].effectRight[i].size = (sfVector2u){ sfTexture_getSize(bomb[0].effectRight[0].texture).x / 7, sfTexture_getSize(bomb[0].effectRight[0].texture).y / 9 };
		sfSprite_setTexture(bomb[_i].effectRight[i].sprite, bomb[0].effectRight[0].texture, sfTrue);
		sfSprite_setOrigin(bomb[_i].effectRight[i].sprite, (sfVector2f) { bomb[_i].effectRight[i].size.x / 2, bomb[_i].effectRight[i].size.y / 2 });

		bomb[_i].effectLeft[i].sprite = sfSprite_create();
		bomb[_i].effectLeft[i].size = (sfVector2u){ sfTexture_getSize(bomb[0].effectRight[0].texture).x / 7, sfTexture_getSize(bomb[0].effectRight[0].texture).y / 9 };
		sfSprite_setTexture(bomb[_i].effectLeft[i].sprite, bomb[0].effectRight[0].texture, sfTrue);
		sfSprite_setOrigin(bomb[_i].effectLeft[i].sprite, (sfVector2f) { bomb[_i].effectLeft[i].size.x / 2, bomb[_i].effectLeft[i].size.y / 2 });
	}

	for (unsigned char i = 0; i < LINE; i++)
	{
		bomb[_i].effectUp[i].sprite = sfSprite_create();
		bomb[_i].effectUp[i].size = (sfVector2u){ sfTexture_getSize(bomb[0].effectRight[0].texture).x / 7, sfTexture_getSize(bomb[0].effectRight[0].texture).y / 9 };
		sfSprite_setTexture(bomb[_i].effectUp[i].sprite, bomb[0].effectRight[0].texture, sfTrue);
		sfSprite_setOrigin(bomb[_i].effectUp[i].sprite, (sfVector2f) { bomb[_i].effectUp[i].size.x / 2, bomb[_i].effectUp[i].size.y / 2 });

		bomb[_i].effectDown[i].sprite = sfSprite_create();
		bomb[_i].effectDown[i].size = (sfVector2u){ sfTexture_getSize(bomb[0].effectRight[0].texture).x / 7, sfTexture_getSize(bomb[0].effectRight[0].texture).y / 9 };
		sfSprite_setTexture(bomb[_i].effectDown[i].sprite, bomb[0].effectRight[0].texture, sfTrue);
		sfSprite_setOrigin(bomb[_i].effectDown[i].sprite, (sfVector2f) { bomb[_i].effectDown[i].size.x / 2, bomb[_i].effectDown[i].size.y / 2 });

	}

	bomb[_i].effectCenter.sprite = sfSprite_create();
	bomb[_i].effectCenter.size = (sfVector2u){ sfTexture_getSize(bomb[0].effectRight[0].texture).x / 7, sfTexture_getSize(bomb[0].effectRight[0].texture).y / 9 };
	sfSprite_setTexture(bomb[_i].effectCenter.sprite, bomb[0].effectRight[0].texture, sfTrue);
	sfSprite_setOrigin(bomb[_i].effectCenter.sprite, (sfVector2f) { bomb[_i].effectCenter.size.x / 2, bomb[_i].effectCenter.size.y / 2 });
}

void LoadBomb()
{
	ExplosionBombTexture = sfTexture_createFromFile("Assets/Bomb/Bomb.png", NULL);
	bomb[0].effectRight[0].texture = sfTexture_createFromFile("Assets/Bomb/Effects.png", NULL);

	for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
	{
		bomb[i].sprite = sfSprite_create();
		sfSprite_setTexture(bomb[i].sprite, ExplosionBombTexture, sfTrue);

		bomb[i].size = (sfVector2u){ sfTexture_getSize(ExplosionBombTexture).x / 4, sfTexture_getSize(ExplosionBombTexture).y };
		sfSprite_setOrigin(bomb[i].sprite, (sfVector2f) { bomb[0].size.x / 2, bomb[0].size.y / 2 });

		bombAnimation[i] = CreateAnimation(5);

		bomb[i].effectDownAnimation = CreateAnimation(4);
		bomb[i].effectDownAnimation.state = 6;
		bomb[i].effectUpAnimation = CreateAnimation(4);
		bomb[i].effectUpAnimation.state = 6;
		bomb[i].effectRightAnimation = CreateAnimation(4);
		bomb[i].effectRightAnimation.state = 6;
		bomb[i].effectLeftAnimation = CreateAnimation(4);
		bomb[i].effectLeftAnimation.state = 6;
		bomb[i].effectCenterAnimation = CreateAnimation(4);
		bomb[i].effectCenterAnimation.state = 6;

		LoadEffects(i);
	}

	ResetBomb();
}

void PlaceBomb()
{
	sfVector2f playerPos = GetPlayerPos();
	float column = GetColumn(playerPos.x);
	float line = GetLine(playerPos.y + GetPlayerSize().y / 2.66);

	if (GetTilesType(line, column) != WALL && GetTilesType(line, column) != BOX && GetTilesType(line, column) != EXIT)
	{
		for (unsigned char i = 0; i < GetBombAmount(); i++)
		{
			if ((!bomb[i].isPlaced) && (!GetTileBombState(line, column)))
			{
				bomb[i].pos = (sfVector2f){ GetTilesPos(line, column).x + (float)GetTilesSize(line, column).x / 2, GetTilesPos(line, column).y + (float)GetTilesSize(line, column).y / 2 };
				SetTileBombState(line, column, sfTrue);

				sfSprite_setPosition(bomb[i].sprite, bomb[i].pos);
				sfSound_play(soundPlaceBomb);
				bomb[i].isPlaced = sfTrue;
				return;
			}
		}
	}
	
}

void PlayDownExplosionAnimation(unsigned char _i, unsigned char _j, float _dt)
{
	sfVector2f tilePos = GetTilesPos(GetLine(bomb[_i].pos.y) + _j + 1, GetColumn(bomb[_i].pos.x));
	sfVector2u tileSize = GetTilesSize(GetLine(bomb[_i].pos.y) + _j + 1, GetColumn(bomb[_i].pos.x));

	bomb[_i].effectDown[_j].pos = (sfVector2f){ tilePos.x + tileSize.x / 2, tilePos.y + tileSize.y / 2 };
	sfSprite_setPosition(bomb[_i].effectDown[_j].sprite, bomb[_i].effectDown[_j].pos);

	if (_j != bomb[_i].power - 1)
	{
		bomb[_i].effectDownAnimation.state = 0;
		bomb[_i].effectDown[_j].yState = 7;
	}
	else
	{
		bomb[_i].effectDownAnimation.state = 0;
		bomb[_i].effectDown[_j].yState = 8;
	}
}

void PlayUpExplosionAnimation(unsigned char _i, unsigned char _j, float _dt)
{
	sfVector2f tilePos = GetTilesPos(GetLine(bomb[_i].pos.y) - _j - 1, GetColumn(bomb[_i].pos.x));
	sfVector2u tileSize = GetTilesSize(GetLine(bomb[_i].pos.y) - _j - 1, GetColumn(bomb[_i].pos.x));

	bomb[_i].effectUp[_j].pos = (sfVector2f){ tilePos.x + tileSize.x / 2, tilePos.y + tileSize.y / 2 };
	sfSprite_setPosition(bomb[_i].effectUp[_j].sprite, bomb[_i].effectUp[_j].pos);

	if (_j != bomb[_i].power - 1)
	{
		bomb[_i].effectUpAnimation.state = 0;
		bomb[_i].effectUp[_j].yState = 1;
	}
	else
	{
		bomb[_i].effectUpAnimation.state = 0;
		bomb[_i].effectUp[_j].yState = 2;
	}
}

void PlayRightExplosionAnimation(unsigned char _i, unsigned char _j, float _dt)
{
	sfVector2f tilePos = GetTilesPos(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + _j + 1);
	sfVector2u tileSize = GetTilesSize(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + _j + 1);

	bomb[_i].effectRight[_j].pos = (sfVector2f){ tilePos.x + tileSize.x / 2, tilePos.y + tileSize.y / 2 };
	sfSprite_setPosition(bomb[_i].effectRight[_j].sprite, bomb[_i].effectRight[_j].pos);

	if (_j != bomb[_i].power - 1)
	{
		bomb[_i].effectRightAnimation.state = 0;
		bomb[_i].effectRight[_j].yState = 5;
	}
	else
	{
		bomb[_i].effectRightAnimation.state = 0;
		bomb[_i].effectRight[_j].yState = 6;
	}
}

void PlayLeftExplosionAnimation(unsigned char _i, unsigned char _j, float _dt)
{
	sfVector2f tilePos = GetTilesPos(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - _j - 1);
	sfVector2u tileSize = GetTilesSize(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - _j - 1);

	bomb[_i].effectLeft[_j].pos = (sfVector2f){ tilePos.x + tileSize.x / 2, tilePos.y + tileSize.y / 2 };
	sfSprite_setPosition(bomb[_i].effectLeft[_j].sprite, bomb[_i].effectLeft[_j].pos);

	if (_j != bomb[_i].power - 1)
	{
		bomb[_i].effectLeftAnimation.state = 0;
		bomb[_i].effectLeft[_j].yState = 3;
	}
	else
	{
		bomb[_i].effectLeftAnimation.state = 0;
		bomb[_i].effectLeft[_j].yState = 4;
	}
}

void PlayCenterExplosionAnimation(unsigned char _i, float _dt)
{
	sfVector2f tilePos = GetTilesPos(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x));
	sfVector2u tileSize = GetTilesSize(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x));

	bomb[_i].effectCenter.pos = (sfVector2f){ tilePos.x + tileSize.x / 2, tilePos.y + tileSize.y / 2 };
	sfSprite_setPosition(bomb[_i].effectCenter.sprite, bomb[_i].effectCenter.pos);

	bomb[_i].effectCenterAnimation.state = 0;
	bomb[_i].effectCenter.yState = 0;
}

void Explode(unsigned char _i, float _dt)
{
	encounter.left = sfFalse;
	encounter.right = sfFalse;
	encounter.up = sfFalse;
	encounter.down = sfFalse;

	SetTileExplodingState(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x), sfTrue);
	PlayCenterExplosionAnimation(_i, _dt);

	if ((GetLine(GetPlayerPos().y) == GetLine(bomb[_i].pos.y)) && (GetColumn(GetPlayerPos().x) == GetColumn(bomb[_i].pos.x)))
		PlayerTakeHit();
		
		
	    

	Enemy* enemiesList = GetEnemiesList();
	for (int e = 0; e < MAX_ENEMIES_AMOUNT; e++)
	{
		if (enemiesList[e].alive)
		{
			if ((GetLine(GetEnemyPos(e).y) == GetLine(bomb[_i].pos.y)) && (GetColumn(GetEnemyPos(e).x) == GetColumn(bomb[_i].pos.x)))
			{
				DecreaseEnemyHP(e);
				
			}
		}
	}

	for (unsigned char j = 0; j < bomb[_i].power; j++)
	{
		if (GetColumn(bomb[_i].pos.x) + j + 1 < COLUMN)
		{
			if (!encounter.right)
			{
				if (GetTilesType(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + j + 1) != WALL && GetTilesType(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + j + 1) != EXIT)
				{
					PlayRightExplosionAnimation(_i, j, _dt);
					SetTileExplodingState(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + j + 1, sfTrue);

					if ((GetLine(GetPlayerPos().y) == GetLine(bomb[_i].pos.y)) && (GetColumn(GetPlayerPos().x) == GetColumn(bomb[_i].pos.x) + j + 1))
						PlayerTakeHit();

					Enemy* enemiesList = GetEnemiesList();
					for (int e = 0; e < MAX_ENEMIES_AMOUNT; e++)
					{
						if (enemiesList[e].alive)
						{
							if ((GetLine(GetEnemyPos(e).y) == GetLine(bomb[_i].pos.y)) && (GetColumn(GetEnemyPos(e).x) == GetColumn(bomb[_i].pos.x) + j + 1))
							{
								DecreaseEnemyHP(e);
							}
						}
					}

					if (GetTilesType(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + j + 1) == BOX)
					{
						encounter.right = sfTrue;

						if (HasExit(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + j + 1))
						{
							SetTileExplodingState(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + j + 1, sfFalse);
							SetTileType(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + j + 1, EXIT);
						}
						else if (rand() % 2 == 1)
						{
							PlaceItem(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) + j + 1);
						}
					}
				}
				else
					encounter.right = sfTrue;
			}
		}

		if (GetColumn(bomb[_i].pos.x) - j - 1 >= 0)
		{
			if (!encounter.left)
			{
				if (GetTilesType(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - j - 1) != WALL && GetTilesType(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - j - 1) != EXIT)
				{
					PlayLeftExplosionAnimation(_i, j, _dt);
					SetTileExplodingState(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - j - 1, sfTrue);

					if ((GetLine(GetPlayerPos().y) == GetLine(bomb[_i].pos.y)) && (GetColumn(GetPlayerPos().x) == GetColumn(bomb[_i].pos.x) - j - 1))
						PlayerTakeHit();

					Enemy* enemiesList = GetEnemiesList();
					for (int e = 0; e < MAX_ENEMIES_AMOUNT; e++)
					{
						if (enemiesList[e].alive)
						{
							if ((GetLine(GetEnemyPos(e).y) == GetLine(bomb[_i].pos.y)) && (GetColumn(GetEnemyPos(e).x) == GetColumn(bomb[_i].pos.x) - j - 1))
							{
								DecreaseEnemyHP(e);
							}
						}
					}

					if (GetTilesType(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - j - 1) == BOX)
					{
						encounter.left = sfTrue;

						if (HasExit(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - j - 1))
						{
							SetTileExplodingState(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - j - 1, sfFalse);
							SetTileType(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - j - 1, EXIT);
						}
						else if (rand() % 2 == 1)
						{
							PlaceItem(GetLine(bomb[_i].pos.y), GetColumn(bomb[_i].pos.x) - j - 1);
						}
					}
				}
				else
					encounter.left = sfTrue;
			}
		}

		if (GetLine(bomb[_i].pos.y) + j + 1 < LINE)
		{
			if (!encounter.down)
			{
				if (GetTilesType(GetLine(bomb[_i].pos.y) + j + 1, GetColumn(bomb[_i].pos.x)) != WALL && GetTilesType(GetLine(bomb[_i].pos.y) + j + 1, GetColumn(bomb[_i].pos.x)) != EXIT)
				{
					PlayDownExplosionAnimation(_i, j, _dt);
					SetTileExplodingState(GetLine(bomb[_i].pos.y) + j + 1, GetColumn(bomb[_i].pos.x), sfTrue);

					if ((GetLine(GetPlayerPos().y) == GetLine(bomb[_i].pos.y) + j + 1) && (GetColumn(GetPlayerPos().x) == GetColumn(bomb[_i].pos.x)))
						PlayerTakeHit();

					Enemy* enemiesList = GetEnemiesList();
					for (int e = 0; e < MAX_ENEMIES_AMOUNT; e++)
					{
						if (enemiesList[e].alive)
						{
							if ((GetLine(GetEnemyPos(e).y) == GetLine(bomb[_i].pos.y) + j + 1) && (GetColumn(GetEnemyPos(e).x) == GetColumn(bomb[_i].pos.x)))
							{
								DecreaseEnemyHP(e);
							}
						}
					}

					if (GetTilesType(GetLine(bomb[_i].pos.y) + j + 1, GetColumn(bomb[_i].pos.x)) == BOX)
					{
						encounter.down = sfTrue;

						if (HasExit(GetLine(bomb[_i].pos.y) + j + 1, GetColumn(bomb[_i].pos.x)))
						{
							SetTileExplodingState(GetLine(bomb[_i].pos.y) + j + 1, GetColumn(bomb[_i].pos.x), sfFalse);
							SetTileType(GetLine(bomb[_i].pos.y) + j + 1, GetColumn(bomb[_i].pos.x), EXIT);
						}
						else if (rand() % 2 == 1)
						{
							PlaceItem(GetLine(bomb[_i].pos.y) + j + 1, GetColumn(bomb[_i].pos.x));
						}
					}
				}
				else
					encounter.down = sfTrue;
			}
		}

		if (GetLine(bomb[_i].pos.y) - j - 1 >= 0)
		{
			if (!encounter.up)
			{
				if (GetTilesType(GetLine(bomb[_i].pos.y) - j - 1, GetColumn(bomb[_i].pos.x)) != WALL && GetTilesType(GetLine(bomb[_i].pos.y) - j - 1, GetColumn(bomb[_i].pos.x)) != EXIT)
				{
					PlayUpExplosionAnimation(_i, j, _dt);
					SetTileExplodingState(GetLine(bomb[_i].pos.y) - j - 1, GetColumn(bomb[_i].pos.x), sfTrue);

					if ((GetLine(GetPlayerPos().y) == GetLine(bomb[_i].pos.y) - j - 1) && (GetColumn(GetPlayerPos().x) == GetColumn(bomb[_i].pos.x)))
						PlayerTakeHit();

					Enemy* enemiesList = GetEnemiesList();
					for (int e = 0; e < MAX_ENEMIES_AMOUNT; e++)
					{
						if (enemiesList[e].alive)
						{
							if ((GetLine(GetEnemyPos(e).y) == GetLine(bomb[_i].pos.y) - j - 1) && (GetColumn(GetEnemyPos(e).x) == GetColumn(bomb[_i].pos.x)))
							{
								DecreaseEnemyHP(e);
							}
						}
					}

					if (GetTilesType(GetLine(bomb[_i].pos.y) - j - 1, GetColumn(bomb[_i].pos.x)) == BOX)
					{
						encounter.up = sfTrue;

						if (HasExit(GetLine(bomb[_i].pos.y) - j - 1, GetColumn(bomb[_i].pos.x)))
						{
							SetTileExplodingState(GetLine(bomb[_i].pos.y) - j - 1, GetColumn(bomb[_i].pos.x), sfFalse);
							SetTileType(GetLine(bomb[_i].pos.y) - j - 1, GetColumn(bomb[_i].pos.x), EXIT);
						}
						else if (rand() % 2 == 1)
						{
							PlaceItem(GetLine(bomb[_i].pos.y) - j - 1, GetColumn(bomb[_i].pos.x));
						}
					}
				}
				else
					encounter.up = sfTrue;
			}
		}
	}
	sfSound_play(soundExplode);
}

void UpdateBombAnimation(float _dt)
{
	for (unsigned char j = 0; j < GetBombAmount(); j++)
	{
		if (bomb[j].effectUpAnimation.state < 6)
			for (unsigned char i = 0; i < bomb[0].power; i++)
			{
				bomb[j].effectUpAnimation.framerate = 1.f / bomb[j].power * 15;
				UpdateAnimation(&bomb[j].effectUpAnimation, bomb[j].effectUp[i].sprite, bomb[0].effectRight[0].texture, bomb[j].effectUp[0].size, bomb[j].effectUp[i].yState, _dt);
			}
		else
		{
			for (unsigned char i = 0; i < bomb[j].power; i++)
			{
				bomb[j].effectUp[i].pos = (sfVector2f){ 4000, 4000 };
				sfSprite_setPosition(bomb[j].effectUp[i].sprite, bomb[j].effectUp[i].pos);
				bomb[j].effectUpAnimation.timer = 0;
			}
		}

		if (bomb[j].effectDownAnimation.state < 6)
			for (unsigned char i = 0; i < bomb[0].power; i++)
			{
				bomb[j].effectDownAnimation.framerate = 1.f / bomb[j].power * 15;
				UpdateAnimation(&bomb[j].effectDownAnimation, bomb[j].effectDown[i].sprite, bomb[0].effectRight[0].texture, bomb[j].effectDown[0].size, bomb[j].effectDown[i].yState, _dt);
			}
		else
		{
			for (unsigned char i = 0; i < bomb[j].power; i++)
			{
				bomb[j].effectDown[i].pos = (sfVector2f){ 4000, 4000 };
				sfSprite_setPosition(bomb[j].effectDown[i].sprite, bomb[j].effectDown[i].pos);
				bomb[j].effectDownAnimation.timer = 0;
			}
		}

		if (bomb[j].effectRightAnimation.state < 6)
			for (unsigned char i = 0; i < bomb[0].power; i++)
			{
				bomb[j].effectRightAnimation.framerate = 1.f / bomb[j].power * 15;
				UpdateAnimation(&bomb[j].effectRightAnimation, bomb[j].effectRight[i].sprite, bomb[0].effectRight[0].texture, bomb[j].effectRight[0].size, bomb[j].effectRight[i].yState, _dt);
			}
		else
		{
			for (unsigned char i = 0; i < bomb[j].power; i++)
			{
				bomb[j].effectRight[i].pos = (sfVector2f){ 4000, 4000 };
				sfSprite_setPosition(bomb[j].effectRight[i].sprite, bomb[j].effectRight[i].pos);
				bomb[j].effectRightAnimation.timer = 0;
			}
		}

		if (bomb[j].effectLeftAnimation.state < 6)
			for (unsigned char i = 0; i < bomb[0].power; i++)
			{
				bomb[j].effectLeftAnimation.framerate = 1.f / bomb[j].power * 15;
				UpdateAnimation(&bomb[j].effectLeftAnimation, bomb[j].effectLeft[i].sprite, bomb[0].effectRight[0].texture, bomb[j].effectLeft[0].size, bomb[j].effectLeft[i].yState, _dt);
			}
		else
		{
			for (unsigned char i = 0; i < bomb[j].power; i++)
			{
				bomb[j].effectLeft[i].pos = (sfVector2f){ 4000, 4000 };
				sfSprite_setPosition(bomb[j].effectLeft[i].sprite, bomb[j].effectLeft[i].pos);
				bomb[j].effectLeftAnimation.timer = 0;
			}
		}

		if (bomb[j].effectCenterAnimation.state < 6)
			for (unsigned char i = 0; i < bomb[0].power; i++)
			{
				bomb[j].effectCenterAnimation.framerate = 1.f / bomb[j].power * 15;
				UpdateAnimation(&bomb[j].effectCenterAnimation, bomb[j].effectCenter.sprite, bomb[0].effectRight[0].texture, bomb[j].effectCenter.size, bomb[j].effectCenter.yState, _dt);
			}
		else
		{
			for (unsigned char i = 0; i < bomb[j].power; i++)
			{
				bomb[j].effectCenter.pos = (sfVector2f){ 4000, 4000 };
				sfSprite_setPosition(bomb[j].effectCenter.sprite, bomb[j].effectCenter.pos);
				bomb[j].effectCenterAnimation.timer = 0;
			}
		}
	}
}

void UpdateBomb(float _dt)
{
	for (unsigned char i = 0; i < GetBombAmount(); i++)
	{
		if (bomb[i].isPlaced)
		{
			bomb[i].timer -= _dt;
			UpdateAnimation(&bombAnimation[i], bomb[i].sprite, ExplosionBombTexture, bomb[i].size, 0, _dt);
		}
		else
			bombAnimation[i] = CreateAnimation(5);

		if (bomb[i].timer <= 0)
		{
			Explode(i, _dt);

			SetTileBombState(GetLine(bomb[i].pos.y), GetColumn(bomb[i].pos.x), sfFalse);
			bomb[i].isPlaced = sfFalse;
			bomb[i].timer = 2.f;
		}
	}

	UpdateBombAnimation(_dt);
}

void DrawBombAnimation(sfRenderWindow* _window)
{
	for (unsigned char j = 0; j < GetBombAmount(); j++)
	{
		for (unsigned char i = 0; i < bomb[0].power; i++)
		{
			if ((bomb[j].effectUpAnimation.state < 6) ||
				(bomb[j].effectDownAnimation.state < 6) ||
				(bomb[j].effectRightAnimation.state < 6) ||
				(bomb[j].effectLeftAnimation.state < 6) ||
				(bomb[j].effectCenterAnimation.state < 6))
			{
				sfRenderWindow_drawSprite(_window, bomb[j].effectDown[i].sprite, NULL);
				sfRenderWindow_drawSprite(_window, bomb[j].effectUp[i].sprite, NULL);
				sfRenderWindow_drawSprite(_window, bomb[j].effectRight[i].sprite, NULL);
				sfRenderWindow_drawSprite(_window, bomb[j].effectLeft[i].sprite, NULL);
				sfRenderWindow_drawSprite(_window, bomb[j].effectCenter.sprite, NULL);
			}
		}
	}
}

void DrawBomb(sfRenderWindow* _window)
{
	for (unsigned char i = 0; i < GetBombAmount(); i++)
	{
		if (bomb[i].isPlaced)
		{
			sfRenderWindow_drawSprite(_window, bomb[i].sprite, NULL);
		}
	}
	DrawBombAnimation(_window);
}

struct Bomb* GetBombs()
{
	return &bomb;
}

int GetBombPower()
{
	return bomb[0].power;
}

void SetBombPower(int _power)
{
	for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
	{
		bomb[i].power = _power;
	}
}

void IncreaseBombPower()
{
	for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
	{
		bomb[i].power++;
	}
}

void DecreaseBombPower()
{
	for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
	{
		bomb[i].power--;
	}
}