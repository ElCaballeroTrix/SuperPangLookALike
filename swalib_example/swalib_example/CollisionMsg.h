#pragma once
#include "Message.h"
#include "vector2d.h"
/*-------CollisionMsg-------
	A message that contains if
	an entity has collided
	with another
*/
class CollisionMsg : public Message
{
private:
	bool collision;
	vec2 position;
public:
	bool GetCollision() { return collision; }
	void SetCollision(bool collision) { this->collision = collision; }
	vec2 GetPosition() { return position; }
	void SetPosition(vec2 position) { this->position = position; }
};

