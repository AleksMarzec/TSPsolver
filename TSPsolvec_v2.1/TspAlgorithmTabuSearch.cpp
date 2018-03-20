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

//Zwraca przez referencj� najlepszego s�siada i jego koszt, informuje czy uda�o si� znale�� s�siada.
bool TspAlgorithmTabuSearch::GetBestNeighbour(Path & path, Value & cost, TabuList & tabu)
{
	bool first = true;
	Index i_best = 0;
	Index j_best = 0;
	cost = 0;

	Path path_best = path;
	Value cost_best = cost;

	//P�tla od 1 do n-2, poniewa� chcemy pomin�� pierwszy i ostatni element kt�ry musi by� sta�y.
	for (Index i = 1; i < path.size() - 1; i++)
	{
		for (Index j = i + 1; j < path.size() - 1; j++)
		{
			if (i == j)
			{
				continue;
			}

			//Je�li operacja jest dozwolona, tzn. nie znajduje si� na li�cie tabu.
			if (tabu.TabuCheck(i, j) == false)
			{
				Path path_new = path;

				//Zamiana wierzcho�k�w - tworzymy s�siada rozwi�zania.
				CompleteGraphHelper::PathSwapVerticesHere(path_new, i, j);

				//Obliczanie kosztu s�siada.
				Value cost_new = CompleteGraphHelper::GetPathCost(*(this->graph), path_new);

				//Je�li jest pierwszy lub lepszy, to podmie�.
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

	//Wykonujemy algorytm przez podan� liczb� iteracji.
	for (Index i = 0; i < iterations; i++)
	{
		Path path_new = path;
		if (GetBestNeighbour(path, cost, tabu) == false)
		{
			//Je�li nie uda�o si� znale�� s�siada ze wzgl�du na tabu - ko�cz.
			break;
		}

		//Je�li koszt aktualnego rozwi�zania jest lepszy od najlepszego to we� nowe najlepsze rozwi�zanie.
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
