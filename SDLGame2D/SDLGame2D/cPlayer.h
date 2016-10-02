#pragma once

#include "cSprite.h"

class cPlayer : public cSprite
{
public:
	cPlayer();
	cPlayer(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible);
	~cPlayer();
};

