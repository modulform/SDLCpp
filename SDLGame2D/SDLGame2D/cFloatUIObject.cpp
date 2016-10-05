#include "cFloatUIObject.h"



cFloatUIObject::cFloatUIObject() : cUIObject()
{
}

cFloatUIObject::cFloatUIObject(int id, float x, float y, float* value) : cUIObject(id, x, y)
{
	mValue = value;
}

void cFloatUIObject::RenderObject(SDL_Renderer* renderer)
{
	std::string valueText = std::to_string(*mValue);

	SDL_Surface* surface = TTF_RenderText_Solid(mFont, valueText.c_str(), mColor);
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

cFloatUIObject::~cFloatUIObject()
{
}
