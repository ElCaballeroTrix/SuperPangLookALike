#pragma once
#include "Message.h"
class StairCollMsg : public Message
{
private:
	bool playerIsInStairCanGoUp = false, playerIsInStairCanGoDown = false;
public:
	void SetPlayerInStair(bool playerIsInStairCanGoUp, bool playerIsInStairCanGoDown) {
		this->playerIsInStairCanGoUp = playerIsInStairCanGoUp; 
		this->playerIsInStairCanGoDown = playerIsInStairCanGoDown;
	}
	bool IsPlayerInStairCanGoUp() { return playerIsInStairCanGoUp; }
	bool IsPlayerInStairCanGoDown() { return playerIsInStairCanGoDown; }
};

