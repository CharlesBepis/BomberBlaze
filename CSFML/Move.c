#include "Move.h"

int checkCloseY(sfVector2f _pos)
{
	return (int)_pos.y % 64 > 32;
}

int checkCloseX(sfVector2f _pos)
{
	return (int)_pos.x % 64 > 32;
}
enum Direction ChangeDirection(sfVector2i _posMap)
{
	enum Direction newDirection;
	int downTile;
	int upTile;
	int rightTile;
	int leftTile;
	int random = rand() % (3);

	if (_posMap.y + 2 > LINE)
	{
		downTile = 0;
	}
	else
	{
		downTile = GetTilesType(_posMap.y + 1, _posMap.x);
	}

	if (_posMap.y - 1 < 0)
	{
		upTile = 0;
	}
	else
	{
		upTile = GetTilesType(_posMap.y - 1, _posMap.x);
	}

	if (_posMap.x + 2 > COLUMN)
	{
		rightTile = 0;
	}
	else
	{
		rightTile = GetTilesType(_posMap.y, _posMap.x + 1);
	}

	if (_posMap.x - 1 < 0)
	{
		leftTile = 0;
	}
	else
	{
		leftTile = GetTilesType(_posMap.y, _posMap.x - 1);
	}

	switch (random)
	{
	case (1):
		if ((!GetTileBombState(_posMap.y - 1, _posMap.x) && upTile != 0 && upTile != 2))
		{
			newDirection = UP;
		}
		else if ((!GetTileBombState(_posMap.y + 1, _posMap.x) && downTile != 0 && downTile != 2))
		{
			newDirection = DOWN;
		}
		else if ((!GetTileBombState(_posMap.y, _posMap.x + 1) && rightTile != 0 && rightTile != 2))
		{
			newDirection = RIGHT;
		}
		else
		{
			newDirection = LEFT;
		}
		break;
	case (2):
		if ((!GetTileBombState(_posMap.y + 1, _posMap.x) && downTile != 0 && downTile != 2))
		{
			newDirection = DOWN;
		}
		else if ((!GetTileBombState(_posMap.y - 1, _posMap.x) && upTile != 0 && upTile != 2))
		{
			newDirection = UP;
		}
		else if ((!GetTileBombState(_posMap.y, _posMap.x - 1) && leftTile != 0 && leftTile != 2))
		{
			newDirection = LEFT;
		}
		else if ((!GetTileBombState(_posMap.y, _posMap.x + 1) && rightTile != 0 && rightTile != 2))
		{
			newDirection = RIGHT;
		}
		else
		{
			newDirection = LEFT;
		}
		break;
	case (3):
		if ((!GetTileBombState(_posMap.y, _posMap.x + 1) && rightTile != 0 && rightTile != 2))
		{
			newDirection = RIGHT;
		}
		else if ((!GetTileBombState(_posMap.y, _posMap.x - 1) && leftTile != 0 && leftTile != 2))
		{
			newDirection = LEFT;
		}
		else if ((!GetTileBombState(_posMap.y - 1, _posMap.x) && upTile != 0 && upTile != 2))
		{
			newDirection = UP;
		}
		else if ((!GetTileBombState(_posMap.y + 1, _posMap.x) && downTile != 0 && downTile != 2))
		{
			newDirection = DOWN;
		}
		else
		{
			newDirection = LEFT;
		}
		break;
	default:
		if ((!GetTileBombState(_posMap.y, _posMap.x - 1) && leftTile != 0 && leftTile != 2))
		{
			newDirection = LEFT;
		}
		else if ((!GetTileBombState(_posMap.y, _posMap.x + 1) && rightTile != 0 && rightTile != 2))
		{
			newDirection = RIGHT;
		}
		else if ((!GetTileBombState(_posMap.y - 1, _posMap.x) && upTile != 0 && upTile != 2))
		{
			newDirection = UP;
		}
		else if ((!GetTileBombState(_posMap.y + 1, _posMap.x) && downTile != 0 && downTile != 2))
		{
			newDirection = DOWN;
		}
		else
		{
			newDirection = LEFT;
		}
		break;
	}

	return newDirection;
}

sfVector2f BasicIA(enum Direction* _dir, sfVector2f _pos, sfVector2u _size, float _speed, int _name, float _dt)
{
	if (*_dir == DOWN)
	{
		sfVector2f tilePos = GetTilesPos(0, 0);
		sfVector2i playerPosMap;
		playerPosMap.x = (int)(_pos.x - tilePos.x) / 64;
		playerPosMap.y = (int)(_pos.y - tilePos.y - 9 / 2) / 64;

		int tile1;
		if (playerPosMap.y + 2 > LINE)
		{
			tile1 = 0;
		}
		else
		{
			tile1 = GetTilesType(playerPosMap.y + 1, playerPosMap.x);
		}

		if ((!GetTileBombState(playerPosMap.y + 1, playerPosMap.x) && tile1 != 0 && tile1 != 2) || (tile1 != 0 && _name == 4))
		{
			_pos = MoveDown(*_dir, _pos, (sfVector2u) { 0, 9 }, _speed, _name, _dt);
		}
		else
		{
			*_dir = ChangeDirection(playerPosMap);
		}
	}
	else if (*_dir == UP)
	{
		sfVector2f tilePos = GetTilesPos(0, 0);
		sfVector2i playerPosMap;
		playerPosMap.x = (int)(_pos.x - tilePos.x) / 64;
		playerPosMap.y = (int)(_pos.y - tilePos.y + 119 / 2) / 64;

		int tile1;
		if (playerPosMap.y - 1 < 0)
		{
			tile1 = 0;
		}
		else
		{
			tile1 = GetTilesType(playerPosMap.y - 1, playerPosMap.x);
		}

		if ((!GetTileBombState(playerPosMap.y - 2, playerPosMap.x) && tile1 != 0 && tile1 != 2) || (tile1 != 0 && _name == 4))
		{
			_pos = MoveUp(*_dir, _pos, (sfVector2u) { 0, 119 }, _speed, _name, _dt);
		}
		else
		{
			*_dir = ChangeDirection(playerPosMap);
		}
	}
	else if (*_dir == RIGHT)
	{
		sfVector2f tilePos = GetTilesPos(0, 0);
		sfVector2i playerPosMap;
		playerPosMap.x = (int)(_pos.x - tilePos.x - 32) / 64;
		playerPosMap.y = (int)(_pos.y - tilePos.y) / 64;

		int tile1;
		if (playerPosMap.x + 2 > COLUMN)
		{
			tile1 = 0;
		}
		else
		{
			tile1 = GetTilesType(playerPosMap.y, playerPosMap.x + 1);
		}

		if ((!GetTileBombState(playerPosMap.y, playerPosMap.x + 1) && tile1 != 0 && tile1 != 2) || (tile1 != 0 && _name == 4))
		{
			_pos = MoveRight(*_dir, _pos, (sfVector2u) { 64, 0 }, _speed, _name, _dt);
		}
		else
		{
			*_dir = ChangeDirection(playerPosMap);
		}
	}
	else if (*_dir == LEFT)
	{
		sfVector2f tilePos = GetTilesPos(0, 0);
		sfVector2i playerPosMap;
		playerPosMap.x = (int)(_pos.x - tilePos.x + 32) / 64;
		playerPosMap.y = (int)(_pos.y - tilePos.y) / 64;

		int tile1;
		if (playerPosMap.x - 1 < 0)
		{
			tile1 = 0;
		}
		else
		{
			tile1 = GetTilesType(playerPosMap.y, playerPosMap.x - 1);
		}

		if ((!GetTileBombState(playerPosMap.y, playerPosMap.x - 1) && tile1 != 0 && tile1 != 2) || (tile1 != 0 && _name == 4))
		{
			_pos = MoveLeft(*_dir, _pos, (sfVector2u) { 64, 0 }, _speed, _name, _dt);
		}
		else
		{
			*_dir = ChangeDirection(playerPosMap);
		}
	}

	return _pos;
}

sfVector2f MoveUp(enum Direction _dir, sfVector2f _pos, sfVector2u _size, float _speed, int _name, float _dt)
{
	sfVector2f tilePos = GetTilesPos(0, 0);
	sfVector2i playerPosMap;
	sfVector2f objectPos;
	playerPosMap.x = (int)(_pos.x - tilePos.x) / 64;
	playerPosMap.y = (int)(_pos.y - tilePos.y + _size.y / 2) / 64;
	objectPos.x = (_pos.x);
	objectPos.y = (_pos.y + _size.y / 2 - 64);

	int tile1;
	if (playerPosMap.y - 1 < 0)
	{
		tile1 = 0;
	}
	else
	{
		tile1 = GetTilesType(playerPosMap.y - 1, playerPosMap.x);
	}

	if (((int)_pos.x % 64) != 0)
	{
		switch (_dir)
		{
		case LEFT:
			_pos.x -= 1;

		case RIGHT:
			_pos.x += 1;

		case UP:
			if (checkCloseX(_pos))
			{
				_pos.x += 1;
			}
			else
			{
				_pos.x -= 1;
			}
		}
	}

	struct Bomb* bombList = GetBombs();

	if ((tile1 != 0 && tile1 != 2) || (tile1 != 0 && _name == 4))
	{
		for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
		{
			if ((bombList[i].isPlaced))
			{
				sfVector2f bombpos = bombList[i].pos;
				bombpos.y += 32;
				if (IsCollidingRectangleRectangle(objectPos, bombpos, (sfVector2u) { 32, 5 }, (sfVector2u) { 32, 5 }))
				{
					return _pos;
				}
			}
		}

		_pos.y -= _dt * _speed;
	}

	return _pos;
}

sfVector2f MoveDown(enum Direction _dir, sfVector2f _pos, sfVector2u _size, float _speed, int _name, float _dt)
{
	sfVector2f tilePos = GetTilesPos(0, 0);
	sfVector2f objectPos;
	sfVector2i objectPosMap;
	objectPosMap.x = (int)(_pos.x - tilePos.x) / 64;
	objectPosMap.y = (int)(_pos.y - tilePos.y - _size.y / 2) / 64;
	objectPos.x = (_pos.x);
	objectPos.y = (_pos.y - _size.y / 2 + 64);

	int tile1;
	if (objectPosMap.y + 2 > LINE)
	{
		tile1 = 0;
	}
	else
	{
		tile1 = GetTilesType(objectPosMap.y + 1, objectPosMap.x);
	}

	if (((int)_pos.x % 64) != 0)
	{
		switch (_dir)
		{
		case LEFT:
			_pos.x -= 1;

		case RIGHT:
			_pos.x += 1;

		case DOWN:
			if (checkCloseX(_pos))
			{
				_pos.x += 1;
			}
			else
			{
				_pos.x -= 1;
			}
		}
	}

	struct Bomb* bombList = GetBombs();

	if ((tile1 != 0 && tile1 != 2) || (tile1 != 0 && _name == 4))
	{
		for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
		{
			if ((bombList[i].isPlaced))
			{
				sfVector2f bombpos = bombList[i].pos;
				bombpos.y -= 10;
				if (IsCollidingRectangleRectangle(objectPos, bombpos, (sfVector2u) { 32, 5 }, (sfVector2u) { 32, 5 }))
				{
					return _pos;
				}
			}
		}

		_pos.y += _dt * _speed;
	}

	return _pos;
}

sfVector2f MoveLeft(enum Direction _dir, sfVector2f _pos, sfVector2u _size, float _speed, int _name, float _dt)
{
	sfVector2f tilePos = GetTilesPos(0, 0);
	sfVector2i playerPosMap;
	playerPosMap.x = (int)(_pos.x - tilePos.x + _size.x / 2) / 64;
	playerPosMap.y = (int)(_pos.y - tilePos.y) / 64;

	int tile1;
	if (playerPosMap.x - 1 < 0)
	{
		tile1 = 0;
	}
	else
	{
		tile1 = GetTilesType(playerPosMap.y, playerPosMap.x - 1);
	}

	if (((int)_pos.y % 64) != 0)
	{
		switch (_dir)
		{
		case DOWN:
			_pos.y -= 1;

		case UP:
			_pos.y += 1;

		case LEFT:
			if (checkCloseY(_pos))
			{
				_pos.y += 1;
			}
			else
			{
				_pos.y -= 1;
			}
		}
	}

	struct Bomb* bombList = GetBombs();

	if ((tile1 != 0 && tile1 != 2) || (tile1 != 0 && _name == 4))
	{
		for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
		{
			if ((bombList[i].isPlaced))
			{
				sfVector2f bombpos = bombList[i].pos;
				bombpos.x += 48;
				if (IsCollidingRectangleRectangle(_pos, bombpos, (sfVector2u) { 10, 32 }, (sfVector2u) { 10, 32 }))
				{
					return _pos;
				}
			}
		}
		_pos.x -= _dt * _speed;
	}

	return _pos;
}

sfVector2f MoveRight(enum Direction _dir, sfVector2f _pos, sfVector2u _size, float _speed, int _name, float _dt)
{
	sfVector2f tilePos = GetTilesPos(0, 0);
	sfVector2i playerPosMap;
	playerPosMap.x = (int)(_pos.x - tilePos.x - _size.x / 2) / 64;
	playerPosMap.y = (int)(_pos.y - tilePos.y) / 64;

	int tile1;
	if (playerPosMap.x + 2 > COLUMN)
	{
		tile1 = 0;
	}
	else
	{
		tile1 = GetTilesType(playerPosMap.y, playerPosMap.x + 1);
	}

	if (((int)_pos.y % 64) != 0)
	{
		switch (_dir)
		{
		case DOWN:
			_pos.y -= 1;

		case UP:
			_pos.y += 1;

		case RIGHT:
			if (checkCloseY(_pos))
			{
				_pos.y += 1;
			}
			else
			{
				_pos.y -= 1;
			}
		}
	}

	struct Bomb* bombList = GetBombs();

	if ((tile1 != 0 && tile1 != 2) || (tile1 != 0 && _name == 4))
	{
		for (unsigned char i = 0; i < MAX_BOMB_AMOUNT; i++)
		{
			if ((bombList[i].isPlaced))
			{
				sfVector2f bombpos = bombList[i].pos;
				bombpos.x -= 48;
				if (IsCollidingRectangleRectangle(_pos, bombpos, (sfVector2u) { 10, 32 }, (sfVector2u) { 10, 32 }))
				{
					return _pos;
				}
			}
		}
		_pos.x += _dt * _speed;
	}

	return _pos;
}