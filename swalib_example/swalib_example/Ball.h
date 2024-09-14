#pragma once
#include "Entity.h"
#include "CollisionComponent.h"
#include "DisplacementComponent.h"
#include "RenderComponent.h"

//const unsigned int NUM_BALLS = 10;	// Max. num balls.

//const float MAX_BALL_SPEED = 480.f;	// Max vel. of ball. (pixels/?).

class Ball : public Entity
{
private:
	vec2   pos;	// Position.
	vec2   vel;	// Velocity.
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	float  radius;	// Radius.
	CollisionComponent* collisionComponent = nullptr;
	DisplacementComponent* displacementComponent = nullptr;
	RenderComponent* renderComponent = nullptr;
public:
	/*Ball() :
		pos(0.0f),
		vel(0.0f),
		gfx(0),
		radius(0.0f)
	{}
	vec2 GetPos() { return pos; }
	void SetPos(vec2 pos) { this->pos = pos; }
	vec2 GetVel() { return vel; }
	void SetVel(vec2 vel) { this->vel = vel; }
	GLuint GetGfx() { return gfx; }
	void SetGfx(GLuint gfx) { this->gfx = gfx; }
	float GetRadius() { return radius; }
	void SetRadius(float radius) { this->radius = radius; }
	void Slot(std::vector<Ball*> balls, int i);
	Sprite* GetSprite() { return sprite; }
	void CreateSprite() { this->sprite = new Sprite(gfx, radius, pos); }*/
	//Ball(){}
	

	void EstablishComponents() override
	{
		collisionComponent = new CollisionComponent(this);
		collisionComponent->SetPos(pos);
		//collisionComponent->SetVel(vel);
		collisionComponent->SetRadius(radius);

		displacementComponent = new DisplacementComponent(this);
		displacementComponent->SetPos(pos);
		displacementComponent->SetVel(vel);

		renderComponent = new RenderComponent(this);
		renderComponent->SetGfx(gfx);
		renderComponent->SetRadius(radius);
		renderComponent->CreateSprite(pos);

		AddComponent(collisionComponent);
		AddComponent(displacementComponent);
		AddComponent(renderComponent);
	}
	vec2 GetPos() { return pos; }
	void SetPos(vec2 pos) { this->pos = pos; }
	vec2 GetVel() { return vel; }
	void SetVel(vec2 vel) { this->vel = vel; }
	GLuint GetGfx() { return gfx; }
	void SetGfx(GLuint gfx) { this->gfx = gfx; }
	float GetRadius() { return radius; }
	void SetRadius(float radius) { this->radius = radius; }
};

