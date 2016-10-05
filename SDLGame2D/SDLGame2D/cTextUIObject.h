#pragma once

#include "cUIObject.h"

class cTextUIObject : public cUIObject
{
public:
	cTextUIObject();
	cTextUIObject(int id, float x, float y, std::string text);
	void RenderObject(SDL_Renderer* renderer);
	~cTextUIObject();

private:
	std::string mText;
};

