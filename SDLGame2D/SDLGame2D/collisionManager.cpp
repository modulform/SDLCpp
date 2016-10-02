#include "collisionManager.h"


bool doCollide(cSprite* sprite1, cSprite* sprite2)
{
	float left1 = sprite1->GetPosX();
	float right1 = left1 + sprite1->GetWidth();
	float top1 = sprite1->GetPosY();
	float bottom1 = top1 + sprite1->GetHeight();

	float left2 = sprite2->GetPosX();
	float right2 = left2 + sprite2->GetWidth();
	float top2 = sprite2->GetPosY();
	float bottom2 = top2 + sprite2->GetHeight();

	// Check edges
	if (left1 > right2)// Left 1 is right of right 2
		return false; // No collision

	if (right1 < left2) // Right 1 is left of left 2 
		return false; // No collision 

	if (top1 > bottom2) // Top 1 is below bottom 2
		return false; // No collision

	if (bottom1 < top2) // Bottom 1 is above top 2
		return false; // No collision 

	// None of the above test were true, collision! return true;

	return true;
}