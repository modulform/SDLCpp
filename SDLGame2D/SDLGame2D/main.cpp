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

std::list<cSprite*> spriteList;

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

	//Initialize spriteList
	spriteList.clear();

	//CREATE TEST SPRITE
	cPlayer* spritePlayer = new cPlayer(gCore->getTexture("PLAYER"), 10.0f, 10.0f, 32.0f, 32.0f, 0.04f, true);
	cEnemy* spriteEnemy = new cEnemy(gCore->getTexture("ENEMY"), 100.0f, 100.0f, 32.0f, 32.0f, 0.01f, true);
	cEnemy* spriteEnemy2 = new cEnemy(gCore->getTexture("ENEMY"), 200.0f, 150.0f, 32.0f, 32.0f, 0.02f, true);
	cSprite* spriteIconWarning = new cSprite(gCore->getTexture("ICON_WARNING"), 20.0f, 300.0f, 32.0f, 32.0f, 0.00f, false);
	//!TEST SPRITE

	//push sprites to the list
	spriteList.push_back(spritePlayer);
	spriteList.push_back(spriteEnemy);
	spriteList.push_back(spriteEnemy2);
	spriteList.push_back(spriteIconWarning);


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

		//RENDER FRAME
		SDL_RenderClear(gCore->getRenderer());		//clear renderer

		for (std::list<cSprite*>::iterator it = spriteList.begin(); it != spriteList.end(); it++)	//iterate throug spriteList
		{
			(*it)->Move();								//move sprite
			(*it)->DrawSprite(gCore->getRenderer());	//draw sprite
		}

		spriteIconWarning->SetIsVisible(doCollideSpriteGroup(spritePlayer, spriteList));	//check collision between player and the enemies

		SDL_RenderPresent(gCore->getRenderer());	//present frame to screen
		//END RENDERING FRAME
	}


	//Shut down graphics engine
	gCore->shutdownGraphics();
	delete(gCore);
	gCore = nullptr;

	return 0;
}