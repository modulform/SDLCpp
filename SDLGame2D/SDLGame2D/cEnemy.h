#pragma once
#include "cSprite.h"
class cEnemy : public cSprite
{
public:
	cEnemy();
	cEnemy(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible);

	void Move();

	~cEnemy();
};