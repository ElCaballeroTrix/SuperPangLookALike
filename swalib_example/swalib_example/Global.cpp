#include "Global.h"
#include "Entity.h"
#include "Tile.h"
#include "LogicManager.h"
#include "RenderEngine.h"
#include "CollisionComponent.h"
#include "DisplacementComponent.h"
#include "RenderComponent.h"

Global* Global::instance = nullptr;

Global::~Global()
{
	delete level;
	level = nullptr;
	delete player;
	player = nullptr;
	for (size_t i = 0; i < balls.size(); i++)
	{
		delete balls[i];
		balls[i] = nullptr;
	}
	for (Tile* tile : initialTiles) {
		delete tile;
		tile = nullptr;
	}
}

Global* Global::Get()
{
	if (instance == nullptr)
	{
		instance = new Global();
	}
	return instance;
}

void Global::ChangeLevel()
{
	needsToChangeLevel = false;
	++backgroundIndex;
	background = CORE_LoadPNG(backgrounds[backgroundIndex], true);
	if (backgroundIndex == 0) {
		level->ChangeLevel();
	}
	else if (backgroundIndex != 0 && backgroundIndex < 3) {
		tiles.clear();
		level->ChangeLevel();
		if (backgroundIndex != 1) {
			SYS_Sleep(3000);
			delete player;
			player = nullptr;
			if (bullet) {
				EraseBullet();
			}
			RenderEngine::GetInstance()->RemoveSprites();
			LogicManager::GetInstance()->InitData();
		}
		ActivateEntities(true);
	}
	else if (backgroundIndex == 3) {
		//Victory scene
		SYS_Sleep(3000);
		victory = true;
		tiles.clear();
		delete player;
		player = nullptr;
		RenderEngine::GetInstance()->RemoveSprites();
		RenderEngine::GetInstance()->RemoveTileSprites();
		if (bullet) {
			EraseBullet();
		}
	}
}

void Global::InitializeTiles()
{
	//Blue Platforms
	GLuint bluePlatformTex = CORE_LoadPNG("data/PlatformSheet.png", false);
	Tile* tilePlatform1_0 = new Tile(68162, bluePlatformTex, 0.0, 0.0, 0.125, 1.0, false, 16.0f, 16.0f, 0);
	Tile* tilePlatform1_1 = new Tile(68163, bluePlatformTex, 0.125, 0.0, 0.125);
	Tile* tilePlatform1_2 = new Tile(68164, bluePlatformTex, 0.25, 0.0, 0.125);
	Tile* tilePlatform1_3 = new Tile(68165, bluePlatformTex, 0.375, 0.0, 0.125);
	Tile* tilePlatform1_4 = new Tile(68166, bluePlatformTex, 0.5, 0.0, 0.125);
	Tile* tilePlatform1_5 = new Tile(68167, bluePlatformTex, 0.625, 0.0, 0.125);
	Tile* tilePlatform1_6 = new Tile(68168, bluePlatformTex, 0.75, 0.0, 0.125);
	Tile* tilePlatform1_7 = new Tile(68169, bluePlatformTex, 0.875, 0.0, 0.125, 1.0, false, 16.0f, 16.0f, 1);
	initialTiles.push_back(tilePlatform1_0); initialTiles.push_back(tilePlatform1_1); initialTiles.push_back(tilePlatform1_2);
	initialTiles.push_back(tilePlatform1_3); initialTiles.push_back(tilePlatform1_4); initialTiles.push_back(tilePlatform1_5);
	initialTiles.push_back(tilePlatform1_6); initialTiles.push_back(tilePlatform1_7);

	//Pink Platform
	GLuint pinkPlatformTex = CORE_LoadPNG("data/Platform2Sheet.png", false);
	Tile* tilePlatform2_0 = new Tile(70721, pinkPlatformTex, 0.0, 0.0, 0.25, 1.0, false, 16.0f, 16.0f, 0);
	Tile* tilePlatform2_1 = new Tile(70722, pinkPlatformTex, 0.25, 0.0, 0.25);
	Tile* tilePlatform2_2 = new Tile(70723, pinkPlatformTex, 0.5, 0.0, 0.25);
	Tile* tilePlatform2_3 = new Tile(70724, pinkPlatformTex, 0.75, 0.0, 0.25, 1.0, false, 16.0f, 16.0f, 1);
	initialTiles.push_back(tilePlatform2_0); initialTiles.push_back(tilePlatform2_1); initialTiles.push_back(tilePlatform2_2);
	initialTiles.push_back(tilePlatform2_3);

	//Stairs
	GLuint stairsTex = CORE_LoadPNG("data/StairsSheet.png", false);
	float stairHeight = 16.f;
	float stairWidth = 8.f;
	Tile* tileStairs0 = new Tile(71654, stairsTex, 0.0, 0.0, 0.34, 0.17, true, stairWidth, stairHeight, 0);
	Tile* tileStairs1 = new Tile(71655, stairsTex, 0.34, 0.0, 0.34, 0.17, true, stairWidth, stairHeight, 0);
	Tile* tileStairs2 = new Tile(71656, stairsTex, 0.68, 0.0, 0.34, 0.17, true, stairWidth, stairHeight, 0);

	Tile* tileStairs3 = new Tile(71751, stairsTex, 0.0, 0.17, 0.34, 0.17, true, stairWidth, stairHeight);
	Tile* tileStairs4 = new Tile(71752, stairsTex, 0.34, 0.17, 0.34, 0.17, true, stairWidth, stairHeight);
	Tile* tileStairs5 = new Tile(71753, stairsTex, 0.68, 0.17, 0.34, 0.17, true, stairWidth, stairHeight);

	Tile* tileStairs6 = new Tile(71848, stairsTex, 0.0, 0.34, 0.34, 0.17, true, stairWidth, stairHeight);
	Tile* tileStairs7 = new Tile(71849, stairsTex, 0.34, 0.34, 0.34, 0.17, true, stairWidth, stairHeight);
	Tile* tileStairs8 = new Tile(71850, stairsTex, 0.68, 0.34, 0.34, 0.17, true, stairWidth, stairHeight);

	Tile* tileStairs9 = new Tile(71945, stairsTex, 0.0, 0.51, 0.34, 0.17, true, stairWidth, stairHeight);
	Tile* tileStairs10 = new Tile(71946, stairsTex, 0.34, 0.51, 0.34, 0.17, true, stairWidth, stairHeight);
	Tile* tileStairs11 = new Tile(71947, stairsTex, 0.68, 0.51, 0.34, 0.17, true, stairWidth, stairHeight);

	Tile* tileStairs12 = new Tile(72042, stairsTex, 0.0, 0.68, 0.34, 0.17, true, stairWidth, stairHeight);
	Tile* tileStairs13 = new Tile(72043, stairsTex, 0.34, 0.68, 0.34, 0.17, true, stairWidth, stairHeight);
	Tile* tileStairs14 = new Tile(72044, stairsTex, 0.68, 0.68, 0.34, 0.17, true, stairWidth, stairHeight);

	Tile* tileStairs15 = new Tile(72139, stairsTex, 0.0, 0.85, 0.34, 0.17, true, stairWidth, stairHeight, 1);
	Tile* tileStairs16 = new Tile(72140, stairsTex, 0.34, 0.85, 0.34, 0.17, true, stairWidth, stairHeight, 1);
	Tile* tileStairs17 = new Tile(72141, stairsTex, 0.68, 0.85, 0.34, 0.17, true, stairWidth, stairHeight, 1);

	initialTiles.push_back(tileStairs0); initialTiles.push_back(tileStairs1); initialTiles.push_back(tileStairs2);
	initialTiles.push_back(tileStairs3); initialTiles.push_back(tileStairs4); initialTiles.push_back(tileStairs5);
	initialTiles.push_back(tileStairs6); initialTiles.push_back(tileStairs7); initialTiles.push_back(tileStairs8);
	initialTiles.push_back(tileStairs9); initialTiles.push_back(tileStairs10); initialTiles.push_back(tileStairs11);
	initialTiles.push_back(tileStairs12); initialTiles.push_back(tileStairs13); initialTiles.push_back(tileStairs14);
	initialTiles.push_back(tileStairs15); initialTiles.push_back(tileStairs16); initialTiles.push_back(tileStairs17);

}

Tile* Global::GetAnInitialTile(int identifier)
{
	for (Tile* tile : initialTiles)
	{
		if (tile->GetIdentifier() == identifier) {
			return tile;
		}
	}
	return nullptr;
}

void Global::EraseBullet()
{
	bullet->SetIsActive(false);
	delete bullet; 
	bullet = nullptr;
	RenderEngine::GetInstance()->RemoveBulletSprite();
}

void Global::ActivateEntities(bool isActive)
{
	player->SetIsActive(isActive);
	for (int i = 0; i < balls.size(); i++)
	{
		balls[i]->SetIsActive(isActive);
	}
}

void Global::ResetLevel()
{
	if (playerHP == 0) {
		//Dead
		//WIN_bGottaQuit = true;
		ActivateEntities(false);
		balls.clear();
		delete player;
		player = nullptr;
		if (bullet) {
			EraseBullet();
		}
		delete level;
		level = nullptr;
		needsReset = false;
		level = new Level();
		LogicManager::GetInstance()->InitData();
		level->DeadLevel();
		backgroundIndex = -1;
		playerHP = 3;
	}
	else {
		ActivateEntities(false);
		SYS_Sleep(1000);
		balls.clear();
		delete player;
		player = nullptr;
		if (bullet) {
			EraseBullet();
		}
		RenderEngine::GetInstance()->RemoveSprites();
		LogicManager::GetInstance()->InitData();
		ActivateEntities(true);
		needsReset = false;
	}
}

void Global::LoseHP()
{
	--playerHP; 
	if (playerHP == 0) {
		//Show Death Background
		level->DeadLevel();
		background = CORE_LoadPNG(backgrounds[4], true);
		RenderEngine::GetInstance()->RemoveSprites();
		RenderEngine::GetInstance()->RemoveTileSprites();
	}
	
}

void Global::ExplodeBall(Entity* explodingBall)
{
	vec2 lastBallPos = explodingBall->FindComponent<DisplacementComponent>()->GetPos();
	vec2 lastBallVel = explodingBall->FindComponent<DisplacementComponent>()->GetVel();
	float lastBallRadius = explodingBall->FindComponent<CollisionComponent>()->GetRadius();

	for (int i = 0;balls.size(); i++)
	{
		if (balls[i] == explodingBall) {
			//If explodingBall is at its smallest size, delete it, else modify it and create another one
			if (lastBallRadius == smallestBallRadius) {
				RenderEngine::GetInstance()->RemoveASprite(explodingBall->FindComponent<RenderComponent>()->GetSprite());
				explodingBall->SetIsActive(false);
				balls.erase(balls.begin() + i);
				//If all balls have been destroid, change level
				if (balls.size() == 0) {
					needsToChangeLevel = true;
					//Change Player Sprite to Celebrate
					player->FindComponent<RenderComponent>()->GetSprite()->SetGfx(victoryPlayerSprite);
				}
				break;
			}
			else {
				vec2 lastBallPos = balls[i]->FindComponent<DisplacementComponent>()->GetPos();
				vec2 lastBallVel = balls[i]->FindComponent<DisplacementComponent>()->GetVel();
				float lastBallRadius = balls[i]->FindComponent<CollisionComponent>()->GetRadius();
				GLuint lastBallTex = balls[i]->FindComponent<RenderComponent>()->GetGfx();
				//Maintain ball but change size
				float newVelY;
				if (lastBallVel.y > 0.f) {
					newVelY = lastBallVel.y;
				}
				else {
					newVelY = lastBallVel.y * -1.0f;
				}
				balls[i]->FindComponent<DisplacementComponent>()->SetVel(vec2(lastBallVel.x, newVelY / 1.1f));
				balls[i]->FindComponent<CollisionComponent>()->SetRadius(lastBallRadius / 2);
				balls[i]->FindComponent<RenderComponent>()->SetRadius(lastBallRadius / 2);
				balls[i]->FindComponent<RenderComponent>()->GetSprite()->SetRadius(lastBallRadius / 2);
				//New Ball smaller with velocity changed
				Entity* newBall = new Entity(balls[i]->GetJsonFile());//Cambiar al color original
				newBall->FindComponent<DisplacementComponent>()->SetPos(lastBallPos);
				newBall->FindComponent<DisplacementComponent>()->SetVel(vec2(lastBallVel.x * -1.0f, newVelY / 1.1f));
				newBall->FindComponent<CollisionComponent>()->SetRadius(lastBallRadius / 2);
				newBall->FindComponent<RenderComponent>()->SetRadius(lastBallRadius / 2);
				newBall->SetIsActive(true);
				balls.push_back(newBall);
				RenderEngine::GetInstance()->AddSprite(newBall->FindComponent<RenderComponent>()->GetSprite());
				break;
			}
		}
	}
}

