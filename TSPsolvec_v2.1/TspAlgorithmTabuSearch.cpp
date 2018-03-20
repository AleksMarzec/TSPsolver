#include "TspAlgorithmTabuSearch.h"
#include "CompleteGraphHelper.h"

TspAlgorithmTabuSearch::TspAlgorithmTabuSearch() : TspAlgorithm::TspAlgorithm()
{

}

TspAlgorithmTabuSearch::TspAlgorithmTabuSearch(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, path, parameters)
{

}

TspAlgorithmTabuSearch::TspAlgorithmTabuSearch(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, start, parameters)
{

}

TspAlgorithmTabuSearch::TspAlgorithmTabuSearch(const TspAlgorithm & tsp) : TspAlgorithm::TspAlgorithm(tsp)
{

}

TspAlgorithmTabuSearch::~TspAlgorithmTabuSearch()
{

}

//Zwraca przez referencjê najlepszego s¹siada i jego koszt, informuje czy uda³o siê znaleŸæ s¹siada.
bool TspAlgorithmTabuSearch::GetBestNeighbour(Path & path, Value & cost, TabuList & tabu)
{
	bool first = true;
	Index i_best = 0;
	Index j_best = 0;
	cost = 0;

	Path path_best = path;
	Value cost_best = cost;

	//Pêtla od 1 do n-2, poniewa¿ chcemy pomin¹æ pierwszy i ostatni element który musi byæ sta³y.
	for (Index i = 1; i < path.size() - 1; i++)
	{
		for (Index j = i + 1; j < path.size() - 1; j++)
		{
			if (i == j)
			{
				continue;
			}

			//Jeœli operacja jest dozwolona, tzn. nie znajduje siê na liœcie tabu.
			if (tabu.TabuCheck(i, j) == false)
			{
				Path path_new = path;

				//Zamiana wierzcho³ków - tworzymy s¹siada rozwi¹zania.
				CompleteGraphHelper::PathSwapVerticesHere(path_new, i, j);

				//Obliczanie kosztu s¹siada.
				Value cost_new = CompleteGraphHelper::GetPathCost(*(this->graph), path_new);

				//Jeœli jest pierwszy lub lepszy, to podmieñ.
				if (first == true || cost_new < cost_best)
				{
					i_best = i;
					j_best = j;
					path_best = path_new;
					cost_best = cost_new;
					if (first == true)
					{
						first = false;
					}
				}
			}
		}
	}

	if (!first)
	{
		path = path_best;
		cost = cost_best;

		//Dodajemy informacje o podmianie do tabu.
		tabu.TabuAdd(i_best, j_best);

		return true;
	}

	return false;
}

//https://en.wikipedia.org/wiki/Tabu_search#Pseudocode
Path TspAlgorithmTabuSearch::ResolveTsp()
{
	Path path = *(GetPath());
	Index size = (this->graph).get()->GetSize();
	Value cost = CompleteGraphHelper::GetPathCost(*(this->graph), path);

	Path path_best = path;
	Value cost_best = cost;

	Index iterations = GetParameterValue("iterations");
	Index tabu_max = GetParameterValue("tabu_max");

	//Lista tabu.
	TabuList tabu = TabuList(size, tabu_max);

	//Wykonujemy algorytm przez podan¹ liczbê iteracji.
	for (Index i = 0; i < iterations; i++)
	{
		Path path_new = path;
		if (GetBestNeighbour(path, cost, tabu) == false)
		{
			//Jeœli nie uda³o siê znaleŸæ s¹siada ze wzglêdu na tabu - koñcz.
			break;
		}

		//Jeœli koszt aktualnego rozwi¹zania jest lepszy od najlepszego to weŸ nowe najlepsze rozwi¹zanie.
		if (cost < cost_best)
		{
			path_best = path;
			cost_best = cost;
		}
	}

	return path_best;
}

const std::string TspAlgorithmTabuSearch::GetName() const
{
	return "TspAlgorithmTabuSearch";
}

const std::string TspAlgorithmTabuSearch::GetTitle() const
{
	return "Tsp Algorithm Tabu Search";
}

const std::string TspAlgorithmTabuSearch::GetDescription() const
{
	return "TSP algorithm Tabu Search";
}

const Parameters TspAlgorithmTabuSearch::GetParametersDefault() const
{
	return { { "iterations", Parameter(GetName(), "iterations", 10, "iteration count") },{ "tabu_max", Parameter(GetName(), "tabu_max", 3, "tabu max") } };
}
