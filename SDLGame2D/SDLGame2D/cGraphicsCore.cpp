#include "cGraphicsCore.h"


cGraphicsCore::cGraphicsCore(SDL_Window* window)
{
	mWindow = window;	//get window pointer from parameter list
	
	// initialize renderer and PNG image processing
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
	{
		logToConsole("ERR - CreateRenderer ", SDL_GetError());
	}
	else
	{
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			logToConsole("ERR - IMG_Init ", SDL_GetError());
		}
	}
}

SDL_Renderer* cGraphicsCore::getRenderer()
{
	return mRenderer;
}

SDL_Texture* cGraphicsCore::loadTexture(std::string path)
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
	{
		logToConsole("ERR - IMG_Load ", SDL_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
		if (newTexture == nullptr)
		{
			logToConsole("ERR - SDL_CreateTextureFromSurface ", SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

void cGraphicsCore::addTexture(std::string name, std::string path)
{
	texEntry tempEntry;
	tempEntry.name = name;
	tempEntry.texture = loadTexture(path);

	if (tempEntry.texture == nullptr)
	{
		logToConsole("ERR - Failed to load texture ", path.c_str());
	}
	else
	{
		textureContainer.push_back(tempEntry);
		logToConsole("SUC - Loaded texture ", path.c_str());
	}
}

SDL_Texture* cGraphicsCore::getTexture(std::string name)
{
	if (name == "")
	{
		logToConsole("ERR - cGraphicsCore.getTexture ", "Name was null-string");
	}
	else
	{
		for (std::list<texEntry>::iterator it = textureContainer.begin(); it != textureContainer.end(); it++)
		{
			if (it->name == name)
			{
				return it->texture;
			}
		}
		return nullptr;
	}
	return nullptr;
}

cGraphicsCore::~cGraphicsCore()
{
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;
}