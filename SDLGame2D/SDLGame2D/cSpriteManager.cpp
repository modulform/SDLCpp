#include "cSpriteManager.h"



cSpriteManager::cSpriteManager()
{
	
}

void cSpriteManager::addSprite(cSprite* item)
{
	mSpriteList.push_back(item);
}

void  cSpriteManager::deleteSprite(cSprite* item)
{
	mSpriteList.remove(item);
}

void cSpriteManager::redrawSprites(cGraphicsCore* gCore)
{
	for (std::list<cSprite*>::iterator it = mSpriteList.begin(); it != mSpriteList.end(); it++)
	{
		(*it)->DrawSprite(gCore->getRenderer());
	}
}

cSpriteManager::~cSpriteManager()
{
}
