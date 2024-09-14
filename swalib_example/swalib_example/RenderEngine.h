#pragma once
#include <vector>
#include "Sprite.h"
/*-------RenderManager-------
	A manager in charge of the game render.
	It initializes and shutdowns all render
*/
class RenderEngine
{
private:
	static RenderEngine* instance;
	std::vector<Sprite*> sprites;
	std::vector<Sprite*> tileSprites;
	Sprite* bulletSprite;
	RenderEngine();
	float ole = 5.f; //Borrar
public:
	//Initializesall render
	void InitRender();
	//Shutdowns all render
	void ShutdownRender();
	std::vector<Sprite*> GetSprites() { return sprites; }
	void AddSprite(Sprite* newSprite) { sprites.push_back(newSprite); }
	void RemoveSprites() { sprites.clear(); }
	void RemoveASprite(Sprite* spriteToBeRemoved);
	void AddTileSprite(Sprite* newSprite) { tileSprites.push_back(newSprite); }
	void RemoveTileSprites() { tileSprites.clear(); }
	void SetBulletSprite(Sprite* bulletSprite) { this->bulletSprite = bulletSprite; }
	void RemoveBulletSprite() { delete bulletSprite; bulletSprite = nullptr; }
	static RenderEngine* GetInstance();
	//Main render function that updates the render each frame
	void GameRenderFunction();
};

