#pragma once
#include "stdafx.h"
#include "core.h"
#include "vector2d.h"
class Tile
{
private:
	int identifier;
	GLuint texture;
	vec2 pos = vec2(0,0);
	float width = 4;
	float height = 4;
	bool isStair = false;		//If it is a stair, the ball or bullet won't collide with it
	int isEndZone = -1;			//If tile is one of the right/down or left/up edges of a platform, -1 = no, 0 = left, 1 = right
	double xSpriteCoordinates = 0.0;
	double ySpriteCoordinates = 0.0;
	double sizePercentageX = 1.0;
	double sizePercentageY = 1.0;
public:
	Tile(int identifier, GLuint texture, double xSpriteCoordinates = 0.0, double ySpriteCoordinates = 0.0, double sizePercentageX = 1.0, double sizePercentageY = 1.0, bool isStair = false, float width = 16, float height = 16, int isEndZone = -1);
	Tile(const Tile*); //Copy constructor
	int GetIdentifier() { return identifier; }
	GLuint GetTexture() { return texture; }
	double GetXSpriteCoordinates() { return xSpriteCoordinates; }
	double GetYSpriteCoordinates() { return ySpriteCoordinates; }
	double GetSizePercentageX() { return sizePercentageX; }
	double GetSizePercentageY() { return sizePercentageY; }
	bool IsStair() { return isStair; }
	void SetPos(vec2 pos) { this->pos = pos;  }
	vec2 GetPos() { return pos; }
	float GetWidth() { return width; }
	float GetHeight() { return height; }
	int IsEndZone() { return isEndZone; }
};

