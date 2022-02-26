#pragma once
#include <chrono> 
#include <string>

// Simple timer class which acts like a stop watch.
// Mainly used for checking the duration of a process
class Timer
{
	public:
		Timer() = default;
		~Timer() = default;

		void StartTimer();
		void EndTimer();
		float ShowResult();

	private:
		std::chrono::steady_clock::time_point start;
		std::chrono::steady_clock::time_point end;
};
