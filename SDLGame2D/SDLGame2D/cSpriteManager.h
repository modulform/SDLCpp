#pragma once

#include <list>
#include "cSprite.h"
#include "cGraphicsCore.h"

class cSpriteManager
{

public:
	cSpriteManager();

	void addSprite(cSprite* object);
	void deleteSprite(cSprite* object);
	void redrawSprites(cGraphicsCore* gCore);

	~cSpriteManager();

private:
	std::list<cSprite*> mSpriteList;
};

