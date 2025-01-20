#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <list>
#include "globals.h"
#include "cUIObject.h"
#include "cTextUIObject.h"
#include "cFloatUIObject.h"

class UserInterfaceManager
{
public:
	UserInterfaceManager(SDL_Renderer* renderer);

	void RenderObjects(SDL_Renderer* renderer);
	void addObject(std::string text, float positionX, float positionY);
	void addObject(float* value, float positionX, float positionY);

	~UserInterfaceManager();

private:
	int iIdCounter;
	SDL_Renderer* mRenderer;
	std::list<cUIObject*> objectList;
};