#include "collisionManager.h"


CollisionResult doCollideSpriteSprite(cSprite* sprite1, cSprite* sprite2)
{
	CollisionResult helper = { false, none, {0,0} };

	if (sprite1 != sprite2)
	{
		//Calculate Sprite1 bounding-box
		float left1 = sprite1->getPosition().x;
		float right1 = left1 + sprite1->getScale().x;
		float top1 = sprite1->getPosition().y;
		float bottom1 = top1 + sprite1->getScale().y;

		//Calculate Sprite1 bounding-box of old position (one frame back)
		float oldLeft1 = sprite1->getOldPosition().x;
		float oldRight1 = oldLeft1 + sprite1->getScale().x;
		float oldTop1 = sprite1->getOldPosition().y;
		float oldBottom1 = oldTop1 + sprite1->getScale().y;

		//Calculate Sprite2 bounding-box
		float left2 = sprite2->getPosition().x;
		float right2 = left2 + sprite2->getScale().x;
		float top2 = sprite2->getPosition().y;
		float bottom2 = top2 + sprite2->getScale().y;

		//AABB collision detection
		if ((left1 < right2) && (right1 > left2) && (top1 < bottom2) && (bottom1 > top2))
		{
			//collision detected
			helper.isColliding = true;
			sprite1->setIsColliding(true);
			//check which part of the collision was not true one frame back.
			//This is the one causing the collsion -> collision direction
			if ((oldRight1 < left2) && (right1 >= left2))
			{
				helper.colDirection = fromLeft;
			}
			else if ((oldLeft1 > right2) && (left1 < right2))
			{
				helper.colDirection = fromRight;
			}
			else if ((oldBottom1 < top2) && (bottom1 >= top2))
			{
				helper.colDirection = fromTop;
			}
			else if ((oldTop1 >= bottom2) && (top1 < bottom2))
			{
				helper.colDirection = fromBottom;
			}
		}
		else
		{
			//no collision detected
			sprite1->setIsColliding(false);
		}

		//return the collisionResult
		return helper;
	}
	return { false, none, { 0,0 } };
}

bool doCollideSpriteGroup(cSprite* sprite, std::list<cSprite*> group)
{
	bool helper = false;

	for (std::list<cSprite*>::iterator it = group.begin(); it != group.end(); it++)
	{
		if (doCollideSpriteSprite(sprite, (*it)).isColliding == true)
		{
			helper = true;
		}
	}

	return helper;
}

cSprite* getNearestSprite(cSprite* sprite1, std::list<cSprite*> spriteList)
{
	struct helperDistance {
		cSprite* sprite = nullptr;
		float distance = 100000.0f;
	};

	helperDistance helper;

	if (!spriteList.empty())
	{
		for (std::list<cSprite*>::iterator it = spriteList.begin(); it != spriteList.end(); it++)
		{
			if ((*it) != sprite1)
			{
				float tempDistance = getVectorLength(getVectorVectorDiff(sprite1->getPosition(), (*it)->getPosition()));
				if (tempDistance <= helper.distance)
				{
					helper.sprite = (*it);
					helper.distance = tempDistance;
				}
			}
		}
		return helper.sprite;
	}
	else
	{
		logToConsole("ERR - getNearestSprite(...)","Empty sprite list.");
		return nullptr;
	}
}