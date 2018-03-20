#pragma once

#include <ctime>
#include <utility>

//Stoper.
class Stopwatch
{
protected:
	std::clock_t valueStart = 0;
	std::clock_t valueStop = 0;
	bool isRunning = false;
	std::pair<std::clock_t, std::clock_t> GetStopwatchFraction() const;
	std::clock_t GetStopwatchMultiplier() const;
	std::clock_t GetStopwatchDivisor() const;

public:
	Stopwatch();
	virtual ~Stopwatch();
	void Start();
	void Stop();
	std::clock_t GetStartRawValue() const;
	std::clock_t GetStopRawValue() const;
	std::clock_t GetCurrentRawValue() const;
	std::clock_t GetDiffRawValue() const;
	bool IsRunning() const;
	std::clock_t GetUnitsPerSecond() const;
	double GetDiffValueInMilisecondsAsDouble() const;
	long GetDiffValueInMilisecondsAsLong() const;
	long GetDiffValueInMiliseconds() const;
};


