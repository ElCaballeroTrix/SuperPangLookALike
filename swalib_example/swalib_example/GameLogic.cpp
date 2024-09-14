#include "GameLogic.h"
#include "Timer.h"
#include "LogicManager.h"

//*******************************************
//Previous functions for logic
//*******************************************

//LARGE_INTEGER frequency, previousTime, currentTime;
//double fixedTick = 1.0 / 60.0;
//double spiralOfDeath = 1.0 / 15.0;
//double elapsed = 0;
//double fpsCount = 0;
//double actualTime = 0;
//double getTime = 0;
//double logicTime = 0;
//extern Ball balls[NUM_BALLS];
//extern Timer timer;
//void TimeLogic() {
	//Time Logic
	/*QueryPerformanceCounter(&currentTime);
	getTime = (static_cast<double>(currentTime.QuadPart) - static_cast<double>(previousTime.QuadPart)) / static_cast<double>(frequency.QuadPart);
	previousTime = currentTime;


	actualTime += getTime;
	elapsed += getTime;
	
	if (elapsed >= spiralOfDeath) {
		elapsed = spiralOfDeath;
	}*/
	//LogicManager::GetInstance()->GetTimer().InitSlotsToProccess();
	
	//while (LogicManager::GetInstance()->GetTimer().ProcessSlots()) {
		//logicTime += fixedTick;
		//GameLogicFunction(); 
		
		//fpsCount = elapsed;
		//elapsed = elapsed - fixedTick;
	//}
	//SYS_Sleep(17);
//}

//void GameLogicFunction() {
	// Run balls
	//for (int i = 0; i < NUM_BALLS; i++) {
	//	// New Pos.
	//	//vec2 newpos = balls[i].pos + balls[i].vel;
	//	vec2 newpos = LogicManager::GetInstance()->GetBalls()[i]->GetPos() + LogicManager::GetInstance()->GetBalls()[i]->GetVel();

	//	// Collision detection.
	//	bool collision = false;
	//	int colliding_ball = -1;
	//	for (int j = 0; j < NUM_BALLS; j++) {
	//		if (i != j) {
	//			//float limit2 = (balls[i].radius + balls[j].radius) * (balls[i].radius + balls[j].radius);
	//			float limit2 = (LogicManager::GetInstance()->GetBalls()[i]->GetRadius() + LogicManager::GetInstance()->GetBalls()[j]->GetRadius()) * (LogicManager::GetInstance()->GetBalls()[i]->GetRadius() + LogicManager::GetInstance()->GetBalls()[j]->GetRadius());
	//			//if (vlen2(newpos - balls[j].pos) <= limit2) {
	//			if (vlen2(newpos - LogicManager::GetInstance()->GetBalls()[j]->GetPos()) <= limit2) {
	//				collision = true;
	//				colliding_ball = j;
	//				break;
	//			}
	//		}
	//	}
	//	LogicManager::GetInstance()->GetBalls()[i]->Slot(LogicManager::GetInstance()->GetBalls(), i);
		//if (!collision) {
		//	//balls[i].pos = newpos;
		//	balls[i].SetPos(newpos);
		//}
		//else {
		//	// Rebound!
		//	//balls[i].vel = balls[i].vel * -1.f ;
		//	balls[i].SetVel(balls[i].GetVel() * -1.f);
		//	//balls[colliding_ball].vel = balls[colliding_ball].vel * -1.f;
		//	balls[colliding_ball].SetVel(balls[colliding_ball].GetVel() * -1.f);
		//}

		//// Rebound on margins.
		////if ((balls[i].pos.x > SCR_WIDTH) || (balls[i].pos.x < 0)) {
		//if ((balls[i].GetPos().x > SCR_WIDTH) || (balls[i].GetPos().x < 0)) {
		//	//balls[i].vel.x *= -1.0;
		//	balls[i].SetVel(vec2( balls[i].GetVel().x * -1.0f, balls[i].GetVel().y));
		//}
		////if ((balls[i].pos.y > SCR_HEIGHT) || (balls[i].pos.y < 0)) {
		//if ((balls[i].GetPos().y > SCR_HEIGHT) || (balls[i].GetPos().y < 0)) {
		//	//[i].vel.y *= -1.0;
		//	balls[i].SetVel(vec2(balls[i].GetVel().x, balls[i].GetVel().y * -1.0f));
		//}
	//}
//}