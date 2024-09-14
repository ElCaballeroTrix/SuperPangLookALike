#pragma once
#include "Component.h"
#include <vector>
/*-------RenderComponent-------
	A component that is in charge of the render
	of an entity
*/
class RenderComponent : public Component
{
private:
	GLuint gfx;	// OpenGL for id. for visualization purposes. 
	float  radius;	// Radius.
	Sprite* sprite; //Sprite for Render
	vec2 pos;
	//Player Sprites
	std::vector<GLuint> playerGFXs;
public:
	RenderComponent(Entity* entity)
		: Component(entity)
	{}
	void Update(double fixedTick) override;
	GLuint GetGfx() { return gfx; }
	void SetGfx(GLuint gfx) { this->gfx = gfx; }
	float GetRadius() { return radius; }
	void SetRadius(float radius) { this->radius = radius; }
	Sprite* GetSprite() { return sprite; }
	void CreateSprite(vec2 pos) { this->sprite = new Sprite(gfx, radius, pos); }
	void SetAPlayerGFX(GLuint playerGfx) { playerGFXs.push_back(playerGfx); }

	virtual void ReceiveMessage(Message* message) override;
};

