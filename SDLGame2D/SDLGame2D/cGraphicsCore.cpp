#include "cGraphicsCore.h"


cGraphicsCore::cGraphicsCore()
{

}

int cGraphicsCore::initGraphics(int winWidth, int winHeight)
{
	//initialize SDL framework
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		logToConsole("ERR - SDL_Init ", SDL_GetError());
		return 1;
	}

	//initalize PNG support
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		logToConsole("ERR - IMG_Init ", SDL_GetError());
	}

	//initialize TTF rendering support
	if (TTF_Init() == -1)
	{
		logToConsole("ERR - TTF_Init ", TTF_GetError());
	}

	//create application window
	mWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	if (mWindow == nullptr)
	{
		logToConsole("ERR - SDL_CreateWindow ", SDL_GetError());
		return 1;
	}

	// create renderer
	// Remark (2016-10-02): Added VSYNC for framerate limitation. Seems to lower the CPU usage...better manually cap it?
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr)
	{
		logToConsole("ERR - CreateRenderer ", SDL_GetError());
		return 1;
	}
	else
	{
		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
	}

	return 0;
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

int cGraphicsCore::shutdownGraphics()
{
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	IMG_Quit();
	SDL_Quit();

	return 0;
}

cGraphicsCore::~cGraphicsCore()
{
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;
}