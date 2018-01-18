#include "cPlayer.h"

cPlayer::cPlayer() : cSprite()		//default constructor calls base class constructor
{
	mType = SPRITETYPE_PLAYER;		//identify sprite as player
	mIsOnGround = false;
}

cPlayer::cPlayer(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible) : cSprite(texture, x, y, w, h, nominalVel, visible)
{
	//non-default constructor calls base class constructor
	mType = SPRITETYPE_PLAYER;
	mIsOnGround = false;
}

void cPlayer::Move()
{
	//first move the player...
	mVelY = mVelY + 0.003F;					//reduce yVelocity by a fixed value (gravity simulation for now)
	if (mVelX > 0.0f)
	{
		if (mIsOnGround == true)
		{
			mVelX = mVelX - 0.002F;
		}
	}
	if (mVelX < 0.0f)
	{
		if (mIsOnGround == true)
		{
			mVelX = mVelX + 0.002F;
		}
	}
	if (abs(mVelX) < 0.0001)
	{
		mVelX = 0.0f;
	}

	mPosX = mPosX + (mVelX * mNominalVel);
	mPosY = mPosY + (mVelY * mNominalVel);


	//...then check if the player is outside screen boundaries and set back inside the boundaries
	if (mPosX < 0.0f)
	{
		mPosX = 0.0f;
		if (!mIsOnGround)
		{
			mVelX = -mVelX;
		}
	}
	else if ((mPosX + mWidth) > SCREEN_WIDTH)
	{
		mPosX = SCREEN_WIDTH - mWidth;
		if (!mIsOnGround)
		{
			mVelX = -mVelX;
		}
	}

	if (mPosY < 0.0f)
	{
		mPosY = 0.0f;
		mIsOnGround = false;
	}
	else if ((mPosY + mHeight) > SCREEN_HEIGHT)
	{
		mPosY = SCREEN_HEIGHT - mHeight;
		mIsOnGround = true;
	}
	else
	{
		mIsOnGround = false;
	}
}

cPlayer::~cPlayer()
{
}
