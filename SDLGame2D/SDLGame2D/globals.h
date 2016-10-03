#pragma once

#include <string>

#define WINDOW_TITLE "2d Simple Game (m.i.n.d.f.l.y 2016)"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

#define SPRITETYPE_DEFAULT 0
#define SPRITETYPE_PLAYER 1
#define SPRITETYPE_ENEMY 2
#define SPRITETYPE_BLOCK 3

typedef struct
{
	int id;
	std::string text;
	float x;
	float y;

} textObject;