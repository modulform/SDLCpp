#include "cLevelFactory.h"
#include <iostream>
#include <fstream>
#include "consoleHandler.h"

cLevelFactory::cLevelFactory()
{
	pCore = nullptr;
	pList = nullptr;
}

cLevelFactory::cLevelFactory(cGraphicsCore* gCore, std::list<cSprite*>* spriteList)
{
	pCore = gCore;
	pList = spriteList;
}

//Loads a level from a text file. Current format:
// 25 columns, 18 rows of single characters
// Each row is terminated by "\n" (integer 10, line break)
// "." reflects an empty slot in the map
// "B" reflects a brick in the map
int cLevelFactory::buildLevelFromFile(std::string filename)
{
	std::ifstream file(filename);
	if (!file)
	{
		//file could not be opened. Log to Console
		logToConsole("Unable to open level data file.", nullptr);
		return -1;
	}

	char c;
	int col = 0;
	int row = 0;
	cSprite* spriteBrick = nullptr;
	while (file.get(c))
	{
		switch (c)
		{
		case 10:	//"\n" line break char. Reset column counter and increase row counter used for sprite positioning
			col = 0;
			row = row + 1;
			break;
		case 66:	//"B")
			spriteBrick = new cSprite(pCore->getTexture("BRICK"), (float)(col * 32.0f), (float)(row * 32.0f), 32.0f, 32.0f, 0.00f, true);
			pList->push_back(spriteBrick);
			col = col + 1;
			break;
		case 46:
			col = col + 1;
			break;
		}
	}

	file.close();

	return 0;
}

cLevelFactory::~cLevelFactory()
{
}
