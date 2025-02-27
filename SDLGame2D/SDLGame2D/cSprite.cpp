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
	mAnimationFrames = 0;
	mAnimRectList = new SDL_Rect[mAnimationFrames];
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
	mAnimationFrames = 0;
	mAnimRectList = new SDL_Rect[mAnimationFrames];
}

void cSprite::DrawSprite(cGraphicsCore* graphCore, int frame)
{
	if (isVisible)
	{
		//Draw actual sprite if it is visible
		SDL_Rect tempRect = { (int)mPosition.x, (int)mPosition.y, (int)mScale.x, (int)mScale.y};
		
		if ((mAnimationFrames > 0) && (mAnimRectList != nullptr))
		//if there is animation frames, utilize the mAnimRectList for animation
		{
			SDL_RenderCopy(graphCore->getRenderer(), mTexture, &mAnimRectList[0], &tempRect);
		}
		else {
			//if there is no animation, provie NULL as source rectangle in the textue (= take full texture)
			SDL_RenderCopy(graphCore->getRenderer(), mTexture, NULL, &tempRect);
		}
		//Draw Direction-Vector
		SDL_SetRenderDrawColor(graphCore->getRenderer(), 255, 0, 0, 0);
		Vec2 dirVector = getVectorVectorSum(getVectorVectorSum(mPosition, getVectorScalarProduct(mScale,0.5f)), getVectorScalarProduct(mVelocity, 20.0f));
		graphCore->drawDebugLine(255, 0, 0, getCenter().x, getCenter().y, dirVector.x, dirVector.y);
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

void cSprite::SetPosX(float pos)
{
	mPosition.x = pos;
}

void cSprite::SetPosY(float pos)
{
	mPosition.y = pos;
}

Vec2 cSprite::getVelocity()
{
	return mVelocity;
}

Vec2 cSprite::getPosition()
{
	return mPosition;
}

Vec2 cSprite::getOldPosition()
{
	return mOldPosition;
}

Vec2 cSprite::getScale()
{
	return mScale;
}

Vec2 cSprite::getCenter()
{
	return {mPosition.x + (mScale.x * 0.5f), mPosition.y + (mScale.y * 0.5f)};
}

void cSprite::setIsColliding(bool state)
{
	isColliding = state;
}

bool cSprite::getIsColliding()
{
	return isColliding;
}

void cSprite::Move()
{
	//Store current position as old position
	mOldPosition = mPosition;
	//Position = Position + (Velocity * mNominalVel)
	mPosition = getVectorVectorSum(mPosition, getVectorScalarProduct(mVelocity, mNominalVel));
}

void cSprite::SetIsVisible(bool value)
{
	isVisible = value;
}

void cSprite::addAnimRect(SDL_Rect rect, int position)
{
	if (mAnimRectList != nullptr)
	{
		mAnimRectList[position] = rect;
	}
}

void cSprite::setAnimationFrames(int frameCount)
{
	mAnimationFrames = frameCount;
}

cSprite::~cSprite()
{
	//free resources
	//delete(mTexture);
}
