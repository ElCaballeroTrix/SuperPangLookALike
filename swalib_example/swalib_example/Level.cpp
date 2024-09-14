#include "Level.h"
#include "Sprite.h"
#include "Tile.h"
#include "Global.h"
#include "RenderEngine.h"
#include "vector2d.h"
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
using namespace rapidjson;

void Level::ChangeLevel()
{
	++currentLevel;
	if (currentLevel != 0) {
		ReadLevel();
	}
}


void Level::ReadLevel()
{
	FILE* fp = nullptr;
	if (currentLevel == 1){
		fp = fopen(leve1Json, "rb");	
	}

	if (currentLevel == 2) {
		fp = fopen(leve2Json, "rb");
		RenderEngine::GetInstance()->RemoveTileSprites();
	}
	char readBuffer[40536];
	FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	Document document = nullptr;
	document.ParseStream(is);
	fclose(fp);
	const Value& tilesetArray = document["layers"][0].FindMember("data")->value;
	for (unsigned int i = 0; i < tilesetArray.Size(); i++)
	{
		if (tilesetArray[i].GetInt() != 0) {
			int ty = tilesetArray[i].GetInt();
			Tile* tile = new Tile(Global::Get()->GetAnInitialTile(tilesetArray[i].GetInt()));
			int y = i / width;
			int x = i - y * width;
			vec2 tilePos = vec2(x * 16.f, SCR_GAMEHEIGHT - y  * 16.f);
			tile->SetPos(tilePos);
			Global::Get()->AddTile(tile);
			Sprite* tileSprite = new Sprite(tile->GetTexture(), 8.f, tilePos, tile->GetXSpriteCoordinates(), tile->GetYSpriteCoordinates(), tile->GetSizePercentageX(), tile->GetSizePercentageY());
			RenderEngine::GetInstance()->AddTileSprite(tileSprite);
		}
	}
}


