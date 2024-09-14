#include "DisplacementComponent.h"
#include "NewPosMsg.h"
#include "LimitWorldCollMsg.h"
#include "EntCollisionMsg.h"
#include "LimitPlayerWorld.h"
#include "PlayerSpriteMsg.h"
#include "BulletSpriteMsg.h"
#include "PlatformCollMsg.h"
#include "StairCollMsg.h"
#include <cmath>

void DisplacementComponent::Update(double fixedTick)
{
	if (m_Owner->GetEntityName().compare("Ball") == 0) {
		vel.y = vel.y + gravity * fixedTick;
		newpos = pos + vel * fixedTick ;
		pos = newpos;
	}
	else if (m_Owner->GetEntityName().compare("Bullet") == 0) {
		//If Bullet Stuck in Wall, after sometime, dissapear
		if (vel.y == 0) {
			bulletTimeInWall += fixedTick * 2.f;
			if (bulletTimeInWall >= 2) {
				m_Owner->SetIsActive(false);
			}
		}
		else {
			newpos = pos + vel * fixedTick;
			pos = newpos;
		}
	}
	else if (m_Owner->GetEntityName().compare("Player") == 0) {
		bool playerIsFalling = false;
		//Player Falling
		if (!playerNoFall && pos.y > 32.f) {
			newpos.y = pos.y - vel.y * fixedTick;
			pos.y = newpos.y;
			playerIsFalling = true;
		}
		//Player Movement
		if (!playerCanClimbStairUp) {
			playerClimbing = false;
		}
		if (!isShooting) {
			//Left Movement(A Key)
			if (canMoveLeft && !isPlayerInLimitLeft && !playerClimbing) {
				isPlayerInLimitRight = false;
				newpos.x = pos.x - vel.x * fixedTick;
				pos.x = newpos.x;
				playerSprite += fixedTick * 10.0f;
				if (playerSprite >= 4) { //Clamp
					playerSprite = 0;
				}
				flipPlayerSprite = 1.f;
			}
			//Right Movement(D Key)
			else if (canMoveRight && !isPlayerInLimitRight && !playerClimbing) {
				isPlayerInLimitLeft = false;
				newpos.x = pos.x + vel.x * fixedTick;
				pos.x = newpos.x;
				playerSprite += fixedTick * 10.0f;
				if (playerSprite >= 4) { //Clamp
					playerSprite = 0;
				}
				flipPlayerSprite = -1.f;
			}
			else if (playerCanClimbStairUp && canMoveUp) {
				playerClimbing = true;
				newpos.y = pos.y + vel.y * fixedTick;
				pos.y = newpos.y;
				playerSprite += fixedTick * 10.0f;
				if (playerSprite < 9 || playerSprite >= 11) {
					playerSprite = 9;
				}
			}
			else if (playerCanClimbStairDown && canMoveDown) {
				if (pos.y <= 32.f) {
					pos.y = 32.f;
					playerCanClimbStairDown = false;
					playerClimbing = false;
				}
				else {
					playerClimbing = true;
					newpos.y = pos.y - vel.y * fixedTick;
					pos.y = newpos.y;
					playerSprite += fixedTick * 10.0f;
					if (playerSprite < 9 || playerSprite >= 11) {
						playerSprite = 9;
					}
				}
			}
			else if (playerClimbing) {
				//Climbing Idle
				playerSprite = 8;
			}
			else{ //Idle
				playerSprite = 4;
			}
		}
		else {
			if (playerSprite < 4 || playerSprite >= 6) {
				playerSprite = 4;
			}
			playerSprite += fixedTick * 10.0f;
			if (playerSprite >= 6) { //Clamp
				playerSprite = 4;
				isShooting = false;
			}
		}
		if (m_Owner->GotHit()) {
			playerSprite = 6;  //Change to hit sprite when damaged and reset level
			Global::Get()->SetNeedsReset(true);
		}
		PlayerSpriteMsg* playerSpriteMsg = new PlayerSpriteMsg();
		playerSpriteMsg->SetPlayerSprite(playerSprite);
		playerSpriteMsg->SetFlipSprite(flipPlayerSprite);
		m_Owner->SendAMessage(playerSpriteMsg);
	}
	//-----------------

	//Messages
	NewPosMsg* newPosmsg = new NewPosMsg();
	newPosmsg->SetNewPos(pos);
	m_Owner->SendAMessage(newPosmsg);
}

void DisplacementComponent::ReceiveMessage(Message* message)
{
	EntCollisionMsg* entCollmsg = dynamic_cast<EntCollisionMsg*>(message);
	if (entCollmsg) {
		vel = vel * -1.f;
	}
	
	PlatformCollMsg* platformCollMsg = dynamic_cast<PlatformCollMsg*>(message);
	if (platformCollMsg) {
		bool leftPlatformLimit = platformCollMsg->IsLeftPlatformLimit();
		bool rightPlatformLimit = platformCollMsg->IsRightPlatformLimit();
		bool upDownPlatformLimit = platformCollMsg->IsUpDownPlatformLimit();
		if (vel.x > 0 && leftPlatformLimit) {
			vel = vec2(GetVel().x * -1.0f, GetVel().y);
		}
		else if (vel.x <= 0 && rightPlatformLimit) {
			vel = vec2(GetVel().x * -1.0f, GetVel().y);
		}
		if (upDownPlatformLimit) {
			vel = vec2(GetVel().x, GetVel().y * -1.0f);
		}
	}
	LimitWorldCollMsg* limitWorlCollmsg = dynamic_cast<LimitWorldCollMsg*>(message);
	if (limitWorlCollmsg) {
		isInLimitWidth = limitWorlCollmsg->IsInLimitWidth();
		isInLimitHeight = limitWorlCollmsg->IsInLimitHeight();
		if (isInLimitWidth) {
			vel = vec2(GetVel().x * -1.0f, GetVel().y);
		}
		if (isInLimitHeight) {
			if (vel.y > 0) {
				vel = vec2(GetVel().x, maxVelY * -1.0f);
			}
			else {
				vel = vec2(GetVel().x, -maxVelY * -1.0f);
			}
		}
	}
	LimitPlayerWorld* limitPlayerWorld = dynamic_cast<LimitPlayerWorld*>(message);
	if (limitPlayerWorld) {
		if (limitPlayerWorld->IsPlayerInLimitRight()) {
			isPlayerInLimitRight = true;
		}
		if (limitPlayerWorld->IsPlayerInLimitLeft()) {
			isPlayerInLimitLeft = true;
		}
		playerNoFall = limitPlayerWorld->IsPlayerInHeightLimit();
	}
	StairCollMsg* stairCollMsg = dynamic_cast<StairCollMsg*>(message);
	if (stairCollMsg) {
		playerCanClimbStairUp = stairCollMsg->IsPlayerInStairCanGoUp();
		playerCanClimbStairDown = stairCollMsg->IsPlayerInStairCanGoDown();
	}

	BulletSpriteMsg* bulletSpriteMsg = dynamic_cast<BulletSpriteMsg*>(message);
	if (bulletSpriteMsg) {
		vel = vec2(0, 0);
	}

}
