#include "Timer.h"

LARGE_INTEGER frequency, previousTime, currentTime;

void Timer::InitSlotsToProccess()
{
	//Time Logic
	QueryPerformanceCounter(&currentTime);
	timeDif = (static_cast<double>(currentTime.QuadPart) - static_cast<double>(previousTime.QuadPart)) / static_cast<double>(frequency.QuadPart);
	previousTime = currentTime;

	if (timeDif <= 0.0f) {
		return;
	}

	fpsCount = timeDif;
	actualTime += timeDif * timeMultiplier;
	elapsed += timeDif;

	if (elapsed >= spiralOfDeath) {
		elapsed = spiralOfDeath;
	}
}

bool Timer::ProcessSlots()
{
	if (elapsed >= fixedTick) {
		logicTime += fixedTick;
		elapsed = elapsed - fixedTick;
		return true;
	}
	return false;
}
