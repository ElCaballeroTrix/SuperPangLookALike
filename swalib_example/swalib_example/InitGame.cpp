#include "InitGame.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "Textures.h"
#include "GameLogic.h"
#include "Timer.h"
#include "LogicManager.h"
#include <vector>
#include "RenderEngine.h"
#include "Global.h"

extern LARGE_INTEGER frequency, previousTime, currentTime;
void InitGameFunction() {
	QueryPerformanceFrequency(&frequency);
	//QueryPerformanceFrequency(&LogicManager::GetInstance()->GetFrequency());
	QueryPerformanceCounter(&previousTime);
	//QueryPerformanceCounter(&LogicManager::GetInstance()->GetPreviousTime());


	RenderEngine::GetInstance()->InitRender();
	LogicManager::GetInstance()->InitData();
	Global::Get()->InitializeTiles();
}
