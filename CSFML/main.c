#include "Game.h"

int main(void)
{
	GameData gameData = { 0 };

	srand(time(NULL));
	Load(&gameData);

	while (sfRenderWindow_isOpen(gameData.window))
	{
		PollEvent(&gameData);
		float dt = sfTime_asSeconds(sfClock_restart(gameData.clock));
		Update(&gameData, dt);
		Draw(&gameData);
	}

	return EXIT_SUCCESS;
}
