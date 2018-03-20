#include "StopWatch.h"

Stopwatch::Stopwatch()
{
	this->valueStart = 0;
	this->valueStop = 0;
	this->isRunning = false;
}

Stopwatch::~Stopwatch()
{

}

std::pair<std::clock_t, std::clock_t> Stopwatch::GetStopwatchFraction() const
{
	std::clock_t stopwatch_multiplier = 1;
	std::clock_t stopwatch_divisor = 1;

	if (CLOCKS_PER_SEC != 1000)
	{
		stopwatch_multiplier = 1000;
		stopwatch_divisor = CLOCKS_PER_SEC;
	}

	return { stopwatch_multiplier, stopwatch_divisor };
}

std::clock_t Stopwatch::GetStopwatchMultiplier() const
{
	return GetStopwatchFraction().first;
}

std::clock_t Stopwatch::GetStopwatchDivisor() const
{
	return GetStopwatchFraction().second;
}

std::clock_t Stopwatch::GetCurrentRawValue() const
{
	return std::clock();
}

void Stopwatch::Start()
{
	this->valueStart = GetCurrentRawValue();
	this->valueStop = this->valueStart;
	this->isRunning = true;
}

void Stopwatch::Stop()
{
	this->valueStop = GetCurrentRawValue();
	this->isRunning = false;
}

std::clock_t Stopwatch::GetStartRawValue() const
{
	return this->valueStart;
}

std::clock_t Stopwatch::GetStopRawValue() const
{
	if (this->isRunning)
	{
		return this->valueStop;
	}
	else
	{
		return GetCurrentRawValue();
	}
}

std::clock_t Stopwatch::GetDiffRawValue() const
{
	return this->valueStop - this->valueStart;
}

bool Stopwatch::IsRunning() const
{
	return this->isRunning;
}

std::clock_t Stopwatch::GetUnitsPerSecond() const
{
	return CLOCKS_PER_SEC;
}

double Stopwatch::GetDiffValueInMilisecondsAsDouble() const
{
	return this->GetDiffRawValue() / GetStopwatchDivisor() * GetStopwatchMultiplier();
}

long Stopwatch::GetDiffValueInMilisecondsAsLong() const
{
	return this->GetDiffRawValue() / GetStopwatchDivisor() * GetStopwatchMultiplier();
}

long Stopwatch::GetDiffValueInMiliseconds() const
{
	return this->GetDiffValueInMilisecondsAsLong();
}
