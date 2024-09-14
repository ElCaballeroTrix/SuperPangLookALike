#pragma once
#include "Message.h"
class PlayerSpriteMsg : public Message
{
private:
	int playerSprite;
	float flipSprite;
public:
	void SetPlayerSprite(int playersprite) { this->playerSprite = playersprite; }
	int GetPlayerSprite() { return playerSprite; }
	void SetFlipSprite(float flipSprite) { this->flipSprite = flipSprite; }
	float GetFlipSprite() { return flipSprite; }
};
