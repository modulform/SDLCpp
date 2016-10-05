#include "cUIObject.h"



cUIObject::cUIObject()
{
	mFont = TTF_OpenFont("fonts\\font.ttf", 16);
	mColor = { 255,255,255 };
}

cUIObject::cUIObject(int id, float x, float y) : cUIObject()
{
	mId = id;
	mX = x;
	mY = y;
}

float cUIObject::getXPos()
{
	return mX;
}

float cUIObject::getYPos()
{
	return mY;
}

void cUIObject::RenderObject(SDL_Renderer* renderer)
{
	//virtual render method. Actual contents are implemented in child classes
}

cUIObject::~cUIObject()
{
}
