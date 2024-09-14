#pragma once
#include <vector>
#include "stdafx.h"
#include "sys.h"
#include "core.h"
#include "font.h"
#include "vector2d.h"
#include "Level.h"
const unsigned int NUM_BALLS = 1;	// Max. num balls.
const float MAX_BALL_SPEED = 480.f;	// Max vel. of ball. (pixels/?).

/*-------Global-------
	Contains information used globaly
*/
extern bool WIN_bGottaQuit;
class Entity;
class Tile;
class Global
{
private:
	static Global* instance;
	std::vector<Entity*> balls;
	const char* ballJSons[3] = { "data/JSONFolder/BallGreenJson.json", "data/JSONFolder/BallBlueJson.json", "data/JSONFolder/BallRedJson.json" };
	float smallestBallRadius = 4.0f; 
	Entity* player;
	int playerHP = 3;
	GLuint playerHPAvatar;
	GLuint victoryPlayerSprite = CORE_LoadPNG("data/Player/Player7.png", false);
	Entity* bullet = nullptr;
	GLuint background;
	const std::vector<char*> backgrounds = { "data/Title.png", "data/Barcelona.png","data/Athens.png", "data/Victoria.png", "data/Derrota.png" };
	unsigned int backgroundIndex = 0;
	GLuint backgroundBorder;
	std::vector<Tile*> initialTiles; //Contains all the tilesets that in the game
	std::vector<Tile*> tiles;		 //Contains the tileset in a level with its position
	Level* level;
	bool victory = false;			//Game Finished with Victory
	Global()
	{
		background = CORE_LoadPNG(backgrounds[0], true);
		level = new Level();
		playerHPAvatar = CORE_LoadPNG("data/Player/PlayerHP.png", false);
		backgroundBorder = CORE_LoadPNG("data/Border.png", true);
	}
	bool levelComplete = false;
	bool needsReset = false;
	bool needsToChangeLevel = false;
public:
	~Global();
	static Global* Get();
	std::vector<Entity*> GetBalls() { return balls; }
	void AddBall(Entity* newEntity) { balls.push_back(newEntity); }
	const char* GetBallJson(int i) { return ballJSons[i]; }
	bool IsLevelCompleted() { return levelComplete; }
	void SetLevelComplete(bool isLevelCompleted) { levelComplete = isLevelCompleted; }
	GLuint GetBackground() { return background; }
	GLuint GetBackgroundBorder() { return backgroundBorder; }
	bool GetNeedsToChangeLevel() { return needsToChangeLevel; }
	//Changes the current level for the next one
	void ChangeLevel();
	//Function that initializes all tile textures
	void InitializeTiles();
	//Returns the tile with the identifier param
	Tile* GetAnInitialTile(int identifier);
	void AddTile(Tile* tile) { tiles.push_back(tile); }
	std::vector<Tile*> GetTiles() { return tiles; }
	void SetPlayer(Entity* player) { this->player = player; }
	Entity* GetPlayer() { return player; }
	void SetBullet(Entity* bullet) { this->bullet = bullet; }
	Entity* GetBullet() { return bullet; }
	//Eliminates de bullet in game
	void EraseBullet();
	int GetCurrentLevel() { return level->GetCurrentLevel(); }
	bool Victory() { return victory; }
	//Activate/Deactivate all entities of a level
	void ActivateEntities(bool isActive);
	//Resets the level by clearing all entities from logic and render 
	//and making them again
	void ResetLevel();
	void SetNeedsReset(bool needsReset) { this->needsReset = needsReset; LoseHP(); }
	bool GetNeedsReset() { return needsReset; }
	//Decrements HP and detects if player is dead for rendering purpose
	void LoseHP();
	//Function that makes two balls out of one unless it is the smallest ball
	void ExplodeBall(Entity* explodingBall);
	int GetHP() { return playerHP; }
	GLuint GetPlayerHPAvatar() { return playerHPAvatar; }
};

