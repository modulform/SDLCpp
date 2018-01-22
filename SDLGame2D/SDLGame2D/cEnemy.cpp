#include "cEnemy.h"



cEnemy::cEnemy() : cSprite()	//default constructor calls base class constructor
{
	mType = SPRITETYPE_ENEMY;		//identify sprite as enemy-sprite
}

cEnemy::cEnemy(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible) : cSprite(texture, x, y, w, h, nominalVel, visible)
{
	mType = SPRITETYPE_ENEMY;		//identify sprite as enemy-sprite
	mVelocity.x = 1.0f;
	mVelocity.y = 1.0f;
}

void cEnemy::Move()
{
	//handle collision with screen boundaries
	if ((mPosition.x <= 0.0f) || ((mPosition.x + mScale.x) >= SCREEN_WIDTH))	//if out of x-axis boundaries...
	{
		mVelocity.x = mVelocity.x * (-1.0f);	//change direction
	}

	if ((mPosition.y <= 0.0f) || ((mPosition.y + mScale.y) >= SCREEN_HEIGHT)) //if out of y-boundaries...
	{
		mVelocity.y = mVelocity.y * (-1.0f);
	}

	//Position = Position + (Velocity + mNominalVel)
	mPosition = getVectorVectorSum(mPosition, getVectorScalarProduct(mVelocity, mNominalVel));
}

cEnemy::~cEnemy()
{
}
