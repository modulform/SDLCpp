#pragma once

#include "cUIObject.h"

class cFloatUIObject : public cUIObject
{
public:
	cFloatUIObject();
	cFloatUIObject(int id, float x, float y, float* value);
	void RenderObject(SDL_Renderer* renderer);
	~cFloatUIObject();

private:
	float* mValue;
};

