#ifndef CREDITS_H
#define CREDITS_H

#include "Menu.h"

#include "Libraries.h"
#include "SFML.h"

sfText* CreateText(sfText* text, sfFont* font, float x, float y, unsigned int sizeFont, sfColor color, char* string);
void LoadCredits(void);
void DrawCredits(sfRenderWindow* window);

#endif