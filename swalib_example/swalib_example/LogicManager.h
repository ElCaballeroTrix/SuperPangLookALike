#pragma once
#include <vector>
#include "Timer.h"

/*-------LogicManager-------
	A manager in charge of the game logic.
	It initializes and shutdowns all data.
*/
class Entity;
class LogicManager
{
private:
	static LogicManager* instance;
	Timer timer;
	LogicManager();
public:
	//Initializes global data 
	void InitData();
	//Shutdowns global data.
	void ShutdownData();
	Timer GetTimer() { return timer; }
	static LogicManager* GetInstance();
	//Main logic function that takes into account time management
	//and updates the logic each frame
	void Update();
	//In charge of game logic called by Update
	void GameLogicFunction();
	//Function for handleing player inputs
	void HandleInputs();
	double GetFpsCount() { return timer.GetFpsCount(); }
	double GetLogictime() { return timer.GetLogicTime(); }
	double GetActualTime() { return timer.GetActualTime(); }
	double GetFixedTick() { return timer.GetFixedTick(); }
	void SetTimerMultiplier(double timerMultiplier) { timer.SetTimeMultiplier(timerMultiplier); }
	//LARGE_INTEGER GetFrequency() { return timer.GetFrequency(); }
	//LARGE_INTEGER GetPreviousTime() { return timer.GetPreviousTime(); }
};

