#pragma once
#pragma message("Top in: " __FILE__)
#include "Entity.h"
#pragma message("Before class in: " __FILE__)

/*-------Component-------
	A game object that represents a specific
	functionality of an entity
*/
class Entity;
class Component
{
protected:
	Entity* m_Owner = nullptr;
public:
	Component(Entity* entity )
	{
		this->m_Owner = entity;
	}
	virtual ~Component()
	{
		delete m_Owner;
		m_Owner = nullptr;
	}
	//The main functionality of a component
	virtual void Update(double fixedTick){}
	//Method to receive a message and therefore information needed
	//for its logic only obtainable from other components within 
	// the same entity
	virtual void ReceiveMessage(Message* message){}
};

