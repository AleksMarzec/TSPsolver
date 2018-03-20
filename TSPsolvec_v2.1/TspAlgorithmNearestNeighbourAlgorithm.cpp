#include "TspAlgorithmNearestNeighbourAlgorithm.h"
#include "CompleteGraphHelper.h"
#include <list>

TspAlgorithmNearestNeighbourAlgorithm::TspAlgorithmNearestNeighbourAlgorithm() : TspAlgorithm::TspAlgorithm()
{

}

TspAlgorithmNearestNeighbourAlgorithm::TspAlgorithmNearestNeighbourAlgorithm(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, path, parameters)
{

}

TspAlgorithmNearestNeighbourAlgorithm::TspAlgorithmNearestNeighbourAlgorithm(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, start, parameters)
{

}

TspAlgorithmNearestNeighbourAlgorithm::TspAlgorithmNearestNeighbourAlgorithm(const TspAlgorithm & tsp) : TspAlgorithm::TspAlgorithm(tsp)
{

}

TspAlgorithmNearestNeighbourAlgorithm::~TspAlgorithmNearestNeighbourAlgorithm()
{

}

Path TspAlgorithmNearestNeighbourAlgorithm::ResolveTsp()
{
	Index start = GetStartPoint();
	Path path = {};
	path.push_back(start);

	//Bie��cy rozpatrywany wiercho�ek.
	Index current = start;

	//Tworzomy list� (koszt usuni�cia elementu jest niski) nieodwiedzonych wierzcho�k�w.
	//Pomijamy pocz�tkowy gdy� ten zawsze jest pierwszym i ostatnim.
	std::list<Index> unvisited = {};

	for (Index i = 0; i < (this->graph).get()->GetSize(); i++)
	{
		if (i != start)
		{
			unvisited.push_back(i);
		}
	}

	//Dop�ki mamy nieodwiedzone wierzcho�ki.
	while (unvisited.size() > 0)
	{
		//Bierzemy pierwszy z nieodwiedzonych wierzcho�k�w.
		std::list<Index>::iterator selected = unvisited.begin();
		Index next = *selected;
		Value cost = (this->graph).get()->GetCost(current, *selected);

		//Je�li nieodwiedzonych wierzcho�k�w jest wi�cej - szukamy takiego, do kt�rego przej�cie jest najta�sze.
		if (unvisited.size() > 1)
		{
			for (std::list<Index>::iterator it = std::next(unvisited.begin()); it != unvisited.end(); ++it)
			{
				Value cost_new = (this->graph).get()->GetCost(current, *it);
				if (cost_new < cost)
				{
					selected = it;
					next = *it;
					cost = cost_new;
				}
			}
		}

		//Usuwamy odwiedzony wierzcho�ek z listy.
		unvisited.erase(selected);

		//Dodajemy wybrany wierzcho�ek do �cie�ki.
		current = next;
		path.push_back(current);
	}

	//Dodajemy na ko�cu �cie�ki punkt pocz�tkowy.
	//Dzi�ki temu otrzymamy cykl Hamiltona.
	path.push_back(path[0]);

	return path;
}

const std::string TspAlgorithmNearestNeighbourAlgorithm::GetName() const
{
	return "TspAlgorithmNearestNeighbourAlgorithm";
}

const std::string TspAlgorithmNearestNeighbourAlgorithm::GetTitle() const
{
	return "Tsp Algorithm Nearest Neighbour Algorithm";
}

const std::string TspAlgorithmNearestNeighbourAlgorithm::GetDescription() const
{
	return "TSP algorithm Nearest Neighbour Algorithm";
}

const Parameters TspAlgorithmNearestNeighbourAlgorithm::GetParametersDefault() const
{
	return {};
}
