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
	//limit moving speed
	if (mVelocity.x > 1.5f)
	{
		mVelocity.x = 1.5f;
	}

	if (mVelocity.x < -1.5f)
	{
		mVelocity.x = -1.5f;
	}

	//first move the player...
	if (!mIsOnGround)
	{
		mVelocity.y = mVelocity.y + 0.003F;					//reduce yVelocity by a fixed value (gravity simulation for now)
	}
	else
	{
		mVelocity.y = 0.0f;
	}
	
	if (mVelocity.x > 0.0f)
	{
		if (mIsOnGround == true)
		{
			mVelocity.x = mVelocity.x - 0.002F;
		}
		else
		{
			mVelocity.x = mVelocity.x - 0.001F;
		}
	}
	if (mVelocity.x < 0.0f)
	{
		if (mIsOnGround == true)
		{
			mVelocity.x = mVelocity.x + 0.002F;
		}
		else
		{
			mVelocity.x = mVelocity.x + 0.001F;
		}
	}
	if (abs(mVelocity.x) < 0.0001)
	{
		mVelocity.x = 0.0f;
	}

	//Position = Position + (Velocity * mNominalVel)
	mPosition = getVectorVectorSum(mPosition, getVectorScalarProduct(mVelocity, mNominalVel));
	
	//...then check if the player is outside screen boundaries and set back inside the boundaries
	if (mPosition.x < 0.0f)
	{
		mPosition.x = 0.0f;
	}
	else if ((mPosition.x + mScale.x) > SCREEN_WIDTH)
	{
		mPosition.x = SCREEN_WIDTH - mScale.x;
	}

	if (mPosition.y < 0.0f)
	{
		mPosition.y = 0.0f;
		mIsOnGround = false;
	}
	else if ((mPosition.y + mScale.y) > SCREEN_HEIGHT)
	{
		mPosition.y = SCREEN_HEIGHT - mScale.y;
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
