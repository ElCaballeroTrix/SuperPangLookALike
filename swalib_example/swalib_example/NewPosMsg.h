#pragma once
#include "Message.h"
#include "vector2d.h"
/*-------NewPosMsg-------
	A message that contains the new 
	position of an entity
*/
class NewPosMsg : public Message
{
private:
	vec2 newpos;
public:
	void SetNewPos(vec2 newpos) { this->newpos = newpos; }
	vec2 GetNewPos() { return newpos; }
};

