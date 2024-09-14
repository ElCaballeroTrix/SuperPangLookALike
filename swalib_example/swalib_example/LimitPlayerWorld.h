#pragma once
#include "Message.h"
class LimitPlayerWorld : public Message
{
private:
	bool isPlayerInLimitRight = false, isPlayerInLimitLeft = false, isPlayerInHeightLimit = false;
public:
	bool IsPlayerInLimitRight() { return isPlayerInLimitRight; }
	bool IsPlayerInLimitLeft() { return isPlayerInLimitLeft; }
	bool IsPlayerInHeightLimit() { return isPlayerInHeightLimit; }
	void SetPlayerIsInLimit(bool isPlayerInLimitRight, bool isPlayerInLimitLeft, bool isPlayerInHeightLimit)
	{
		this->isPlayerInLimitRight = isPlayerInLimitRight;
		this->isPlayerInLimitLeft = isPlayerInLimitLeft;
		this->isPlayerInHeightLimit = isPlayerInHeightLimit;
	}
};

