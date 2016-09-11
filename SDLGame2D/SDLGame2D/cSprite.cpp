#include "cSprite.h"

cSprite::cSprite(SDL_Texture* texture, float x, float y, int w, int h, float nominalVel)
{
	mTexture = texture;
	mPosX = x;
	mPosY = y;
	mVelX = 0;
	mVelY = 0;
	mWidth = w;
	mHeight = h;
	mNominalVel = nominalVel;
}

void cSprite::DrawSprite(SDL_Renderer* renderer)
{
	SDL_Rect tempRect = { (int)mPosX, (int)mPosY, (int)mWidth, (int)mHeight };
	SDL_RenderCopy(renderer, mTexture, NULL, &tempRect);
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

void cSprite::Move()
{
	mPosX = mPosX + (mVelX * mNominalVel);
	mPosY = mPosY + (mVelY * mNominalVel);
}

SDL_Rect cSprite::getBoundingBox() //updates and returns the sprites bounding box
{
	SDL_Rect temp;
	temp.x = mPosX;
	temp.y = mPosY;
	temp.w = mWidth;
	temp.h = mHeight;

	return temp;
}

cSprite::~cSprite()
{
}
