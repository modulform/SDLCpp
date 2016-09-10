#pragma once

#include <SDL.h>

class cSprite
{

public:
	cSprite(SDL_Texture* texture, float x, float y, int w, int h, float nominalVel);
	~cSprite();

	void DrawSprite(SDL_Renderer* renderer);	//render the sprite to the given renderer
	void SetVelX(float vel);					//set velocity in x-direction
	void SetVelY(float vel);					//set velocity in y-direction
	float GetVelX();							//get current velocity in x-direction
	float GetVelY();							//get current velocity in y-direction
	void Move();								//add the current velocity vector to the position vector
private:
	SDL_Texture* mTexture;	//Sprite texture
	float mPosX;			//x-position
	float mPosY;			//y-position
	float mVelX;			//velocity in x-direction
	float mVelY;			//velocity in y-direction
	int mWidth;				//sprite width
	int mHeight;			//sprite height
	float mNominalVel;		//nominal velocity value
};

