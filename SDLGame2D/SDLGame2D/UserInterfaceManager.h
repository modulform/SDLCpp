#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <list>
#include "globals.h"

class UserInterfaceManager
{
public:
	UserInterfaceManager(SDL_Renderer* renderer);

	void RenderObjects(SDL_Renderer* renderer);
	void addTextObject(std::string text, float positionX, float positionY);

	~UserInterfaceManager();

private:
	int iIdCounter;
	SDL_Renderer* mRenderer;
	std::list<textObject> objectList;
	TTF_Font* font;
	SDL_Color displayColor;
};