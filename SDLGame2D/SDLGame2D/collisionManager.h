#pragma once

#include <list>
#include "cSprite.h"

bool doCollideSpriteSprite(cSprite* sprite1, cSprite* sprite2);
bool doCollideSpriteGroup(cSprite* sprite, std::list<cSprite*> group);

