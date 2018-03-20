#include "TspAlgorithmBruteForce.h"
#include "CompleteGraphHelper.h"
#include <algorithm>

TspAlgorithmBruteForce::TspAlgorithmBruteForce() : TspAlgorithm::TspAlgorithm()
{

}

TspAlgorithmBruteForce::TspAlgorithmBruteForce(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, path, parameters)
{

}

TspAlgorithmBruteForce::TspAlgorithmBruteForce(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, start, parameters)
{

}

TspAlgorithmBruteForce::TspAlgorithmBruteForce(const TspAlgorithm & tsp) : TspAlgorithm::TspAlgorithm(tsp)
{

}

TspAlgorithmBruteForce::~TspAlgorithmBruteForce()
{

}

Path TspAlgorithmBruteForce::ResolveTsp()
{
	Index start = GetStartPoint();
	Path path = CompleteGraphHelper::GetCycle(*(this->graph).get(), start);
	Value cost = CompleteGraphHelper::GetPathCost(*(this->graph), path);

	//Bierzemy wektor sk³adaj¹cy siê z wierzcho³ków od 1 do n-1, czyli z pominiêciem zerowego.
	std::vector<Index> vector = {};
	for (Index i = 1; i < (this->graph).get()->GetSize(); i++)
	{
		vector.push_back(i);
	}

	//Rozwa¿amy wszystkie permutacje.
	std::vector<Index> vector_best = vector;
	while (std::next_permutation(vector.begin(), vector.end()))
	{
		Value cost_new = CompleteGraphHelper::GetPathCostFromPath(*(this->graph), vector);

		//Dodajemy koszt po³¹czenia z wierzcho³kiem zerowym (tymczasowym startowym).
		cost_new += (this->graph).get()->GetCost(0, vector.front());
		cost_new += (this->graph).get()->GetCost(vector.back(), 0);

		if (cost_new < cost)
		{
			vector_best = vector;
			cost = cost_new;
		}
	}

	vector_best.push_back(0);

	//Przesuwamy œcie¿kê tak aby zaczyna³a siê od po¿¹danego punktu.
	Path path_best = CompleteGraphHelper::ShiftPath(vector_best, start);

	//Dodajemy na koñcu œcie¿ki punkt pocz¹tkowy.
	path_best.push_back(path_best[0]);

	return path_best;
}

const std::string TspAlgorithmBruteForce::GetName() const
{
	return "TspAlgorithmBruteForce";
}

const std::string TspAlgorithmBruteForce::GetTitle() const
{
	return "Tsp Algorithm Brute Force";
}

const std::string TspAlgorithmBruteForce::GetDescription() const
{
	return "TSP algorithm Brute Force";
}

const Parameters TspAlgorithmBruteForce::GetParametersDefault() const
{
	return {};
}
