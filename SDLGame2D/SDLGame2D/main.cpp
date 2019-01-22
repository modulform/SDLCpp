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
Uint32 iFpsLastTime;
Uint32 iFpsFrameCount;

int loadMedia()
{
	logToConsole("INF - Loading media...", nullptr);
	gCore->addTexture("PLAYER", "img\\player2.png");
	gCore->addTexture("ENEMY", "img\\enemy1.png");
	gCore->addTexture("BRICK", "img\\brick128.png");
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
	iFpsLastTime = 0;
	iFpsFrameCount = 0;

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
	cSprite* spriteBrick = new cSprite(gCore->getTexture("BRICK"), 500.0f, SCREEN_HEIGHT-100.0f, 128.0f, 32.0f, 0.0f, true);
	cSprite* spriteBrick2 = new cSprite(gCore->getTexture("BRICK"), 0.0f, SCREEN_HEIGHT - 32.0f, 128.0f, 32.0f, 0.0f, true);
	cSprite* spriteBrick3 = new cSprite(gCore->getTexture("BRICK"), 200.0f, SCREEN_HEIGHT - 150.0f, 128.0f, 32.0f, 0.0f, true);
	//!TEST SPRITE

	//push sprites to the list
	spriteList.push_back(spriteBrick);
	spriteList.push_back(spriteBrick2);
	spriteList.push_back(spriteBrick3);
	spriteList.push_back(spritePlayer);

	//TEXT RENDERING TRYOUT
	UIManager->addObject("m.i.n.d.f.l.y 2018", 655.0f, 10.0f);
	UIManager->addObject("FPS: ", 10.0f, 10.0f);
	UIManager->addObject(&fFps, 55.0f, 10.0f);
	//END TEXT RENDERING

	//INITIALIZE FRAMES COUNTER
	iFpsLastTime = SDL_GetTicks();

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

		//CHECK KEYBOARD INPUT AND APPLY MOVEMENT
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if ((currentKeyStates[SDL_SCANCODE_UP] == 1) && (spritePlayer->mIsOnGround))
		{
			spritePlayer->SetVelY(-3.5f);
			spritePlayer->mIsOnGround = false;
		}

		if ((currentKeyStates[SDL_SCANCODE_RIGHT] == 1) && (!spritePlayer->getIsColliding())/* && (spritePlayer->mIsOnGround)*/) //air control ON
		{
			spritePlayer->incVelX(0.005f);
		}

		if ((currentKeyStates[SDL_SCANCODE_LEFT] == 1) && (!spritePlayer->getIsColliding())/* && (spritePlayer->mIsOnGround)*/) //air control ON
		{
			spritePlayer->incVelX(-0.005f);
		}

		if (currentKeyStates[SDL_SCANCODE_DELETE] == 1)
		{
			spritePlayer->SetPosX((float)(SCREEN_WIDTH / 2.0f) - 16.0f);
			spritePlayer->SetPosY((float)(SCREEN_HEIGHT / 2.0f) - 16.0f);
			spritePlayer->SetVelX(0.0f);
			spritePlayer->SetVelY(0.0f);
		}

		if (currentKeyStates[SDL_SCANCODE_ESCAPE] == 1)
		{
			quit = true;
		}

		//RENDER FRAME
		SDL_SetRenderDrawColor(gCore->getRenderer(), 0, 0, 0, 0);
		SDL_RenderClear(gCore->getRenderer());		//clear renderer

		for (std::list<cSprite*>::iterator it = spriteList.begin(); it != spriteList.end(); it++)	//iterate throug spriteList
		{
			(*it)->Move();								//move sprite
			(*it)->DrawSprite(gCore);	//draw sprite
		}

		//FIND NEAREST SPRITE AND DRAW LINE FOR DEBUG PURPOSES
		cSprite* nearestSprite = getNearestSprite(spritePlayer, spriteList);

		if (nearestSprite != nullptr)
		{
			gCore->drawDebugLine(0, 255, 0, spritePlayer->getCenter(), nearestSprite->getCenter());
		}

		//COLLISION DETECTION AND REACTION
		CollisionResult tempCol = doCollideSpriteSprite(spritePlayer, nearestSprite);
		if (tempCol.isColliding)
		{
			//react on collision result
			switch (tempCol.colDirection)
			{
			case fromTop:
				spritePlayer->SetPosY(nearestSprite->getPosition().y - spritePlayer->getScale().y-1.0f);
				spritePlayer->mIsOnGround = true;	//...tell the sprite it reached ground
				break;
			case fromBottom:
				spritePlayer->SetVelY(spritePlayer->getVelocity().y * (-0.7f)); //...invert the y-velocity (bounce back)
				break;
			case fromLeft:
				spritePlayer->SetPosX(spritePlayer->getOldPosition().x);
				spritePlayer->SetVelX(0.0f);
				break;
			case fromRight:
				spritePlayer->SetPosX(spritePlayer->getOldPosition().x);
				spritePlayer->SetVelX(0.0f);
				break;
			}
		}
		//END COLLISION DETECTION AND REACTION

		UIManager->RenderObjects(gCore->getRenderer());

		SDL_RenderPresent(gCore->getRenderer());	//present frame to screen
		//END RENDERING FRAME

		//HANDLE FRAME COUNTER
		iFpsFrameCount++;
		if (iFpsLastTime < SDL_GetTicks() - FPS_INTERVAL * 1000)
		{
			iFpsLastTime = SDL_GetTicks();
			fFps = (float)iFpsFrameCount;
			iFpsFrameCount = 0;
		}
		//END HANDLE FRAME COUNTER
	}//END MAIN GAME LOOP


	//Shut down graphics engine
	gCore->shutdownGraphics();
	delete(gCore);
	gCore = nullptr;

	return 0;
}