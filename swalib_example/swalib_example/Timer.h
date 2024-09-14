#pragma once
#include "stdafx.h"
/*-------Timer-------
	Timing system to control the 
	time logic and to not produce errors
	like the death spiral
*/
class Timer
{
private:
	double fixedTick = 1.0 / 60.0;
	double spiralOfDeath = 1.0 / 15.0;
	double elapsed = 0;
	double fpsCount = 0;
	double actualTime = 0;
	double timeDif = 0;
	double logicTime = 0;
	double timeMultiplier = 1;
public:
	//Obtains all the information needed for fps, and time calculation in each fram
	// and checks that the spiral of death does not happen
	void InitSlotsToProccess();
	//In charge of maintaining a regular fps
	bool ProcessSlots();
	//LARGE_INTEGER GetFrequency() { return frequency; }
	//LARGE_INTEGER GetPreviousTime() { return previousTime; }
	double GetFixedTick() { return fixedTick; }
	double GetFpsCount() { return fpsCount; }
	double GetActualTime() { return actualTime; }
	double GetLogicTime() { return logicTime; }
	void SetTimeMultiplier(double timeMultiplier) { this->timeMultiplier = timeMultiplier; }
};

