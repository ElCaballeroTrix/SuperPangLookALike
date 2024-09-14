#include "CollisionComponent.h"
#include "DisplacementComponent.h"
#include "EntCollisionMsg.h"
#include "LimitWorldCollMsg.h"
#include "NewPosMsg.h"
#include "LimitPlayerWorld.h"
#include "PlayerSpriteMsg.h"
#include "BulletSpriteMsg.h"
#include "PlatformCollMsg.h"
#include "Tile.h"
#include "StairCollMsg.h"

void CollisionComponent::Update(double fixedTick)
{
	collision = false;
	colliding_ball = -1;
	//Ball Collisions
	if (m_Owner->GetEntityName().compare("Ball") == 0) {
		//Ball hit player
		Entity* player = Global::Get()->GetPlayer();
		vec2 playerPos = Global::Get()->GetPlayer()->FindComponent<DisplacementComponent>()->GetPos();
		float playerRadius = Global::Get()->GetPlayer()->FindComponent<CollisionComponent>()->GetRadius();
		float limitPlayer = (radius / 2 + playerRadius) * (radius / 2 + playerRadius);
		if (vlen2(pos - playerPos) <= limitPlayer) {
			//When player is hit, notify him so that he can send a message to change sprite and then reset level
			player->SetGotHit(true);
		}


		//Platform Collision
		bool isInLimitPlatformLeft = false, isInLimitPlatformRight = false, isInLimitPlatformUpDown = false;
		std::vector<Tile*> platforms = Global::Get()->GetTiles();
		for (Tile* platform : platforms) {
			if (!platform->IsStair()) {
				int placeOfCollision = RectCirCollision(pos, radius, platform->GetPos(), platform->GetWidth(), platform->GetHeight());
				if (platform->IsEndZone() == -1 && placeOfCollision != -1) {
					//If ball collides with platform top or bottom side and is not a limit
					isInLimitPlatformUpDown = true;
					isInLimitPlatformRight = false;
					isInLimitPlatformLeft = false;
					break;
				}
				else if (platform->IsEndZone() == 0 && placeOfCollision == 2) {
					//If ball collides with platform top or bottom side and left side
					isInLimitPlatformUpDown = true;
					isInLimitPlatformLeft = true;
					isInLimitPlatformRight = false;
					break;
				}
				else if (platform->IsEndZone() == 1 && placeOfCollision == 3) {
					//If ball collides with platform top or bottom side and right side
					isInLimitPlatformUpDown = true;
					isInLimitPlatformRight = true;
					isInLimitPlatformLeft = false;
					break;

				}
				else if (platform->IsEndZone() == 0 && placeOfCollision == 0) {
					//If ball collides with platform left side
					isInLimitPlatformUpDown = false;
					isInLimitPlatformRight = false;
					isInLimitPlatformLeft = true;
					break;
				}
				else if (platform->IsEndZone() == 1 && placeOfCollision == 1) {
					//If ball collides with platform right side
					isInLimitPlatformUpDown = false;
					isInLimitPlatformRight = true;
					isInLimitPlatformLeft = false;
					break;
				}
			}
		}
		if (isInLimitPlatformLeft || isInLimitPlatformRight || isInLimitPlatformUpDown) {
			PlatformCollMsg* platformCollMsg = new PlatformCollMsg();
			platformCollMsg->SetPlatformLimits(isInLimitPlatformLeft, isInLimitPlatformRight, isInLimitPlatformUpDown);
			m_Owner->SendAMessage(platformCollMsg);
		}

		//Limit detection
		bool isInLimitWidth = false, isInLimitHeight = false;
		//16.f is the border thickness
		if (((pos.x + radius > SCR_WIDTH - 16.f) || (pos.x - radius < 16.f))) {
			isInLimitWidth = true;
		}
		if ((pos.y + radius > SCR_GAMEHEIGHT - 16.f) || (pos.y - radius < 16.f)) {
			isInLimitHeight = true;
			//If ball glitched and player can't hit it, destroy it
			if (pos.y <= 0.f) {
				Global::Get()->ExplodeBall(m_Owner);
			}
		}
		

		if (collision) {
			EntCollisionMsg* entCollmsg = new EntCollisionMsg();
			m_Owner->SendAMessage(entCollmsg);
		}

		if (isInLimitHeight || isInLimitWidth) {
			LimitWorldCollMsg* limitWorlCollmsg = new LimitWorldCollMsg();
			limitWorlCollmsg->SetIsInLimit(isInLimitWidth, isInLimitHeight);
			m_Owner->SendAMessage(limitWorlCollmsg);
		}
	}
	//---------------------
	//Player Collisions
	else if(m_Owner->GetEntityName().compare("Player") == 0) {
		//Limit detection
		bool isInLimitRight = false; bool isInLimitLeft = false; bool isInLimitDown = false;

		//16.f is the border thickness
		if (pos.x + radius > SCR_WIDTH - 16.f) {
			isInLimitRight = true;
		}
		if (pos.x - radius < 16.f) {
			isInLimitLeft = true;
		}
		if (pos.y <= 32.f) {
			isInLimitDown = true;
		}

		//Stair Detection
		bool playerIsInStairCanGoUp = false, playerIsInStairCanGoDown = false;
		bool stairDetected = false;
		bool playerAboveTile = false;
		std::vector<Tile*> platforms = Global::Get()->GetTiles();
		for (Tile* platform : platforms) {
			//Wider detection for platform ends and platform ends next to stairs
			//So that player can not fall of platforms but can still reach stairs
			bool collidingWithPlatform = RectRectCollision(pos, width, height, platform->GetPos(), platform->GetWidth(), platform->GetHeight());
			if (!playerAboveTile && collidingWithPlatform ) {
				playerAboveTile = true;
			}
			if (platform->IsStair()) {
				bool collidingWithStair = RectRectCollision(pos, width, height + 2.F, platform->GetPos(), platform->GetWidth(), platform->GetHeight());
				if(collidingWithPlatform){
					isInLimitRight = false;
					isInLimitLeft = false;
					playerIsInStairCanGoUp = true;
					playerIsInStairCanGoDown = true;
					break;
				}
				else if (collidingWithStair) {
					playerIsInStairCanGoUp = false;
					playerIsInStairCanGoDown = true;
				}
			}
		}
		//Limits
		LimitPlayerWorld* limitPlayerWorld = new LimitPlayerWorld();
		limitPlayerWorld->SetPlayerIsInLimit(isInLimitRight, isInLimitLeft, playerAboveTile);
		m_Owner->SendAMessage(limitPlayerWorld);

		StairCollMsg* stairCollMsg = new StairCollMsg();
		stairCollMsg->SetPlayerInStair(playerIsInStairCanGoUp, playerIsInStairCanGoDown);
		m_Owner->SendAMessage(stairCollMsg);
	}
	//---------------------
	//Bullet Collisions
	else if (m_Owner->GetEntityName().compare("Bullet") == 0) {
		height += 5;
		//Limit detection
		if ((pos.y > SCR_GAMEHEIGHT - 16.f)) {
			BulletSpriteMsg* bulletSpriteMsg = new BulletSpriteMsg();
			bulletSpriteMsg->SetIsBulletInLimit(true);
			m_Owner->SendAMessage(bulletSpriteMsg);
		}
		else {
			//Ball detection if bullet is not in limit or platform
			std::vector<Entity*> balls = Global::Get()->GetBalls();
			for (Entity* ball : balls)
			{
				if (RectCirCollision(	ball->FindComponent<CollisionComponent>()->GetPos(),
										ball->FindComponent<CollisionComponent>()->GetRadius(),
										pos, width, height) != -1) {
					m_Owner->SetIsActive(false);
					Global::Get()->ExplodeBall(ball);
				}
			}
			//Platform Collision
			std::vector<Tile*> platforms = Global::Get()->GetTiles();
			for (Tile* platform : platforms) {
				if (!platform->IsStair() && RectRectCollision(pos, width, height, platform->GetPos(), platform->GetWidth(), platform->GetHeight())) {
					BulletSpriteMsg* bulletSpriteMsg = new BulletSpriteMsg();
					bulletSpriteMsg->SetIsBulletInLimit(true);
					m_Owner->SendAMessage(bulletSpriteMsg);
				}
			}
		}	
	}
	//--------------
	
}

int CollisionComponent::RectCirCollision(vec2 cirPos, float cirRadius, vec2 rectPos, float rectWidth, float rectHeight)
{
	int returnValue = -1; //-1 = No collision, 0 = Left, 1 = Right, 2 or 3 = Up or Bottom 
	vec2 cirEntityPos = cirPos;
	float cirEntityRadius = cirRadius;

	float checkX = cirEntityPos.x;	//Which x edge of bullet to check for collision
	float checkY = cirEntityPos.y;	//Which y edge of bullet to check for collision
	if (cirEntityPos.x < rectPos.x - rectWidth) { //Left Edge of Bullet
		checkX = rectPos.x - rectWidth;
		returnValue = 0;
	}
	else if (cirEntityPos.x > rectPos.x + rectWidth) { //Right Edge of Bullet
		checkX = rectPos.x + rectWidth;
		returnValue = 1;
	}
	if (cirEntityPos.y > rectPos.y) { //Top Edge of Bullet
		checkY = rectPos.y;
		returnValue += 2;
	}
	else if (cirEntityPos.y < rectPos.y - rectHeight) { //Bottom Edge of Bullet
		checkY = rectPos.y - rectHeight;
		returnValue += 2;
	}
	//Check distance
	float distanceX = cirEntityPos.x - checkX;
	float distanceY = cirEntityPos.y - checkY;
	float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY));

	if (distance <= cirEntityRadius) {
		return returnValue;	
	}
	return -1;
}

bool CollisionComponent::RectRectCollision(vec2 rect1Pos, float rect1Width, float rect1Height, vec2 rect2Pos, float rect2Width, float rect2Height)
{
	if (rect1Pos.x + rect1Width >= rect2Pos.x &&	//Rect1 right edge past Rect2 left
		rect1Pos.x <= rect2Pos.x + rect2Width &&	//Rect1 left edge past Rect2 right
		rect1Pos.y - rect1Height <= rect2Pos.y &&	//Rect1 top edge past Rect2 bottom
		rect1Pos.y >= rect2Pos.y - rect2Height)		//Rect1 bottom edge past Rect2 top
	{
		return true;
	}
	return false;
}

void CollisionComponent::ReceiveMessage(Message* message)
{
	NewPosMsg* newPosMsg = dynamic_cast<NewPosMsg*>(message);
	if (newPosMsg) {
		pos = newPosMsg->GetNewPos();
	}
}
