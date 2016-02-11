#pragma once

#include <SDL/SDL.h>

class cSprite
{

public:
	cSprite(SDL_Texture* texture, float x, float y, int w, int h);
	~cSprite();

	void DrawSprite(SDL_Renderer* renderer);
private:
	SDL_Texture* mTexture;
	float mPosX;
	float mPosY;
	int mWidth;
	int mHeight;

};

