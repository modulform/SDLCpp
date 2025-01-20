#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class cUIObject
{
public:
	cUIObject();

	cUIObject(int id, float x, float y);
	float getXPos();
	float getYPos();
	virtual void RenderObject(SDL_Renderer* renderer);

	~cUIObject();

protected:
	TTF_Font* mFont;
	SDL_Color mColor;
	float mX;
	float mY;

private:
	int mId;
};

