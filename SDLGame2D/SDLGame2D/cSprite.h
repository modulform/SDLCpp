#pragma once

#include <SDL/SDL.h>
#include "globals.h"

class cSprite
{

public:
	cSprite::cSprite();
	cSprite(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible);
	~cSprite();

	void DrawSprite(SDL_Renderer* renderer);	//render the sprite to the given renderer
	void SetVelX(float vel);					//set velocity in x-direction
	void SetVelY(float vel);					//set velocity in y-direction
	float GetVelX();							//get current velocity in x-direction
	float GetVelY();							//get current velocity in y-direction
	float GetPosX();							//get current position on x-axis
	float GetPosY();							//get current position on y-axis
	float GetWidth();							//get current width
	float GetHeight();							//get current height
	virtual void Move();								//add the current velocity vector to the position vector
	void SetIsVisible(bool value);				//sets the visiblity property
protected:
	int mType;				//Sprite type (see definition in Notes.txt)
	SDL_Texture* mTexture;	//Sprite texture
	float mPosX;			//x-position
	float mPosY;			//y-position
	float mVelX;			//velocity in x-direction
	float mVelY;			//velocity in y-direction
	float mWidth;				//sprite width
	float mHeight;			//sprite height
	float mNominalVel;		//nominal velocity value
	bool isVisible;			//indicates if the sprite shall be rendered
};

