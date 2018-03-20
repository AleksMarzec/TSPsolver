#include "TspAlgorithmRandom.h"
#include "CompleteGraphHelper.h"

TspAlgorithmRandom::TspAlgorithmRandom() : TspAlgorithm::TspAlgorithm()
{

}

TspAlgorithmRandom::TspAlgorithmRandom(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, path, parameters)
{

}

TspAlgorithmRandom::TspAlgorithmRandom(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, start, parameters)
{

}

TspAlgorithmRandom::TspAlgorithmRandom(const TspAlgorithm & tsp) : TspAlgorithm::TspAlgorithm(tsp)
{

}

TspAlgorithmRandom::~TspAlgorithmRandom()
{

}

Path TspAlgorithmRandom::ResolveTsp()
{
	Path path = *(GetPath());
	Value cost = CompleteGraphHelper::GetPathCost(*(this->graph), path);
	Index iterations = GetParameterValue("iterations");

	if (iterations > 0)
	{
		Index start = GetStartPoint();

		for (Index i = 0; i < iterations; i++)
		{
			Path path_new = CompleteGraphHelper::GetCycleRandom(*(this->graph), start);
			Value cost_new = CompleteGraphHelper::GetPathCost(*(this->graph), path_new);

			if (cost_new < cost)
			{
				path = path_new;
				cost = cost_new;
			}
		}
	}
	return path;
}

const std::string TspAlgorithmRandom::GetName() const
{
	return "TspAlgorithmRandom";
}

const std::string TspAlgorithmRandom::GetTitle() const
{
	return "Tsp Algorithm Random";
}

const std::string TspAlgorithmRandom::GetDescription() const
{
	return "TSP algorithm example";
}

const Parameters TspAlgorithmRandom::GetParametersDefault() const
{
	return { { "iterations", Parameter(GetName(), "iterations", 10, "iteration count") } };
}

