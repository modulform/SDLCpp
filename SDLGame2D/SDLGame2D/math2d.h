#pragma once

#include <math.h>

struct Vec2 {
	float x;
	float y;
};

float getVectorLength(Vec2 v);

Vec2 getVectorVectorSum(Vec2 v1, Vec2);
Vec2 getVectorScalarProduct(Vec2 v, float s);