#include "cTextUIObject.h"



cTextUIObject::cTextUIObject() : cUIObject()
{
}

cTextUIObject::cTextUIObject(int id, float x, float y, std::string text) : cUIObject(id, x, y)
{
	//handle base class elements by calling base class constructor
	mText = text;		//set member mText to constructor paramenter
}

void cTextUIObject::RenderObject(SDL_Renderer* renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(mFont, mText.c_str(), mColor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect tempRect;
	tempRect.x = (int)mX;
	tempRect.y = (int)mY;
	tempRect.w = surface->w;
	tempRect.h = surface->h;
	SDL_RenderCopy(renderer, texture, NULL, &tempRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

cTextUIObject::~cTextUIObject()
{
}
