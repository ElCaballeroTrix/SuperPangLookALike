#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "../swalib_example/swalib_example/InitGame.h"
#include "../swalib_example/swalib_example/GameRender.h"
#include "../swalib_example/swalib_example/GameLogic.h"
#include "../swalib_example/swalib_example/Shutdown.h"
#include "../swalib_example/swalib_example/LogicManager.h"
#include "../swalib_example/swalib_example/RenderEngine.h"
#include "../swalib_example/swalib_example/Global.h"
#include "../swalib_example/swalib_example/Entity.h"
#include "../swalib_example/swalib_example/DisplacementComponent.h"

extern double fixedTick;
int Main(void)
{
	Global* global = Global::Get();
	LogicManager* logicManager = LogicManager::GetInstance();
	RenderEngine* renderEngine = RenderEngine::GetInstance();
	InitGameFunction();

	while (!SYS_GottaQuit()) {	// Controlling a request to terminate an application.

		//Ejercicio 2.1
		//Si se desactiva el VSync, las bolas se mueven muy rápido, imposible de seguir

		logicManager->Update();
		renderEngine->GameRenderFunction();
		
		SYS_Pump();	// Process Windows messages.
	}

	ShutDownFunction();

	return 0;
}
