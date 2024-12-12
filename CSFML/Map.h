#ifndef MAP_H
#define MAP_H

#include"Libraries.h"
#include"SFML.h"
#include"Screen.h"

#include"Item.h"

#define LINE 11
#define COLUMN 13

struct Map
{
	sfSprite* sprite;
	sfTexture* texture;
	sfVector2f pos;
	sfVector2u size;
};

enum Type
{
	WALL,
	GROUND,
	BOX,
	EXPLODED_GROUND,
	EXIT
};

struct Tiles
{
	sfVector2f pos;
	sfVector2u size;
	sfSprite* sprite;
	sfTexture* texture;
	int rand;
	enum Type type;
	sfBool hasItem;
	sfBool hasBomb;
	sfBool isExploding;
	sfBool hasExit;
};

void LoadMap(void);
void CreateMap(void);
void UpdateMap(void);
void DrawMap(sfRenderWindow* window);
void DrawBackgroundMap(sfRenderWindow* _window);

sfVector2f GetTilesPos(int line, int column);
sfVector2u GetTilesSize(int line, int column);
int GetTilesType(int line, int column);
sfBool GetTileItemState(int line, int column);
sfBool GetTileBombState(int line, int column);
sfBool GetTileExplodingState(int line, int column);
int GetColumn(float x);
int GetLine(float y);
sfBool HasExit(int line, int column);

void SetTileItemState(int line, int column, sfBool hasItem);
void SetTileBombState(int line, int column, sfBool hasBomb);
void SetTileExplodingState(int line, int column, sfBool isExploding);
void SetTileType(int i, int j, enum Type type);

#endif // !MAP_H