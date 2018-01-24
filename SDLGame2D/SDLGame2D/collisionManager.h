#pragma once

#include <list>
#include "cSprite.h"

CollisionResult doCollideSpriteSprite(cSprite* sprite1, cSprite* sprite2);
cSprite* getNearestSprite(cSprite* sprite1, std::list<cSprite*> spriteList);
bool doCollideSpriteGroup(cSprite* sprite, std::list<cSprite*> group);