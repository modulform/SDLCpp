#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

#include "cGraphicsCore.h"	//handles graphics core functionality like renderer and textures
#include "consoleHandler.h"	//handles console output (debug output)
#include "cSprite.h"		//general sprite class

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

SDL_Window* gWindow = nullptr;
cGraphicsCore* gCore = nullptr;


int initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		logToConsole("ERR - SDL_Init ", SDL_GetError());
		return 1;
	}

	gWindow = SDL_CreateWindow("2D Game Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr)
	{
		logToConsole("ERR - SDL_CreateWindow ", SDL_GetError());
		return 1;
	}
	else
	{
		gCore = new cGraphicsCore(gWindow);
	}

	return 0;
}

int loadMedia()
{
	logToConsole("INF - Loading media...", nullptr);
	gCore->addTexture("PLAYER", "img\\player1.png");
	gCore->addTexture("BRICK", "img\\brick32.png");

	return 0;
}

void closeSDL()
{
	delete(gCore);

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}

int main(int, char**)
{
	//initialize SDL and report success
	if (initSDL() == 0)
	{
		logToConsole("SUC - SDL initialized successfully.", nullptr);
	}

	//load media here
	if (loadMedia() == 0)
	{
		logToConsole("SUC - Successfully loaded media.", nullptr);
	}

	bool quit = false;		//main loop flag
	SDL_Event e;			//Event handler

							//CREATE TEST SPRITE
	cSprite* spritePlayer = new cSprite(gCore->getTexture("PLAYER"), 10.0f, 10.0f, 64, 64, 0.01f);
	cSprite* spriteBrick1 = new cSprite(gCore->getTexture("BRICK"), 100.0f, 100.0f, 32, 32, 0);
	cSprite* spriteBrick2 = new cSprite(gCore->getTexture("BRICK"), 132.0f, 100.0f, 32, 32, 0);
	//!TEST SPRITE

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
					case SDLK_RIGHT:
						spritePlayer->SetVelX(1.0f);
						break;
					case SDLK_LEFT:
						spritePlayer->SetVelX(-1.0f);
						break;
					case SDLK_DOWN:
						spritePlayer->SetVelY(1.0f);
						break;
					case SDLK_UP:
						spritePlayer->SetVelY(-1.0f);
						break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym)
				{
					case SDLK_RIGHT:
						if (spritePlayer->GetVelX() > 0)
							spritePlayer->SetVelX(0);
						break;
					case SDLK_LEFT:
						if (spritePlayer->GetVelX() < 0)
							spritePlayer->SetVelX(0);
						break;
					case SDLK_DOWN:
						if (spritePlayer->GetVelY() > 0)
							spritePlayer->SetVelY(0);
						break;
					case SDLK_UP:
						if (spritePlayer->GetVelY() < 0)
							spritePlayer->SetVelY(0);
						break;
				}
				break;
			}

		}
		//Apply movement
		spritePlayer->Move();
		//Render new frame
		SDL_RenderClear(gCore->getRenderer());
		spritePlayer->DrawSprite(gCore->getRenderer());
		SDL_RenderPresent(gCore->getRenderer());
	}


	//Close SDL
	closeSDL();

	return 0;
}