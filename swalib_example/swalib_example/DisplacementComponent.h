#pragma once
#pragma message("Top in: " __FILE__)
#include "Component.h"
#pragma message("Before class in: " __FILE__)
/*-------DisplacementComponent-------
	A component that updates the position of 
	an entity
*/
class DisplacementComponent : public Component
{
private:
	vec2   pos;	// Position.
	vec2   vel;	// Velocity.
	float   maxVelY = 252.f;
	float gravity = -200.0f;
	vec2 newpos;
	bool isInLimitWidth = false; 
	bool isInLimitHeight = false;
	//Player variables
	bool canMoveLeft = false, canMoveRight = false;
	bool canMoveUp = false, canMoveDown = false;
	bool isPlayerInLimitRight = false, isPlayerInLimitLeft = false, playerNoFall = false;
	float playerSprite = 0; //PlayerSprite to change to
	float flipPlayerSprite = 1.f; //Flip player sprite or not
	bool isShooting = false;
	bool playerCanClimbStairUp = false, playerCanClimbStairDown = false;
	bool playerClimbing = false;
	//Bullet variables
	float bulletTimeInWall = 0; //Time the bullet is stuck in wall
public:
	DisplacementComponent(Entity* entity)
		: Component(entity)
	{}
	void Update(double fixedTick) override;
	vec2 GetPos() { return pos; }
	void SetPos(vec2 pos) { this->pos = pos; }
	vec2 GetVel() { return vel; }
	void SetVel(vec2 vel) { this->vel = vel; }
	void SetCanMoveLeft(bool canMoveLeft) { this->canMoveLeft = canMoveLeft; }
	void SetCanMoveRight(bool canMoveRight) { this->canMoveRight = canMoveRight; }
	void SetCanMoveUp(bool canMoveUp) { this->canMoveUp = canMoveUp; }
	void SetCanMoveDown(bool canMoveDown) { this->canMoveDown = canMoveDown; }
	void SetIsShooting(bool isShooting) { this->isShooting = isShooting; }
	bool IsPlayerClimbing() { return playerClimbing; }

	virtual void ReceiveMessage(Message* message) override;
};

