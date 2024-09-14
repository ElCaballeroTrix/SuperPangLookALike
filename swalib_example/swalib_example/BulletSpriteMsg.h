#pragma once
#include "Message.h"
class BulletSpriteMsg : public Message
{
private:
	bool isBulletInLimit = false;
public:
	void SetIsBulletInLimit(bool isBulletInLimit) { this->isBulletInLimit = isBulletInLimit; }
	bool GetIsBulletInLimit() { return isBulletInLimit; }
};

