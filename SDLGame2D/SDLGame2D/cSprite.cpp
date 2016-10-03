#include "cSprite.h"

cSprite::cSprite()
{
	mType = SPRITETYPE_DEFAULT;
	mTexture = nullptr;
	mPosX = 0.0f;
	mPosY = 0.0f;
	mVelX = 0.0f;
	mVelY = 0.0f;
	mWidth = 0.0f;
	mHeight = 0.0f;
	mNominalVel = 0.0f;
	isVisible = true;
}

cSprite::cSprite(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible)
{
	mType = SPRITETYPE_DEFAULT;
	mTexture = texture;
	mPosX = x;
	mPosY = y;
	mVelX = 0.0f;
	mVelY = 0.0f;
	mWidth = w;
	mHeight = h;
	mNominalVel = nominalVel;
	isVisible = visible;
}

void cSprite::DrawSprite(SDL_Renderer* renderer)
{
	if (isVisible)
	{
		SDL_Rect tempRect = { (int)mPosX, (int)mPosY, (int)mWidth, (int)mHeight };
		SDL_RenderCopy(renderer, mTexture, NULL, &tempRect);
	}
}

void cSprite::SetVelX(float vel)
{
	mVelX = vel;
}

void cSprite::SetVelY(float vel)
{
	mVelY = vel;
}

float cSprite::GetVelX()
{
	return mVelX;
}

float cSprite::GetVelY()
{
	return mVelY;
}

float cSprite::GetPosX()
{
	return mPosX;
}

float cSprite::GetPosY()
{
	return mPosY;
}

float cSprite::GetHeight()
{
	return mHeight;
}

float cSprite::GetWidth()
{
	return mWidth;
}

void cSprite::Move()
{
	mPosX = mPosX + (mVelX * mNominalVel);
	mPosY = mPosY + (mVelY * mNominalVel);
}

void cSprite::SetIsVisible(bool value)
{
	isVisible = value;
}

cSprite::~cSprite()
{
	//free resources
	//delete(mTexture);
}
