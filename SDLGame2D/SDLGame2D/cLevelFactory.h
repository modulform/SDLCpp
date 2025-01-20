#pragma once

#include "cGraphicsCore.h"
#include "cSprite.h"
#include <string>

class cLevelFactory
{
public:
	cLevelFactory();
	cLevelFactory(cGraphicsCore* gCore, std::list<cSprite*>* spriteList);
	int buildLevelFromFile(std::string filename);
	~cLevelFactory();
private:
	cGraphicsCore* pCore = NULL;
	std::list<cSprite*>* pList = NULL;
};

