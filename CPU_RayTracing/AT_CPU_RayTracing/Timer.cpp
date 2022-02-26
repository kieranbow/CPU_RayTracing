#include "Timer.h"

void Timer::StartTimer()
{
	start = std::chrono::high_resolution_clock::now();
}

void Timer::EndTimer()
{
	end = std::chrono::high_resolution_clock::now();
}

float Timer::ShowResult()
{
	std::chrono::duration<float> seconds = end - start;
	return seconds.count();
}
