
#include "math2d.h"

float getVectorLength(Vec2 v)
{
	return sqrtf((v.x * v.x) + (v.y * v.y));
}

Vec2 getVectorVectorSum(Vec2 v1, Vec2 v2)
{
	Vec2 helper = { v1.x + v2.x, v1.y + v2.y };
	return helper;
}

Vec2 getVectorVectorDiff(Vec2 v1, Vec2 v2)
{
	Vec2 helper = { v1.x - v2.x, v1.y - v2.y };
	return helper;
}

Vec2 getVectorScalarProduct(Vec2 v, float s)
{
	Vec2 helper = { v.x * s, v.y * s };
	return helper;
}