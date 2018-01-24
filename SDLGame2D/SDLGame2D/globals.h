#pragma once

#include <string>
#include "math2d.h"

#define WINDOW_TITLE "2d Simple Game (m.i.n.d.f.l.y 2016)"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 576

#define FPS_INTERVAL 1.0

#define SPRITETYPE_DEFAULT 0
#define SPRITETYPE_PLAYER 1
#define SPRITETYPE_ENEMY 2
#define SPRITETYPE_BLOCK 3

enum direction { none, fromTop, fromBottom, fromRight, fromLeft };

struct AABB
{
	Vec2 min;
	Vec2 max;
};

struct CollisionResult
{
	bool isColliding;
	direction colDirection;
	Vec2 colVector;
};