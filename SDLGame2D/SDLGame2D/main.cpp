#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <list>

#include "globals.h"				//contains global definitions
#include "cSprite.h"				//general sprite class
#include "cPlayer.h"				//Child of cSprite: Specific player-sprite implementation
#include "cEnemy.h"					//Child of cSprite: Specific enemy-sprite implementation
#include "cGraphicsCore.h"			//handles graphics core functionality like renderer and textures
#include "consoleHandler.h"			//handles console output (debug output)
#include "collisionManager.h"		//handles collision detection
#include "UserInterfaceManager.h"	//handles user interface management and rendering (for now only text rendering)

cGraphicsCore* gCore = nullptr;
UserInterfaceManager* UIManager = nullptr;

std::list<cSprite*> spriteList;
float fFps;
Uint32 fps_lastTime;
Uint32 fps_frames;

int loadMedia()
{
	logToConsole("INF - Loading media...", nullptr);
	gCore->addTexture("PLAYER", "img\\player2.png");
	gCore->addTexture("ENEMY", "img\\enemy1.png");
	gCore->addTexture("ICON_WARNING", "img\\warning.png");
	return 0;
}

int initGlobalObjects()
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

	//CREATE ADDITIONAL MANAGERS
	UIManager = new UserInterfaceManager(gCore->getRenderer());

	//LOAD MEDIA
	if (loadMedia() == 0)
	{
		logToConsole("SUC - Successfully loaded media.", nullptr);
	}

	//Initialize spriteList
	spriteList.clear();

	//initialize global variables
	fFps = 0.0f;
	fps_lastTime = 0;
	fps_frames = 0;

	return 0;
}

int main(int, char**)
{
	if (initGlobalObjects() == 1)
	{
		return 1;			//exit if initialize was not successful
	}

	bool quit = false;		//main loop flag
	SDL_Event e;			//Event handler

	//CREATE TEST SPRITE
	cPlayer* spritePlayer = new cPlayer(gCore->getTexture("PLAYER"), (float)(SCREEN_WIDTH / 2.0f)-16.0f, (float)(SCREEN_HEIGHT / 2.0f)-16.0f, 32.0f, 32.0f, 0.06f, true);
	cEnemy* spriteEnemy = new cEnemy(gCore->getTexture("ENEMY"), 100.0f, 100.0f, 32.0f, 32.0f, 0.04f, true);
	cEnemy* spriteEnemy2 = new cEnemy(gCore->getTexture("ENEMY"), 600.0f, 300.0f, 32.0f, 32.0f, 0.03f, true);
	cSprite* spriteIconWarning = new cSprite(gCore->getTexture("ICON_WARNING"), (SCREEN_WIDTH / 2), (SCREEN_HEIGHT - 50.0f), 32.0f, 32.0f, 0.00f, false);
	//!TEST SPRITE

	//push sprites to the list
	spriteList.push_back(spritePlayer);
	spriteList.push_back(spriteEnemy);
	spriteList.push_back(spriteEnemy2);
	spriteList.push_back(spriteIconWarning);

	//TEXT RENDERING TRYOUT
	UIManager->addObject("m.i.n.d.f.l.y 2016", 655.0f, 380.0f);
	UIManager->addObject("FPS: ", 10.0f, 380.0f);
	UIManager->addObject(&fFps, 55.0f, 380.0f);
	//END TEXT RENDERING

	//INITIALIZE FRAMES COUNTER
	fps_lastTime = SDL_GetTicks();

	//BEGIN MAIN GAME LOOP
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

		UIManager->RenderObjects(gCore->getRenderer());

		SDL_RenderPresent(gCore->getRenderer());	//present frame to screen
		//END RENDERING FRAME

		//HANDLE FRAME COUNTER
		fps_frames++;
		if (fps_lastTime < SDL_GetTicks() - FPS_INTERVAL * 1000)
		{
			fps_lastTime = SDL_GetTicks();
			fFps = (float)fps_frames;
			fps_frames = 0;
		}
		//END HANDLE FRAME COUNTER
	}//END MAIN GAME LOOP


	//Shut down graphics engine
	gCore->shutdownGraphics();
	delete(gCore);
	gCore = nullptr;

	return 0;
}