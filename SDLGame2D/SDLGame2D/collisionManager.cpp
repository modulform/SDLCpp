#include "collisionManager.h"


CollisionResult doCollideSpriteSprite(cSprite* sprite1, cSprite* sprite2)
{
	CollisionResult helper = { false, none, {0,0} };

	if (sprite1 != sprite2)
	{
		
		float left1 = sprite1->getPosition().x;
		float right1 = left1 + sprite1->getScale().x;
		float top1 = sprite1->getPosition().y;
		float bottom1 = top1 + sprite1->getScale().y;

		float left2 = sprite2->getPosition().x;
		float right2 = left2 + sprite2->getScale().x;
		float top2 = sprite2->getPosition().y;
		float bottom2 = top2 + sprite2->getScale().y;

		// Check edges
		if (left1 > right2)// Left 1 is right of right 2
			return helper; // No collision

		if (right1 < left2) // Right 1 is left of left 2 
			return helper; // No collision 

		if (top1 > bottom2) // Top 1 is below bottom 2
			return helper; // No collision

		if (bottom1 < top2) // Bottom 1 is above top 2
			return helper; // No collision 

		// None of the above test were true, collision!
		helper.isColliding = true;
		// Calculate the collision vector
		helper.colVector = getVectorVectorDiff(sprite1->getCenter(), sprite2->getCenter());
		// Determine collision direction
		
		if ((bottom1 >= top2) && (top1 < top2) && (right1 > left2) && (left1 < right2))
		{
			helper.colDirection = fromTop;
		}
		else if ((top1 <= bottom2) && (bottom1 > bottom2) && (right1 > left2) && (left1 < right2))
		{
			helper.colDirection = fromBottom;
		}
		if ((right1 >= left2) && (left1 < left2) && (bottom1 > top2) && (top1 < bottom2))
		{
			helper.colDirection = fromLeft;
		}
		else if ((left1 <= right2) && (right1 > right2) && (bottom1 > top2) && (top1 < bottom2))
		{
			helper.colDirection = fromRight;
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