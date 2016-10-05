#include "UserInterfaceManager.h"

UserInterfaceManager::UserInterfaceManager(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	iIdCounter = 0;			//initialize ID counter that provides session-unique IDs
}

void UserInterfaceManager::RenderObjects(SDL_Renderer* renderer)
{
	for (std::list<cUIObject*>::iterator it = objectList.begin(); it != objectList.end(); it++)
	{
		(*it)->RenderObject(renderer);
	}
}

void UserInterfaceManager::addObject(std::string text, float positionX, float positionY)
{
	iIdCounter++;
	cTextUIObject* temp = new cTextUIObject(iIdCounter, positionX, positionY, text);

	objectList.push_back(temp);
}

void UserInterfaceManager::addObject(float* value, float positionX, float positionY)
{
	iIdCounter++;
	cFloatUIObject* temp = new cFloatUIObject(iIdCounter, positionX, positionY, value);

	objectList.push_back(temp);
}

UserInterfaceManager::~UserInterfaceManager()
{
}
