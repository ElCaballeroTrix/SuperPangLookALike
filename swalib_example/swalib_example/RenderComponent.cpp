#include "RenderComponent.h"
#include "NewPosMsg.h"
#include "PlayerSpriteMsg.h"
#include "BulletSpriteMsg.h"

void RenderComponent::Update(double fixedTick)
{
	//Update Sprite
	sprite->SetGfx(gfx);
	sprite->SetRadius(radius);
}

void RenderComponent::ReceiveMessage(Message* message)
{
	NewPosMsg* newPosMsg = dynamic_cast<NewPosMsg*>(message);
	if (newPosMsg) {
		sprite->SetPos(newPosMsg->GetNewPos());
	}

	PlayerSpriteMsg* playerSpriteMsg = dynamic_cast<PlayerSpriteMsg*>(message);
	if (playerSpriteMsg) {
		int playerSprite = playerSpriteMsg->GetPlayerSprite();
		gfx = playerGFXs[playerSprite];
		sprite->SetFlipSprite(playerSpriteMsg->GetFlipSprite());	
	}

	BulletSpriteMsg* bulletSpriteMsg = dynamic_cast<BulletSpriteMsg*>(message);
	if (bulletSpriteMsg) {
		if (m_Owner->GetEntityName() == "Bullet") {
			gfx = CORE_LoadPNG("data/BulletStuck.png", false);
		}
	}
	
}