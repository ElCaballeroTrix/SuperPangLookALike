#pragma once
#include "Message.h"
class PlatformCollMsg : public Message
{
private:
	bool leftPlatformLimit = false, rightPlatformLimit = false, upDownPlatformLimit = false;
public:
	void SetPlatformLimits(bool leftPlatformLimit, bool rightPlatformLimit, bool upDownPlatformLimit) {
		this->leftPlatformLimit = leftPlatformLimit;
		this->rightPlatformLimit = rightPlatformLimit;
		this->upDownPlatformLimit = upDownPlatformLimit;
	}
	bool IsLeftPlatformLimit() { return leftPlatformLimit; }
	bool IsRightPlatformLimit() { return rightPlatformLimit; }
	bool IsUpDownPlatformLimit() { return upDownPlatformLimit; }

};

