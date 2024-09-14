#pragma once
#include "CollisionMsg.h"
class LimitWorldCollMsg : public CollisionMsg
{
private:
	bool isInLimitWidth, isInLimitHeight;
public:
	bool IsInLimitWidth() { return isInLimitWidth; }
	bool IsInLimitHeight() { return isInLimitHeight; }
	void SetIsInLimit(bool isInLimitWidth, bool isInLimitHeight) 
	{ 
		this->isInLimitWidth = isInLimitWidth; 
		this->isInLimitHeight = isInLimitHeight;
	}
};

