#include "RenderEngine.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include <string.h> 
#include "Timer.h"
#include "Global.h"
#include "LogicManager.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
#include <iostream>
#include <cctype>
using namespace rapidjson;

RenderEngine* RenderEngine::instance;
extern GLuint texbkg;
//extern double fpsCount;
//extern double logicTime;
//extern double actualTime;
RenderEngine::RenderEngine()
{

}

void RenderEngine::InitRender()
{
	FONT_Init();	// Characters and symbols inicialization to draw on screen.

	// Set up rendering.
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); // Sets up clipping.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	// Specifies clear values for the color buffers.
	glMatrixMode(GL_PROJECTION);	// Specifies projection matrix is the current matrix.
	glLoadIdentity();	// Replaces the current matrix with the identity matrix.
	glOrtho(0.0, SCR_WIDTH, 0.0, SCR_HEIGHT, 0.0, 1.0);	// Multiplies the current matrix by an orthographic matrix.
	glEnable(GL_TEXTURE_2D);	// Enabling two-dimensional texturing.
	// NOTA: Mirar diferencias comentando las 2 siguientes funciones.
	glEnable(GL_BLEND);	// Blend the incoming RGBA color values with the values in the color buffers.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	// Blend func. for alpha color.
}

void RenderEngine::ShutdownRender()
{
	// Fonts shutdown.
	FONT_End();
}

void RenderEngine::RemoveASprite(Sprite* spriteToBeRemoved)
{
	for (int i = 0; i< sprites.size(); i++)
	{
		if (sprites[i] == spriteToBeRemoved) {
			sprites.erase(sprites.begin() + i);
			break;
		}
	}
}

RenderEngine* RenderEngine::GetInstance()
{
	if (instance == nullptr) {
		instance = new RenderEngine();
	}
	return instance;
}

void RenderEngine::GameRenderFunction()
{
	Global* global = Global::Get();
	// Render
	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.

	// Render backgground
	//If background is not part of a level, expand to whole screen
	if (global->GetCurrentLevel() == 0 || global->Victory() || global->GetCurrentLevel() == -1) {
		CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2.f, SCR_HEIGHT / 2.f), vec2(SCR_WIDTH, SCR_HEIGHT), global->GetBackground());
	}
	else {
		CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2.f, SCR_GAMEHEIGHT / 2.f), vec2(SCR_WIDTH, SCR_GAMEHEIGHT), global->GetBackground());
	}
	//Render entities only in level, not in Game Over or Main Menu
	if (global->GetCurrentLevel() > 0 && global->GetCurrentLevel() < 3 && !global->Victory()) {
		
		//Render Tiles
		for (int j = 0; j < tileSprites.size(); j++) {
			CORE_RenderSprite(tileSprites[j]->GetPos() + vec2(0.f, -16.f), tileSprites[j]->GetPos() + vec2(16.f,0.f), tileSprites[j]->GetGfx(), tileSprites[j]->GetXSpriteCoordinates(), tileSprites[j]->GetYSpriteCoordinates(), tileSprites[j]->GetSizePercentageX(), tileSprites[j]->GetSizePercentageY());
		}
		//Render Bullet
		if (bulletSprite) {
			CORE_RenderSprite(vec2(bulletSprite->GetPos().x - 8.f, bulletSprite->GetPos().y - bulletSprite->GetBulletHeight()), vec2(bulletSprite->GetPos().x + 8.f, bulletSprite->GetPos().y),  bulletSprite->GetGfx());
		}
		// Render balls and Player
		for (int i = 0; i < sprites.size(); i++) {
			CORE_RenderCenteredSprite(sprites[i]->GetPos(), vec2(sprites[i]->GetRadius() * 2.f * sprites[i]->GetFlipSprite(), sprites[i]->GetRadius() * 2.f), sprites[i]->GetGfx());
		}
		//Border
		CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2.f, SCR_GAMEHEIGHT / 2.f), vec2(SCR_WIDTH, SCR_GAMEHEIGHT), global->GetBackgroundBorder());

		//HP
		FONT_DrawString(vec2(SCR_WIDTH / 2 - 70, SCR_HEIGHT - 41), "HP: ");
		switch (global->GetHP())
		{
		case 3:
			CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2 - 16, SCR_HEIGHT - 32), vec2(16.f,16.f), global->GetPlayerHPAvatar());
			CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2, SCR_HEIGHT - 32), vec2(16.f, 16.f), global->GetPlayerHPAvatar());
			CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2 + 16, SCR_HEIGHT - 32), vec2(16.f, 16.f), global->GetPlayerHPAvatar());
			break;
		case 2:
			CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2 - 16, SCR_HEIGHT - 32), vec2(16.f, 16.f), global->GetPlayerHPAvatar());
			CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2, SCR_HEIGHT - 32), vec2(16.f, 16.f), global->GetPlayerHPAvatar());
			break;
		case 1:
			CORE_RenderCenteredSprite(vec2(SCR_WIDTH / 2 - 16, SCR_HEIGHT - 32), vec2(16.f, 16.f), global->GetPlayerHPAvatar());
			break;
		default:
			break;
		}

		// Time Logic
		char timeLogicString[50] = { 0 };
		snprintf(timeLogicString, 50, "LOGIC:%lf", LogicManager::GetInstance()->GetLogictime());
		FONT_DrawString(vec2(SCR_WIDTH - 256, SCR_HEIGHT - 16), timeLogicString);

		// Time Passed
		char currentTimeString[50] = { 0 };
		snprintf(currentTimeString, 50, "TIME:%.0lf", LogicManager::GetInstance()->GetActualTime());
		FONT_DrawString(vec2(SCR_WIDTH - 128, SCR_HEIGHT - 32), currentTimeString);

		// FPS
		double fps = 1.0 / LogicManager::GetInstance()->GetFpsCount();// fpsCount;
		char fpsString[50] = { 0 };
		snprintf(fpsString, 50, "FPS:%.0lf", fps);
		FONT_DrawString(vec2(0, SCR_HEIGHT - 16), fpsString);
	}
	
	if (global->GetCurrentLevel() == 0){
		// Text
		FONT_DrawString(vec2(SCR_WIDTH / 2 - 12 * 16, 16), "PRESS ENTER TO CONTINUE");
	}
	if (global->GetCurrentLevel() == -1) {
		// Text
		FONT_DrawString(vec2(SCR_WIDTH / 2 - 10 * 16, 16), "PRESS I TO CONTINUE");
	}
	

	// Exchanges the front and back buffers
	SYS_Show();

	if (global->GetNeedsReset()) {
		global->ResetLevel();
	}
	if (global->GetNeedsToChangeLevel()) {
		global->ChangeLevel();
	}
}
