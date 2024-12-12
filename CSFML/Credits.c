#include "Credits.h"
#include "Game.h"

sfText* creditsText;

sfText* CreateText(sfText* _text, sfFont* _font, float _x, float _y, unsigned int _sizeFont, sfColor _color, char* string)
{
	_text = sfText_create();
	sfText_setFont(_text, _font);
	sfText_setCharacterSize(_text, _sizeFont);
	sfText_setColor(_text, _color);
	sfText_setString(_text, string);

	sfFloatRect textSize = sfText_getGlobalBounds(_text);
	sfText_setOrigin(_text, (sfVector2f) { textSize.width / 2, textSize.height / 2 });
	sfText_setPosition(_text, (sfVector2f) { _x, _y });
	return _text;
}

void LoadCredits()
{
	sfFont* font = sfFont_createFromFile("Assets/Font/BloodLust.ttf");
	creditsText = CreateText(creditsText, font, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 40, sfRed, "Programmeurs:\n\nEnzo BERTI\nLuc D'EURVEILHER\nCharles DE SOUZA\nNeyl MAHFOUF\nYohann MORITS\nAntoine RICHARD\n\nGraphistes:\n\nLorena ARNOUX\nLana GRATREAUD\nFabien RATHONIE");
}

void DrawCredits(sfRenderWindow* _window)
{
	sfRenderWindow_drawText(_window, creditsText, NULL);
}
