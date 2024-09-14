#pragma once
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
/*-------Sprite-------
	Class used by RenderManager to paint
	a certain game object in scene
*/
class Sprite
{
private:
	GLuint gfx;			// OpenGL for id. for visualization purposes. 
	float  radius;		// Radius.
	vec2 pos;			// Position.
	float flip = 1.f;	// To flip the sprite (1 no flip, -1 flip)
	double xSpriteCoordinates = 0.0;	//X coordinates for a sprite inside a SpriteSheet
	double ySpriteCoordinates = 0.0;	//Y coordinates for a sprite inside a SpriteSheet
	double sizePercentageX = 1.0;		//Size of sprite X in spritesheet in percentage
	double sizePercentageY = 1.0;		//Size of sprite Y in spritesheet in percentage
	int bulletHeight = 0;				//Used for showing correctly the bullet 
public:
	Sprite(){}
	Sprite(GLuint gfx, float radius, vec2 pos, double xSpriteCoordinates = 0.0, double ySpriteCoordinates = 0.0, double sizePercentageX = 1.0, double sizePercentageY = 0.0) {
		this->gfx = gfx;
		this->radius = radius;
		this->pos = pos;
		this->xSpriteCoordinates = xSpriteCoordinates;
		this->ySpriteCoordinates = ySpriteCoordinates;
		this->sizePercentageX = sizePercentageX;
		this->sizePercentageY = sizePercentageY;
	}
	GLuint GetGfx() { return gfx; }
	void SetGfx(GLuint gfx) { this->gfx = gfx; }
	float GetRadius() { return radius; }
	void SetRadius(float radius) { this->radius = radius; }
	vec2 GetPos() { return pos; }
	void SetPos(vec2 pos) { this->pos = pos; }
	void SetFlipSprite(float flip) { this->flip = flip; }
	float GetFlipSprite() { return flip; }
	double GetXSpriteCoordinates() { return xSpriteCoordinates; }
	double GetYSpriteCoordinates() { return ySpriteCoordinates; }
	double GetSizePercentageX() { return sizePercentageX; }
	double GetSizePercentageY() { return sizePercentageY; }
	//In each frame, the bullet turns taller to form the bullet trace
	double GetBulletHeight() { 
		if (bulletHeight < 380) {
			bulletHeight += 5;
		}
		return bulletHeight; 
	}
};

