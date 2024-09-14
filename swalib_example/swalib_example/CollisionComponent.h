#pragma once
#include "Component.h"
/*-------CollisionComponent-------
	A component that detects the collision
	with other balls and limits of the scene
*/
class CollisionComponent : public Component
{
private:
	vec2   pos;	// Position.
	vec2 newpos;
	float  radius;	// Radius.
	bool collision;		//If ball is colliding
	int colliding_ball;	//Colliding ball
	//Width and height for rectangular collisions
	float width;		
	float height;
	//Private function for detecting collision between a circle and a rectangle and if it needs to change velocity on x or y
	int RectCirCollision(vec2 cirPos, float cirRadius, vec2 rectPos, float rectWidth, float rectHeight);
	//Detects if the is a collision rectangle with rectangle 
	bool RectRectCollision(vec2 rect1Pos, float rect1Width, float rect1Height, vec2 rect2Pos, float rect2Width, float rect2Height);
public:
	CollisionComponent(Entity* entity)
		: Component(entity)   
	{
		collision = false;
		colliding_ball = -1;
	}
	void Update(double fixedTick) override;
	vec2 GetPos() { return pos; }
	void SetPos(vec2 pos) { this->pos = pos; newpos = pos; }
	float GetRadius() { return radius; }
	void SetRadius(float radius) { this->radius = radius; }
	void SetWidth(float width) { this->width = width; }
	void SetHeight(float height) { this->height = height; }
	bool GetCollision() { return collision; }
	int GetCollidingBall() { return colliding_ball; }

	virtual void ReceiveMessage(Message* message) override;
};

