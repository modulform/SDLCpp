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

void cPlayer::Move()
{
	//first move the player...
	mPosX = mPosX + (mVelX * mNominalVel);
	mPosY = mPosY + (mVelY * mNominalVel);

	//...then check if the player is outside screen boundaries and set back inside the boundaries
	if (mPosX < 0.0f)
	{
		mPosX = 0.0f;
	}
	else if ((mPosX + mWidth) > SCREEN_WIDTH)
	{
		mPosX = SCREEN_WIDTH - mWidth;
	}

	if (mPosY < 0.0f)
	{
		mPosY = 0.0f;
	}
	else if ((mPosY + mHeight) > SCREEN_HEIGHT)
	{
		mPosY = SCREEN_HEIGHT - mHeight;
	}
}

cPlayer::~cPlayer()
{
}
