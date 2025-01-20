#pragma once

#include <SDL.h>
#include "globals.h"
#include "math2d.h"
#include "cGraphicsCore.h"

class cSprite
{

public:
	cSprite::cSprite();
	cSprite(SDL_Texture* texture, float x, float y, float w, float h, float nominalVel, bool visible);
	~cSprite();

	void DrawSprite(cGraphicsCore* graphCore, int frame);		//render the sprite to the given renderer
	void incVelX(float increment);					//increase x-velocity by increment
	void incVelY(float increment);					//increase y-velocity by increment
	void SetVelX(float vel);						//set velocity in x-direction
	void SetVelY(float vel);						//set velocity in y-direction
	void SetPosX(float pos);						//set position on x
	void SetPosY(float pos);						//set position on y
	Vec2 getVelocity();								//get current velocity
	Vec2 getPosition();								//get current position
	Vec2 getOldPosition();							//get old position
	Vec2 getScale();								//get current scale (width | height)
	Vec2 getCenter();								//get the center point of the sprite
	bool getIsColliding();							//get information if the sprite is colliding with something
	void setIsColliding(bool state);				//set isColliding property
	virtual void Move();							//add the current velocity vector to the position vector
	void SetIsVisible(bool value);					//sets the visiblity property
	void addAnimRect(SDL_Rect rect, int position);	//adds a given SDL_Rect to the list of animation clip rectangles
	void setAnimationFrames(int frameCount);
protected:
	int mType;					//Sprite type (see definition in Notes.txt)
	SDL_Texture* mTexture;		//Sprite texture
	Vec2 mPosition;				//Sprite Position
	Vec2 mOldPosition;			//Sprite old position (used for detecting collision direction)
	Vec2 mVelocity;				//Sprite Velocity
	Vec2 mScale;				//Sprite Scale (x = width, y = height)
	float mNominalVel;			//nominal velocity value
	bool isVisible;				//indicates if the sprite shall be rendered
	bool isColliding;			//inidcates if the sprite currently collides with 
	int mAnimationFrames;		//Count of animation frames the sprite supports
	SDL_Rect* mAnimRectList;	//Container for the animation clip rectangles selecting the frames in the texture map
};

