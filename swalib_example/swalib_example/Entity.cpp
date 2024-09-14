#include "Entity.h"
#include "Component.h"
#include "CollisionComponent.h"
#include "DisplacementComponent.h"
#include "RenderComponent.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
using namespace rapidjson;

Entity::Entity(const char* jsonFile)
{
	this->jsonFile = jsonFile;
	//Read JSON
	FILE* fp = fopen(jsonFile, "rb");
	char readBuffer[65536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document document;
	document.ParseStream(is);
	fclose(fp);
	//--------------------
	//Interpret JSON
	entityName = document["Entity"].GetString();
	vec2 maxPos = vec2(document["pos"].FindMember("x")->value.GetFloat(),
				document["pos"].FindMember("y")->value.GetFloat());
	vec2 maxVel = vec2(document["vel"].FindMember("x")->value.GetFloat(),
				document["vel"].FindMember("y")->value.GetFloat());
	float radius = document["radius"].GetFloat();
	vec2 pos, vel;
	pos = maxPos;
	vel = vec2(maxVel.x, maxVel.y);
	//-----------------------

	CollisionComponent* collisionComponent = new CollisionComponent(this);
	collisionComponent->SetPos(pos);
	collisionComponent->SetRadius(radius);
	collisionComponent->SetWidth(document["width"].GetFloat());
	collisionComponent->SetHeight(document["height"].GetFloat());

	DisplacementComponent* displacementComponent = new DisplacementComponent(this);
	displacementComponent->SetPos(pos);
	displacementComponent->SetVel(vel);

	RenderComponent* renderComponent = new RenderComponent(this);
	renderComponent->SetRadius(radius);
	renderComponent->SetGfx(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx")->value.GetString(), false));
	renderComponent->CreateSprite(pos);
	//Load All Player Sprites
	if (entityName == "Player") {
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx1")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx2")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx3")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx4")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx5")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx6")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx7")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx8")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx9")->value.GetString(), false));
		renderComponent->SetAPlayerGFX(CORE_LoadPNG(document["RenderComponent"].FindMember("gfx10")->value.GetString(), false));
	}

	AddComponent(displacementComponent);
	AddComponent(collisionComponent);	
	AddComponent(renderComponent);
}

void Entity::Update(double elapsed)
{
	if (isActive) {
		for (auto compIt = components.begin();
			compIt != components.end();
			++compIt)
		{
			if (isActive) {
				(*compIt)->Update(elapsed);
			}
		}
	}
}

void Entity::SendAMessage(Message* msg)
{
	if (isActive) {
		for (auto compIt = components.begin();
			compIt != components.end();
			++compIt)
		{
			(*compIt)->ReceiveMessage(msg);
		}
	}
}