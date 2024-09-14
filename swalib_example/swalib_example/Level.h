#pragma once
class Level
{
private:
	const char* leve1Json = "data/JSONFolder/Level1SuperPang.json";
	const char* leve2Json = "data/JSONFolder/Level2SuperPang.json";
	unsigned int currentLevel = 0;
	int width = 48;		//Width of tilemap
	int height = 26;	//Height of tilemap
public:
	int GetCurrentLevel() { return currentLevel; }
	//Function that reads the json containing the current level
	//and adds a sprite to the render sprite vector
	void ReadLevel();
	//Changes the level and calls "ReadLevel()"
	void ChangeLevel();
	//This function tells the renderEngine to display text when player
	//is dead
	void DeadLevel() { currentLevel = -1; }
};

