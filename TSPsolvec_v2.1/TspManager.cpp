#include "TspManager.h"
#include "CompleteGraphHelper.h"
#include "TspFactory.h"
#include "TspHelper.h"
#include "Config.h"
#include <boost/timer/timer.hpp>
#include <boost/chrono.hpp>
#include "StopWatch.h"
#include <vector>
#include <string>

TspManager::TspManager(const std::shared_ptr<const std::vector<std::string>> & algorithm_names, const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Index> & start, const std::shared_ptr<const ParametersAll> & parameters)
{
	this->algorithm_names = algorithm_names;
	this->graph = graph;
	this->start = start;
	this->parameters = parameters;
}

TspManager::~TspManager()
{

}

void TspManager::SetAlgorithms(std::shared_ptr<const std::vector<std::string>>algorithm_names)
{
	this->algorithm_names = algorithm_names;
}

std::shared_ptr<const std::vector<std::string>> TspManager::GetAlgorithms() const
{
	return this->algorithm_names;
}

void TspManager::SetGraph(std::shared_ptr<const CompleteGraph> graph)
{
	this->graph = graph;
}

std::shared_ptr<const CompleteGraph> TspManager::GetGraph() const
{
	return this->graph;
}

void TspManager::SetStartPoint(std::shared_ptr<const Index> start)
{
	this->start = start;
}

std::shared_ptr<const Index> TspManager::GetStartPoint() const
{
	return this->start;
}

void TspManager::SetParameters(std::shared_ptr<const ParametersAll> parameters)
{
	this->parameters = parameters;
}

std::shared_ptr<const ParametersAll> TspManager::GetParameters() const
{
	return this->parameters;
}

//Wyœwietlanie informacji o grafie i punkcie pocz¹tkowym.
void TspManager::Info(std::ostream & stream, std::ostream & stream_errors)
{
	if (this->graph != nullptr)
	{
		stream << "Graph:" << std::endl;
		CompleteGraphHelper::DisplayGraph(*(this->graph), stream);
		stream << "Start Point:" << std::endl;
		Index start = 0;

		if (this->start != nullptr)
		{
			start = *(this->start);
		}

		stream << start << std::endl;
		stream << std::endl;
	}
}

//Wykonanie algorytmów na podanych danych i wyœwietlenie wyników.
void TspManager::Execute(const bool & verbose, std::ostream & stream, std::ostream & stream_errors)
{
	if (this->algorithm_names != nullptr)
	{
		if (this->graph != nullptr)
		{
			boost::timer::cpu_timer timer;
			//Stopwatch stopwatch = Stopwatch();

			for (const std::string & algorithm_name : *(this->algorithm_names))
			{
				Index start = 0;
				if (this->start != nullptr)
				{
					start = *(this->start);
				}
				std::shared_ptr<TspAlgorithm> algorithm_ptr = TspFactory::CreateAlgorithm(algorithm_name, this->graph, start, this->parameters);

				if (algorithm_ptr == nullptr)
				{
					stream_errors << "Error: Invalid algorithm name: " << algorithm_name << std::endl;
					stream_errors << std::endl;
					continue;
				}

				stream << "Algorithm:" << std::endl;
				stream << algorithm_name << std::endl;
				
				TspHelper::DisplayAlgorithmParameters(*algorithm_ptr, true, stream);
				timer.start();
				
				//stopwatch.Start();

				Path path = algorithm_ptr.get()->Resolve();

				timer.stop();

				//stopwatch.Stop();

				stream << "Time:" << std::endl;

				boost::timer::cpu_times times = timer.elapsed();
				auto nanoseconds = boost::chrono::nanoseconds(times.user + times.system);
				auto milliseconds = boost::chrono::duration_cast<boost::chrono::milliseconds>(nanoseconds);
				stream << milliseconds.count() << std::endl;

				//Wyœwietlanie bardziej szczegó³owych danych.
				if (verbose == true)
				{
					stream << "Stats:" << std::endl;
					stream << timer.format(boost::timer::default_places, "%ws wall, %us user + %ss system = %ts CPU (%p%)") << std::endl;
				}

				//stream << stopwatch.GetDiffValueInMiliseconds() << std::endl;

				stream << "Result (path, costs, cost):" << std::endl;
				CompleteGraphHelper::DisplayPath(*(this->graph), path, true, true, true, stream);
				stream << std::endl;
			}
		}
		else
		{
			stream_errors << "Error: Null graph" << std::endl;
			stream_errors << std::endl;
		}
	}
	else
	{
		stream_errors << "Error: Null algorithm names" << std::endl;
		stream_errors << std::endl;
	}
}

