#include "collisionManager.h"


CollisionResult doCollideSpriteSprite(cSprite* sprite1, cSprite* sprite2)
{
	CollisionResult helper = { false, {0,0} };

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
			return { false,{ 0,0 } }; // No collision

		if (right1 < left2) // Right 1 is left of left 2 
			return { false,{ 0,0 } }; // No collision 

		if (top1 > bottom2) // Top 1 is below bottom 2
			return { false,{ 0,0 } }; // No collision

		if (bottom1 < top2) // Bottom 1 is above top 2
			return { false,{ 0,0 } }; // No collision 

		// None of the above test were true, collision!
		// Calculate the collision vector
		Vec2 vecHelper = getVectorVectorSum(sprite2->getCenter(), getVectorScalarProduct(sprite1->getCenter(), -1.0f));
		return {true, vecHelper};
	}
	return { false,{ 0,0 } };
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