#include "cSprite.h"



cSprite::cSprite(SDL_Texture* texture, float x, float y, int w, int h)
{
	mTexture = texture;
	mPosX = x;
	mPosY = y;
	mWidth = w;
	mHeight = h;
}

void cSprite::DrawSprite(SDL_Renderer* renderer)
{
	SDL_Rect tempRect = { mPosX, mPosY, mWidth, mHeight };
	SDL_RenderCopy(renderer, mTexture, NULL, &tempRect);
}

cSprite::~cSprite()
{
}
