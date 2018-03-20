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

	//Bie¿¹cy rozpatrywany wiercho³ek.
	Index current = start;

	//Tworzomy listê (koszt usuniêcia elementu jest niski) nieodwiedzonych wierzcho³ków.
	//Pomijamy pocz¹tkowy gdy¿ ten zawsze jest pierwszym i ostatnim.
	std::list<Index> unvisited = {};

	for (Index i = 0; i < (this->graph).get()->GetSize(); i++)
	{
		if (i != start)
		{
			unvisited.push_back(i);
		}
	}

	//Dopóki mamy nieodwiedzone wierzcho³ki.
	while (unvisited.size() > 0)
	{
		//Bierzemy pierwszy z nieodwiedzonych wierzcho³ków.
		std::list<Index>::iterator selected = unvisited.begin();
		Index next = *selected;
		Value cost = (this->graph).get()->GetCost(current, *selected);

		//Jeœli nieodwiedzonych wierzcho³ków jest wiêcej - szukamy takiego, do którego przejœcie jest najtañsze.
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

		//Usuwamy odwiedzony wierzcho³ek z listy.
		unvisited.erase(selected);

		//Dodajemy wybrany wierzcho³ek do œcie¿ki.
		current = next;
		path.push_back(current);
	}

	//Dodajemy na koñcu œcie¿ki punkt pocz¹tkowy.
	//Dziêki temu otrzymamy cykl Hamiltona.
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
