#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "cSprite.h"		//general sprite class
#include "cGraphicsCore.h"	//handles graphics core functionality like renderer and textures
#include "consoleHandler.h"	//handles console output (debug output)

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400

cGraphicsCore* gCore = nullptr;

int loadMedia()
{
	logToConsole("INF - Loading media...", nullptr);
	gCore->addTexture("PLAYER", "img\\player1.png");

	return 0;
}

int main(int, char**)
{
	//BOOT UP GRAPHICS ENGINE
	logToConsole("INF - Initializing graphics core...", nullptr);
	gCore = new cGraphicsCore();
	if (gCore->initGraphics(SCREEN_WIDTH, SCREEN_HEIGHT) != 0)
	{
		logToConsole("ERR - Failed to initialize graphics engine ", "cGraphicsCore->initGraphics failed.");
		return 1;
	}
	logToConsole("SUC - Successfully initialized graphics core.", nullptr);

	logToConsole("INF - Loading media...", nullptr);

	//LOAD MEDIA
	if (loadMedia() == 0)
	{
		logToConsole("SUC - Successfully loaded media.", nullptr);
	}

	bool quit = false;		//main loop flag
	SDL_Event e;			//Event handler

	//CREATE TEST SPRITE
	cSprite* spritePlayer = new cSprite(gCore->getTexture("PLAYER"), 10.0f, 10.0f, 64, 64, 0.01f);
	//!TEST SPRITE

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//CHECK KEYBOARD INPUT
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_UP] == 1)
		{
			spritePlayer->SetVelY(-1.0f);
		}
		if (currentKeyStates[SDL_SCANCODE_UP] == 0)
		{
			if (spritePlayer->GetVelY() < 0)
				spritePlayer->SetVelY(0);
		}

		if (currentKeyStates[SDL_SCANCODE_DOWN] == 1)
		{
			spritePlayer->SetVelY(1.0f);
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN] == 0)
		{
			if (spritePlayer->GetVelY() > 0)
				spritePlayer->SetVelY(0);
		}

		if (currentKeyStates[SDL_SCANCODE_RIGHT] == 1)
		{
			spritePlayer->SetVelX(1.0f);
		}
		if (currentKeyStates[SDL_SCANCODE_RIGHT] == 0)
		{
			if (spritePlayer->GetVelX() > 0)
				spritePlayer->SetVelX(0);
		}

		if (currentKeyStates[SDL_SCANCODE_LEFT] == 1)
		{
			spritePlayer->SetVelX(-1.0f);
		}
		if (currentKeyStates[SDL_SCANCODE_LEFT] == 0)
		{
			if (spritePlayer->GetVelX() < 0)
				spritePlayer->SetVelX(0);
		}

		//Apply movement
		spritePlayer->Move();
		//Render new frame
		SDL_RenderClear(gCore->getRenderer());
		spritePlayer->DrawSprite(gCore->getRenderer());
		SDL_RenderPresent(gCore->getRenderer());
	}


	//Shut down graphics engine
	gCore->shutdownGraphics();
	delete(gCore);
	gCore = nullptr;

	return 0;
}