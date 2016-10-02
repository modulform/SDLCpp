#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <list>

#include "consoleHandler.h"
#include "globals.h"

struct texEntry
{
	SDL_Texture* texture;
	std::string name;
};

class cGraphicsCore
{
public:
	cGraphicsCore();
	~cGraphicsCore();

	///<summar>Initializes SDL framework and creates a window of specified size</summary>
	int initGraphics(int winWidth, int winHeight);

	///<summary>Shuts down SDL and destroys the window
	int shutdownGraphics();

	///<summary>Returns the renderer pointer of the cGraphicsCore class</summary>
	SDL_Renderer* getRenderer();

	///<summary>Loads a texture from given image and adds it to the texture container</summary>
	void addTexture(std::string name, std::string path);

	///<summary>Returns the texture pointer for a given name</summary>
	SDL_Texture* getTexture(std::string name);
private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	std::list<texEntry> textureContainer;

	SDL_Texture* loadTexture(std::string path);
};