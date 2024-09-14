#include "GameRender.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include <string.h> 
#include "Textures.h"
#include "Timer.h"
#include "LogicManager.h"

//*******************************************
//Previous function for render
//*******************************************

//extern Ball balls[NUM_BALLS];
//extern GLuint texbkg;
//extern double fpsCount;
//extern double logicTime;
//extern double actualTime;
//
//void GameRenderFunction() {
//	// Render
//	glClear(GL_COLOR_BUFFER_BIT);	// Clear color buffer to preset values.
//
//	// Render backgground
//	for (int i = 0; i <= SCR_WIDTH / 128; i++) {
//		for (int j = 0; j <= SCR_HEIGHT / 128; j++) {
//			CORE_RenderCenteredSprite(vec2(i * 128.f + 64.f, j * 128.f + 64.f), vec2(128.f, 128.f), texbkg);
//		}
//	}
//
//	// Render balls
//	for (int i = 0; i < NUM_BALLS; i++) {
//		CORE_RenderCenteredSprite(LogicManager::GetInstance()->GetBalls()[i]->GetPos(), vec2(LogicManager::GetInstance()->GetBalls()[i]->GetRadius() * 2.f, LogicManager::GetInstance()->GetBalls()[i]->GetRadius() * 2.f), LogicManager::GetInstance()->GetBalls()[i]->GetGfx());
//	}
//
//	// Text
//	FONT_DrawString(vec2(SCR_WIDTH / 2 - 6 * 16, 16), "HELLO WORLD!");
//	
//	// Time Logic
//	char timeLogicString[50] = { 0 };
//	snprintf(timeLogicString, 50, "LOGIC:%lf", logicTime);
//	FONT_DrawString(vec2(SCR_WIDTH - 256, SCR_HEIGHT - 16), timeLogicString);
//
//	// Time Passed
//	char currentTimeString[50] = { 0 };
//	snprintf(currentTimeString, 50,"TIME:%.0lf", actualTime);
//	FONT_DrawString(vec2(SCR_WIDTH - 128, SCR_HEIGHT - 32 ), currentTimeString);
//
//	// FPS
//	double fps = 1.0 / fpsCount;
//	char fpsString[50] = { 0 };
//	snprintf(fpsString, 50, "FPS:%.0lf", fps);
//	FONT_DrawString(vec2(0, SCR_HEIGHT - 16), fpsString);
//
//	
//
//	// Exchanges the front and back buffers
//	SYS_Show();
//}


