#include "LogicManager.h"
#include "sys.h"
#include "RenderEngine.h"
#include "Global.h"
#include "Entity.h"
#include "CollisionComponent.h"
#include "DisplacementComponent.h"
#include "RenderComponent.h"

LogicManager* LogicManager::instance = nullptr;
extern GLuint texbkg;
extern GLuint texsmallball;
extern double fixedTick;
LogicManager::LogicManager()
{
}
LogicManager* LogicManager::GetInstance()
{
	if (instance == nullptr) {
		instance = new LogicManager();
	}
	return instance;
}


void LogicManager::InitData()
{
	// Load textures
	texbkg = CORE_LoadPNG("data/circle-bkg-128.png", true);
	texsmallball = CORE_LoadPNG("data/tyrian_ball.png", false);

	
	// Init game state.
	for (int i = 0; i < NUM_BALLS; i++) {
		Entity* ball = new Entity(Global::Get()->GetBallJson(2));

		Global::Get()->AddBall(ball);
		RenderEngine::GetInstance()->AddSprite(Global::Get()->GetBalls()[i]
			->FindComponent<RenderComponent>()->GetSprite());
	}
	//Init Player
	Entity* player = new Entity("data/JSONFolder/PlayerJson.json");
	RenderEngine::GetInstance()->AddSprite(player->FindComponent<RenderComponent>()->GetSprite());
	Global::Get()->SetPlayer(player);
}
void LogicManager::ShutdownData()
{
	// Unload textures.
	CORE_UnloadPNG(texbkg);
	CORE_UnloadPNG(texsmallball);
}

void LogicManager::Update()
{
	//Time Logic
	timer.InitSlotsToProccess();

	while (timer.ProcessSlots()) {
		GameLogicFunction();
	}
	//SYS_Sleep(17);
}

void LogicManager::GameLogicFunction()
{
	HandleInputs();

	//Run Player
	if (Global::Get()->GetPlayer()) {
		Global::Get()->GetPlayer()->Update(timer.GetFixedTick());
	}
	//Run Bullet if is in game
	if (Global::Get()->GetBullet()) {
		Global::Get()->GetBullet()->Update(timer.GetFixedTick());
		//If bullet was stuck in wall for some time, dissapear
		if (!Global::Get()->GetBullet()->GetIsActive()) {
			Global::Get()->EraseBullet();
		}
	}
	// Run balls
	for (int i = 0; i < Global::Get()->GetBalls().size(); i++) {
		Global::Get()->GetBalls()[i]->Update(timer.GetFixedTick());
	}
}

void LogicManager::HandleInputs()
{
	//Press ESC to EXIT Game
	if ((GetAsyncKeyState(0x1B) & 0x8000) != 0) {
		WIN_bGottaQuit = true;
	}
	//Press I to Main Menu in Death Scene
	if (Global::Get()->GetCurrentLevel() == -1 && ((GetAsyncKeyState(0x49) & 0x8000) != 0)) {
		Global::Get()->ChangeLevel();
		//InitData();
	}
	if (Global::Get()->GetPlayer()) {
		//Press Enter to begin game
		if (Global::Get()->GetCurrentLevel() == 0 && ((GetAsyncKeyState(0x0D) & 0x8000) != 0)) {
			Global::Get()->ChangeLevel();
		}
		DisplacementComponent* playerDisplacement = Global::Get()->GetPlayer()->FindComponent<DisplacementComponent>();
		//Left Movement(A key)
		if ((GetAsyncKeyState(0x41) & 0x8000) != 0) {
			playerDisplacement->SetCanMoveLeft(true);
		}
		else {
			playerDisplacement->SetCanMoveLeft(false);
		}
		//Right Movement(D Key)
		if ((GetAsyncKeyState(0x44) & 0x8000) != 0) {
			playerDisplacement->SetCanMoveRight(true);
		}
		else {
			playerDisplacement->SetCanMoveRight(false);
		}
		//Up Movement(W Key)
		if ((GetAsyncKeyState(0x57) & 0x8000) != 0) {
			playerDisplacement->SetCanMoveUp(true);
		}
		else {
			playerDisplacement->SetCanMoveUp(false);
		}
		//Down Movement(S Key)
		if ((GetAsyncKeyState(0x53) & 0x8000) != 0) {
			playerDisplacement->SetCanMoveDown(true);
		}
		else {
			playerDisplacement->SetCanMoveDown(false);
		}
		//F Key to Spawn Bullet
		if (((GetAsyncKeyState(0x46) & 0x8000) != 0) && !Global::Get()->GetBullet() && !playerDisplacement->IsPlayerClimbing()) {
			Entity* bullet = new Entity("data/JSONFolder/BulletJson.json");
			bullet->FindComponent<DisplacementComponent>()->SetPos(playerDisplacement->GetPos());
			bullet->SetIsActive(true);
			playerDisplacement->SetIsShooting(true);

			RenderEngine::GetInstance()->SetBulletSprite(bullet->FindComponent<RenderComponent>()->GetSprite());
			Global::Get()->SetBullet(bullet);
		}
	}
}
