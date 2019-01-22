#pragma once

#include <math.h>

struct Vec2 {
	float x;
	float y;
};

float getVectorLength(Vec2 v);

///<summary>Calculates v1 + v2 component-based</summary>
Vec2 getVectorVectorSum(Vec2 v1, Vec2 v2);

///<summary>Calculates v1 - v2 component-based</summary>
Vec2 getVectorVectorDiff(Vec2 v1, Vec2 v2);

///<summary>Calculates v1 * s component-based</summary>
Vec2 getVectorScalarProduct(Vec2 v, float s);

///<summar>Calculates the normalized vector from v</summary>
Vec2 getNormalizedVector(Vec2 v);