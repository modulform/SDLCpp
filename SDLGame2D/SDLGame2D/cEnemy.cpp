#include "cEnemy.h"



cEnemy::cEnemy() : cSprite()	//default constructor calls base class constructor
{
	mType = SPRITETYPE_ENEMY;		//identify sprite as enemy-sprite
}

cEnemy::cEnemy(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible) : cSprite(texture, x, y, w, h, nominalVel, visible)
{
	mType = SPRITETYPE_ENEMY;		//identify sprite as enemy-sprite
	mVelX = 1.0f;
	mVelY = 1.0f;
}

void cEnemy::Move()
{
	//handle collision with screen boundaries
	if ((mPosX <= 0.0f) || ((mPosX + mWidth) >= SCREEN_WIDTH))	//if out of x-axis boundaries...
	{
		mVelX = mVelX * (-1.0f);	//change direction
	}

	if ((mPosY <= 0.0f) || ((mPosY + mHeight) >= SCREEN_HEIGHT)) //if out of y-boundaries...
	{
		mVelY = mVelY * (-1.0f);
	}

	mPosX = mPosX + (mVelX * mNominalVel);
	mPosY = mPosY + (mVelY * mNominalVel);
}

cEnemy::~cEnemy()
{
}
