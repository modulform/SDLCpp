#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

	///<summary>Draws a red line one pixel of width (debug purposes)</summary>
	void drawDebugLine(int R, int G, int B, int x1, int y1, int x2, int y2);

	///<summary>Draws a red line one pixel of width (debug purposes)</summary>
	void drawDebugLine(int R, int G, int B, Vec2 p1, Vec2 p2);

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	std::list<texEntry> textureContainer;

	SDL_Texture* loadTexture(std::string path);
};