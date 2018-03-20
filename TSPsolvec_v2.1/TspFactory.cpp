#include "TspFactory.h"
#include "TspAlgorithmRandom.h"
#include "TspAlgorithmBruteForce.h"
#include "TspAlgorithmNearestNeighbourAlgorithm.h"
#include "TspAlgorithmTabuSearch.h"
#include "TspAlgorithmGenetic.h"

TspFactory::TspFactory()
{
	this->parameters = {};
	for (const std::shared_ptr<TspAlgorithm> & algorithm : CreateAlgorithmsAll(nullptr))
	{
		if (algorithm != nullptr)
		{
			this->parameters.insert({ algorithm.get()->GetName(), algorithm.get()->GetParametersResult() });
		}
	}
}

TspFactory::~TspFactory()
{

}


//Zwraca listê dostêpnych algorytmów.
const std::vector<std::string> TspFactory::GetAlgorithmNames()
{
	return { "TspAlgorithmRandom", "TspAlgorithmBruteForce", "TspAlgorithmNearestNeighbourAlgorithm", "TspAlgorithmTabuSearch", "TspAlgorithmGenetic" };
}

//Sprawdza czy podana nazwa algorytmu jest poprawna.
const bool TspFactory::CheckAlgorithmName(const std::string & algorithm_name)
{
	for (const std::string & name : GetAlgorithmNames())
	{
		if (algorithm_name == name)
		{
			return true;
		}
	}

	return false;
}

std::shared_ptr<TspAlgorithm> TspFactory::CreateAlgorithm(const std::string & algorithm_name, const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters)
{
	if (algorithm_name == "TspAlgorithmRandom")
	{
		return std::make_shared<TspAlgorithmRandom>(TspAlgorithmRandom(graph, start, parameters));
	}
	else if (algorithm_name == "TspAlgorithmBruteForce")
	{
		return std::make_shared<TspAlgorithmBruteForce>(TspAlgorithmBruteForce(graph, start, parameters));
	}
	else if (algorithm_name == "TspAlgorithmNearestNeighbourAlgorithm")
	{
		return std::make_shared<TspAlgorithmNearestNeighbourAlgorithm>(TspAlgorithmNearestNeighbourAlgorithm(graph, start, parameters));
	}
	else if (algorithm_name == "TspAlgorithmTabuSearch")
	{
		return std::make_shared<TspAlgorithmTabuSearch>(TspAlgorithmTabuSearch(graph, start, parameters));
	}
	else if (algorithm_name == "TspAlgorithmGenetic")
	{
		return std::make_shared<TspAlgorithmGenetic>(TspAlgorithmGenetic(graph, start, parameters));
	}
	else
	{
		return nullptr;
	}
}

std::vector<std::shared_ptr<TspAlgorithm>> TspFactory::CreateAlgorithms(const std::vector<std::string> & algorithm_names, const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters)
{
	std::vector<std::shared_ptr<TspAlgorithm>> algorithms;

	for (const std::string & algorithm_name : algorithm_names)
	{
		std::shared_ptr<TspAlgorithm> algorithm_ptr = CreateAlgorithm(algorithm_name, graph, start, parameters);

		if (algorithm_ptr != nullptr)
		{
			algorithms.push_back(algorithm_ptr);
		}
	}

	return algorithms;
}

std::vector<std::shared_ptr<TspAlgorithm>> TspFactory::CreateAlgorithmsAll(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters)
{
	return CreateAlgorithms(GetAlgorithmNames(), graph, start, parameters);
}

const ParametersAll TspFactory::GetAlgorithmParametersAll() const
{
	return this->parameters;
}

