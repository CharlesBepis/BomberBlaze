#include "Map.h"

struct Map map;
struct Tiles tiles[LINE][COLUMN];

void CreateMap(void)
{
	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			tiles[i][j].sprite = sfSprite_create();
			sfSprite_setTexture(tiles[i][j].sprite, tiles[0][0].texture, sfTrue);

			tiles[i][j].size = (sfVector2u){ 64, 64 };
			tiles[i][j].pos = (sfVector2f){ (SCREEN_WIDTH - tiles[i][j].size.x * COLUMN) / 2 + j * 64, (SCREEN_HEIGHT - tiles[i][j].size.y * LINE) / 2 + i * 64 };
			tiles[i][j].rand = rand() % 100;
			tiles[i][j].hasItem = sfFalse;
			tiles[i][j].hasBomb = sfFalse;
			tiles[i][j].isExploding = sfFalse;
			tiles[i][j].hasExit = sfFalse;

			sfSprite_setPosition(tiles[i][j].sprite, tiles[i][j].pos);

			//Generation de base sans les caisses
			if (i % 2 != 0)
			{
				if (j % 2 != 0)
				{
					tiles[i][j].type = WALL;
				}
				else
				{
					tiles[i][j].type = GROUND;
				}
			}
			else
			{
				tiles[i][j].type = GROUND;
			}

			//Ajout des caisses en aleatoire
			if (tiles[i][j].type == GROUND)
			{
				if (tiles[i][j].rand >= 0 && tiles[i][j].rand < 80)
				{
					tiles[i][j].type = GROUND;
				}
				else
				{
					tiles[i][j].type = BOX;
				}
			}
			//zone safe joueur

			if (i <= 2 && j <= 2)
			{
				tiles[i][j].type = GROUND;
			}
			tiles[1][1].type = WALL;
		}
	}

	int line;
	int column;

	do
	{
		line = 2 + rand() % (11 - 2);
		column = 2 + rand() % (13 - 2);
	} while (tiles[line][column].type != GROUND);

	tiles[line][column].type = BOX;
	tiles[line][column].hasExit = sfTrue;
}

void LoadMap(void)
{
	tiles[0][0].texture = sfTexture_createFromFile("Assets/Map/MapTile.png", NULL);

	map.sprite = sfSprite_create();
	map.texture = sfTexture_createFromFile("Assets/Map/Walls.png", NULL);
	sfSprite_setTexture(map.sprite, map.texture, sfTrue);
	map.pos = (sfVector2f){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	map.size = sfTexture_getSize(map.texture);
	sfSprite_setOrigin(map.sprite, (sfVector2f) { map.size.x / 2, map.size.y / 2 });
	sfSprite_setPosition(map.sprite, map.pos);

	CreateMap();
}

void UpdateMap()
{
	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			int frameWidth = (int)tiles[i][j].size.x;
			int frameHeight = (int)tiles[i][j].size.y;
			sfIntRect rect = { tiles[i][j].type * frameWidth, 0 * frameHeight, frameWidth, frameHeight };
			sfSprite_setTextureRect(tiles[i][j].sprite, rect);

			if (tiles[i][j].isExploding)
				tiles[i][j].type = EXPLODED_GROUND;
		}
	}
}

void DrawMap(sfRenderWindow* _window)
{

	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (tiles[i][j].type == GROUND || tiles[i][j].type == EXPLODED_GROUND)
				sfRenderWindow_drawSprite(_window, tiles[i][j].sprite, NULL);
		}
	}

	DrawItem(_window);

	for (int i = 0; i < LINE; i++)
	{
		for (int j = 0; j < COLUMN; j++)
		{
			if (tiles[i][j].type != GROUND && tiles[i][j].type != EXPLODED_GROUND)
				sfRenderWindow_drawSprite(_window, tiles[i][j].sprite, NULL);
		}
	}
}

void DrawBackgroundMap(sfRenderWindow* _window)
{
	sfRenderWindow_drawSprite(_window, map.sprite, NULL);
}

sfVector2f GetTilesPos(int _i, int _j)
{
	return tiles[_i][_j].pos;
}

sfVector2u GetTilesSize(int _i, int _j)
{
	return tiles[_i][_j].size;
}

int GetTilesType(int _i, int _j)
{
	return tiles[_i][_j].type;
}

sfBool GetTileItemState(int _i, int _j)
{
	return tiles[_i][_j].hasItem;
}
void SetTileItemState(int _i, int _j, sfBool _hasItem)
{
	tiles[_i][_j].hasItem = _hasItem;
}

sfBool GetTileBombState(int _i, int _j)
{
	return tiles[_i][_j].hasBomb;
}
void SetTileBombState(int _i, int _j, sfBool _hasBomb)
{
	tiles[_i][_j].hasBomb = _hasBomb;
}

sfBool GetTileExplodingState(int _i, int _j)
{
	return tiles[_i][_j].isExploding;
}
void SetTileExplodingState(int _i, int _j, sfBool _isExploding)
{
	tiles[_i][_j].isExploding = _isExploding;
}

void SetTileType(int _i, int _j, enum Type _type)
{
	tiles[_i][_j].type = _type;
}

int GetColumn(float _x)
{
	int column = (_x - tiles[0][0].pos.x) / tiles[0][0].size.x;

	if ((column >= 0) && (column <= COLUMN))
	{
		return column;
	}
	else
	{
		return -1;
	}
}

int GetLine(float _y)
{
	int line = (_y - tiles[0][0].pos.y) / tiles[0][0].size.y;

	if ((line >= 0) && (line <= LINE))
	{
		return line;
	}
	else
	{
		return -1;
	}
}

sfBool HasExit(int _line, int _column)
{
	return tiles[_line][_column].hasExit;
}