#pragma once
#pragma message("Top in: " __FILE__)
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "Sprite.h"
#include "Global.h"
#include "Message.h"
#pragma message("Before class in: " __FILE__)
/*-------Entity-------
	Contains a list of components 
	with different functionality
*/
class Component;
class Entity
{
protected:
	std::vector<Component*> components;
	const char* jsonFile;
	bool isActive = false;
	std::string entityName;
	//Player variables
	bool gotHit = false;
public:
	//Constructor based on a json file
	Entity(const char* jsonFile);
	std::string GetEntityName() { return entityName; }
	void AddComponent(Component* component) { components.push_back(component); }

	//Finds a specific component from its list of components
	template<class T>
	T* FindComponent()
	{
		for (auto compIt = components.begin(); compIt != components.end(); ++compIt)
		{
			T* comp = dynamic_cast<T*>(*compIt);
			if (comp)
				return comp;
		}
		return NULL;
	}

	virtual void EstablishComponents(){}
	//Calls the update function of every component in its list
	virtual void Update(double elapsed);
	virtual void Activate(){}
	virtual void Deactivate(){}
	//Sends a message to all of its components
	//A component calls this method to update values 
	//needed by other components
	void SendAMessage(Message* msg);
	void SetIsActive(bool isActive) { this->isActive = isActive; }
	bool GetIsActive() { return isActive; }
	bool GotHit() { return gotHit; }
	void SetGotHit(bool gotHit) { this->gotHit = gotHit; }
	const char* GetJsonFile() { return jsonFile; }

};



