#include "cSprite.h"

cSprite::cSprite()
{
	mType = SPRITETYPE_DEFAULT;
	mTexture = nullptr;
	mPosition = { 0.0f, 0.0f };
	mVelocity = { 0.0f, 0.0f };
	mScale = { 0.0f, 0.0f };
	mNominalVel = 0.0f;
	isVisible = true;
}

cSprite::cSprite(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible)
{
	mType = SPRITETYPE_DEFAULT;
	mTexture = texture;
	mPosition = { x, y };
	mVelocity = { 0.0f, 0.0f };
	mScale = { w,h };
	mNominalVel = nominalVel;
	isVisible = visible;
}

void cSprite::DrawSprite(cGraphicsCore* graphCore)
{
	if (isVisible)
	{
		SDL_Rect tempRect = { (int)mPosition.x, (int)mPosition.y, (int)mScale.x, (int)mScale.y };
		SDL_RenderCopy(graphCore->getRenderer(), mTexture, NULL, &tempRect);
		//Draw Direction-Vector
		SDL_SetRenderDrawColor(graphCore->getRenderer(), 255, 0, 0, 0);
		Vec2 dirVector = getVectorVectorSum(getVectorVectorSum(mPosition, getVectorScalarProduct(mScale,0.5f)), getVectorScalarProduct(mVelocity, 20.0f));
		graphCore->drawDebugLine(getCenter().x, getCenter().y, dirVector.x, dirVector.y);
	}
}

void cSprite::incVelX(float increment)
{
	mVelocity.x = mVelocity.x + increment;
}

void cSprite::incVelY(float increment)
{
	mVelocity.y = mVelocity.y + increment;
}

void cSprite::SetVelX(float vel)
{
	mVelocity.x = vel;
}

void cSprite::SetVelY(float vel)
{
	mVelocity.y = vel;
}

Vec2 cSprite::getVelocity()
{
	return mVelocity;
}

Vec2 cSprite::getPosition()
{
	return mPosition;
}

Vec2 cSprite::getScale()
{
	return mScale;
}

Vec2 cSprite::getCenter()
{
	return {mPosition.x + (mScale.x * 0.5f), mPosition.y + (mScale.y * 0.5f)};
}

void cSprite::Move()
{
	//Position = Position + (Velocity * mNominalVel)
	mPosition = getVectorVectorSum(mPosition, getVectorScalarProduct(mVelocity, mNominalVel));
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
