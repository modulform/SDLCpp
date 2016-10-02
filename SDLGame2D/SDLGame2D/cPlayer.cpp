#include "cPlayer.h"

cPlayer::cPlayer() : cSprite()		//default constructor calls base class constructor
{
	mType = SPRITETYPE_PLAYER;		//identify sprite as player
}

cPlayer::cPlayer(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible) : cSprite(texture, x, y, w, h, nominalVel, visible)
{
	//non-default constructor calls base class constructor
	mType = SPRITETYPE_PLAYER;
}

cPlayer::~cPlayer()
{
}
