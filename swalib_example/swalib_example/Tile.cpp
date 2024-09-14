#include "Tile.h"

Tile::Tile(int identifier, GLuint texture, double xSpriteCoordinates, double ySpriteCoordinates, double sizePercentageX, double sizePercentageY, bool isStair, float width, float height, int isEndZone)
{
		this->identifier = identifier;
		this->texture = texture;
		this->xSpriteCoordinates = xSpriteCoordinates;
		this->ySpriteCoordinates = ySpriteCoordinates;
		this->sizePercentageX = sizePercentageX;
		this->sizePercentageY = sizePercentageY;
		this->isStair = isStair;
		this->width = width;
		this->height = height;
		this->isEndZone = isEndZone;
}

Tile::Tile(const Tile* obj)
{
	this->identifier = obj->identifier;
	this->texture = obj->texture;
	this->xSpriteCoordinates = obj->xSpriteCoordinates;
	this->ySpriteCoordinates = obj->ySpriteCoordinates;
	this->sizePercentageX = obj->sizePercentageX;
	this->sizePercentageY = obj->sizePercentageY;
	this->isStair = obj->isStair;
	this->width = obj->width;
	this->height = obj->height;
	this->isEndZone = obj->isEndZone;
}
