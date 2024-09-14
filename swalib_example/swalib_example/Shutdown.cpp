#include "Shutdown.h"
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "Textures.h"
#include "LogicManager.h"
#include "RenderEngine.h"

extern GLuint texbkg;
extern GLuint texsmallball;

void ShutDownFunction() {
	// End app.
	LogicManager::GetInstance()->ShutdownData();
	RenderEngine::GetInstance()->ShutdownRender();
}