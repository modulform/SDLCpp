#include "UserInterfaceManager.h"



UserInterfaceManager::UserInterfaceManager(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	iIdCounter = 0;			//initialize ID counter that provides session-unique IDs
	font = TTF_OpenFont("fonts\\font.ttf", 60);
	displayColor = { 255,255,255 };
}

void UserInterfaceManager::RenderObjects(SDL_Renderer* renderer)
{
	for (std::list<textObject>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, it->text.c_str(), displayColor);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect tempRect;
		tempRect.x = it->x;
		tempRect.y = it->y;
		tempRect.w = 100;
		tempRect.h = 12;
		SDL_RenderCopy(renderer, texture, NULL, &tempRect);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
}

void UserInterfaceManager::addTextObject(std::string text, float positionX, float positionY)
{
	textObject helper;

	iIdCounter++;
	helper.id = iIdCounter;
	helper.text = text;
	helper.x = positionX;
	helper.y = positionY;

	objectList.push_back(helper);
}

UserInterfaceManager::~UserInterfaceManager()
{
}
