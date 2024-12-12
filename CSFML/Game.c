#include "Game.h"

void LoadWindow(GameData* _gameData)
{
	sfVideoMode mode = { SCREEN_WIDTH, SCREEN_HEIGHT, 32 };
	_gameData->window = sfRenderWindow_create(mode, "Bomber Blaze", sfFullscreen, NULL);
	_gameData->clock = sfClock_create();
	sfRenderWindow_setFramerateLimit(_gameData->window, 60);
}

void Load(GameData* _gameData)
{
	LoadWindow(_gameData);
	LoadMap();
	LoadEnemies();
	LoadPlayer();
	LoadBomb();
	LoadItem();
	LoadMenu();
	LoadCredits();
	LoadPause();
	LoadHUD();
	LoadGameOver();
	LoadSound();
}

void PollEvent(GameData* _gameData)
{
	while (sfRenderWindow_pollEvent(_gameData->window, &_gameData->event))
	{
		switch (_gameData->event.type)
		{
		case sfEvtClosed:
			if (*GetPlayerScore() > GetHiscore())
			{
				SaveHiscore(*GetPlayerScore());
			}
			sfRenderWindow_close(_gameData->window);
			break;

		case sfEvtMouseButtonPressed:
			break;

		case sfEvtKeyPressed:
			if (_gameData->event.key.code == sfKeyEscape)
			{
				switch (GetGameState())
				{
				case GAME:
					SetGameState(PAUSE);
					break;

				case CREDITS:
					SetGameState(MENU);
					break;

				case PAUSE:
					if (*GetPlayerScore() > GetHiscore())
					{
						SaveHiscore(*GetPlayerScore());
					}

					sfMusic_stop(Main);
					sfMusic_play(Menu);
					SetGameState(MENU);
					break;

				case GAME_OVER:
					SetGameState(MENU);
					sfMusic_stop(Over);
					sfMusic_play(Menu);
					break;
				}
			}

			if (_gameData->event.key.code == sfKeyReturn)
			{
				switch (GetGameState())
				{
				case PAUSE:
					SetGameState(GAME);
					break;
				case GAME_OVER:
					SetGameState(GAME);
					CreateMap();
					ResetPlayer();
					ResetLevel();
					ResetScore();
					ResetItem();
					ResetBomb();
					CreateEnemiesRoom(GetPlayerLevel());
					PlayHUDLevel();
					timer = 0;
					sfMusic_stop(Over);
					sfMusic_play(Main);
					break;
				}
			}

			if ((_gameData->event.key.code == sfKeySpace) && (GetBombAmount() > 0))
			{
				PlaceBomb();
				break;
			}
		case sfEvtMouseWheelMoved:
			break;
		case sfEvtMouseMoved:
			break;
		}
	}
}

void Update(GameData* _gameData, float _dt)
{
	switch (GetGameState())
	{
	case GAME:
		UpdatePlayer(_dt);
		UpdateEnemies(_dt);
		UpdateMap();
		UpdateBomb(_dt);
		UpdateItem(_dt);
		CapStats();
		UpdateHUD(_dt);
		break;

	case MENU:
		UpdateMenu(_dt, _gameData->window);
		break;

	default:
		break;
	}
}

void Draw(const GameData* _gameData)
{
	sfRenderWindow_clear(_gameData->window, sfBlack);

	switch (GetGameState())
	{
	case GAME:
		// les items sont draw dans DrawMap()
		DrawMap(_gameData->window);
		DrawBomb(_gameData->window);
		DrawBackgroundMap(_gameData->window);
		DrawEnemies(_gameData->window);
		DrawPlayer(_gameData->window);
		DrawHUD(_gameData->window);
		break;

	case MENU:
		DrawMenu(_gameData->window);
		break;

	case CREDITS:
		DrawCredits(_gameData->window);
		break;

	case PAUSE:
		DrawMap(_gameData->window);
		DrawBomb(_gameData->window);
		DrawBackgroundMap(_gameData->window);
		DrawEnemies(_gameData->window);
		DrawPlayer(_gameData->window);
		DrawHUD(_gameData->window);

		DrawPause(_gameData->window);
		break;

	case GAME_OVER:
		DrawGameOver(_gameData->window);
		break;

	default:
		break;
	}

	sfRenderWindow_display(_gameData->window);
}