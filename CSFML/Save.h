#include"Libraries.h"
#include"SFML.h"
#include"Screen.h"
#include"GameState.h"

char textContent[50];
int score;

void SaveHiscore(int);
int GetHiscore(void);
void ReadHiscore(int* _score);