#pragma once
#include "CollisionMsg.h"
#include "Entity.h"
/*-------EntCollisionMsg-------
	A message that contains the 
	colliding entity of an entity
	if it is colliding.
*/
class EntCollisionMsg : public CollisionMsg
{
private:
	Entity* collidingEntity;
public:
	Entity* GetCollidingEntity() { return collidingEntity; }
	void SetCollidingEntity(Entity* collidingEntity) {
		this->collidingEntity = collidingEntity;
	}
};

