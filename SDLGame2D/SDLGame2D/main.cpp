#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <list>

#include "globals.h"				//contains global definitions
#include "cSprite.h"				//general sprite class
#include "cPlayer.h"				//Child of cSprite: Specific player-sprite implementation
#include "cEnemy.h"					//Child of cSprite: Specific enemy-sprite implementation
#include "cGraphicsCore.h"			//handles graphics core functionality like renderer and textures
#include "consoleHandler.h"			//handles console output (debug output)
#include "collisionManager.h"		//handles collision detection

cGraphicsCore* gCore = nullptr;

int loadMedia()
{
	logToConsole("INF - Loading media...", nullptr);
	gCore->addTexture("PLAYER", "img\\player2.png");
	gCore->addTexture("ENEMY", "img\\enemy1.png");
	gCore->addTexture("ICON_WARNING", "img\\warning.png");

	return 0;
}

int main(int, char**)
{
	//BOOT UP GRAPHICS CORE
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
	cPlayer* spritePlayer = new cPlayer(gCore->getTexture("PLAYER"), 10.0f, 10.0f, 32.0f, 32.0f, 0.01f, true);
	cEnemy* spriteEnemy = new cEnemy(gCore->getTexture("ENEMY"), 100.0f, 100.0f, 32.0f, 32.0f, 0.01f, true);
	cSprite* spriteIconWarning = new cSprite(gCore->getTexture("ICON_WARNING"), 20.0f, 300.0f, 32.0f, 32.0f, 0.00f, false);
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
		spriteEnemy->Move();

		//Check collision
		if (doCollide(spritePlayer, spriteEnemy))
		{
			spriteIconWarning->SetIsVisible(true);
		}
		else
		{
			spriteIconWarning->SetIsVisible(false);
		}
		
		//Render new frame
		SDL_RenderClear(gCore->getRenderer());
		spritePlayer->DrawSprite(gCore->getRenderer());
		spriteEnemy->DrawSprite(gCore->getRenderer());
		spriteIconWarning->DrawSprite(gCore->getRenderer());
		SDL_RenderPresent(gCore->getRenderer());
	}


	//Shut down graphics engine
	gCore->shutdownGraphics();
	delete(gCore);
	gCore = nullptr;

	return 0;
}