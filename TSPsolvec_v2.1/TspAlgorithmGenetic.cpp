#include "TspAlgorithmGenetic.h"
#include "CompleteGraphHelper.h"
#include <vector>


TspAlgorithmGenetic::TspAlgorithmGenetic() : TspAlgorithm::TspAlgorithm()
{

}

TspAlgorithmGenetic::TspAlgorithmGenetic(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, path, parameters)
{

}

TspAlgorithmGenetic::TspAlgorithmGenetic(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm(graph, start, parameters)
{

}

TspAlgorithmGenetic::TspAlgorithmGenetic(const TspAlgorithm & tsp) : TspAlgorithm::TspAlgorithm(tsp)
{

}

TspAlgorithmGenetic::~TspAlgorithmGenetic()
{

}

//Ewolucja populacji.
Population TspAlgorithmGenetic::EvolvePopulation(const Population & population, const Real & mutation_rate_real, const Index & tournament_size, const bool & elitism)
{
	Population population_new = Population(population.GetGraph(), population.GetStartPoint(), population.GetPopulationSize(), false);

	//Zachowanie najlepszych osobników.
	Index elitism_offset = 0;

	if (elitism == true)
	{
		if (elitism_offset < population.GetPopulationSize())
		{
			population_new.SavePath(0, population.GetPathBest());
		}
	}

	//Krzy¿owanie.
	//Tworzenie osobników z obecnej populacji.
	for (Index i = elitism_offset; i < population_new.GetPopulationSize(); i++)
	{
		//Wybór rodziców.
		Path parent1 = TournamentSelection(population, tournament_size);
		Path parent2 = TournamentSelection(population, tournament_size);

		//Krzy¿owanie rodziców.
		Path child = Crossover(parent1, parent2);

		//Dodanie nowego osobnika do populacji.
		population_new.SavePath(i, child);
	}

	//Mutacje.
	for (Index i = elitism_offset; i < population_new.GetPopulationSize(); i++)
	{
		Path temp = Mutate(population_new.GetPath(i), mutation_rate_real);
		population_new.SavePath(i, temp);
	}

	return population_new;
}

//Krzy¿owanie rodziców i tworzenie potomstwa.
Path TspAlgorithmGenetic::Crossover(const Path & parent1, const Path & parent2)
{
	// Obs³uga b³êdów.
	if (parent1.size() == 0 || parent2.size() == 0)
	{
		return {};
	}

	Path child;

	//Obs³uga b³êdów.
	if (parent1.size() != parent2.size())
	{
		if (parent1.size() < parent2.size())
		{
			child = parent1;
		}
		else
		{
			child = parent2;
		}
		return child;
	}

	//Obs³uga b³êdów.
	if (parent1.size() <= 2)
	{
		child = parent1;
		return child;
	}

	//Tworzenie nowego potomka.
	child = Path(parent1.size());

	//Informuje, które pola dziecka zosta³y wype³nione.
	std::vector<bool> filled = std::vector<bool>(child.size(), false);

	//Dodane miasta.
	std::vector<Index> added = {};

	//Losowanie pozycji pocz¹tkowej i koñcowej dla pierwszego rodzica.
	Index position_start = (Index)(CompleteGraphHelper::GetRandomReal(0.0, 1.0) * parent1.size());
	if (position_start >= parent1.size())
	{
		position_start--;
	}

	Index position_end = (Index)(CompleteGraphHelper::GetRandomReal(0.0, 1.0) * parent1.size());
	if (position_end >= parent1.size())
	{
		position_end--;
	}

	//Wprowadzenie do dziecka losowego fragmentu pierwszego rodzica.
	for (Index i = 0; i < child.size(); i++)
	{
		//Sprawdzanie pozycji.
		if (position_start < position_end && i > position_start && i < position_end)
		{
			child[i] = parent1[i];
			added.push_back(child[i]);
			filled[i] = true;
		} //Jeœli pozycja pocz¹tkowa jest wiêksza od koñcowej.
		else if (position_start > position_end)
		{
			if (!(i < position_start && i > position_end))
			{
				child[i] = parent1[i];
				added.push_back(child[i]);
				filled[i] = true;
			}
		}
	}

	//Uzupe³nienie dziecka wierzo³kami drugiego rodzica.
	for (Index i = 0; i < parent2.size(); i++)
	{
		bool contained = false;

		for (Index c = 0; c < added.size(); c++)
		{
			if (parent2[i] == added[c])
			{
				contained = true;
				break;
			}
		}

		//Jeœli dziecko nie zawiera jeszcze danego miasta.
		if (contained == false)
		{
			//Uzupe³nienie "pustych" pozycji.
			for (Index j = 0; j < child.size(); j++)
			{
				if (filled[j] == false)
				{
					child[j] = parent2[i];
					added.push_back(child[j]);
					filled[j] = true;
					break;
				}
			}
		}
	}

	child[child.size() - 1] = child[0];

	return child;
}

//Mutaja œcie¿ki przez zamianê dwóch miast ze sob¹.
bool TspAlgorithmGenetic::MutateHere(Path & path, const Real & mutation_rate_real)
{
	//Obs³uga b³êdów.
	if (path.size() <= 3)
	{
		//Nie ma czego mutowaæ - pierwszy i ostatni wierzcho³ek chcemy zachowaæ a poœrodku jest tylko jeden.
		return false;
	}

	bool mutated = false;

	//Pêtla po wszystkich miastach oprócz pierwszego i ostatniego.
	for (Index position1 = 1; position1 < path.size() - 1; position1++)
	{
		//Zastosowanie wspó³czynnika mutacji.
		if (CompleteGraphHelper::GetRandomReal(0.0, 1.0) < mutation_rate_real)
		{
			//Losowanie drugiego miasta.
			Index position2 = (Index)((path.size() - 2) * CompleteGraphHelper::GetRandomReal(0.0, 1.0)) + 1;

			if (position2 >= path.size() - 1)
			{
				position2--;
			}

			if (position1 != position2 && position1 > 0 && position2 > 0 && position1 < path.size() - 1 && position2 < path.size())
			{
				CompleteGraphHelper::PathSwapVerticesHere(path, position1, position2);

				if (mutated == false)
				{
					mutated = true;
				}
			}
		}
	}
	return mutated;
}

Path TspAlgorithmGenetic::Mutate(const Path & path, const Real & mutation_rate_real)
{
	Path path_new = path;
	MutateHere(path_new, mutation_rate_real);
	return path_new;
}

//Wybieranie kandydata œcie¿ki do krzy¿owania.
Path TspAlgorithmGenetic::TournamentSelection(const Population & population, const Index & tournament_size)
{
	//Obs³uga b³êdów.
	if (population.GetPopulationSize() == 0)
	{
		return {};
	}

	//Grupa turniejowa
	Population tournament = Population(population.GetGraph(), population.GetStartPoint(), tournament_size, false);

	//Wybieranie losowych kandydatów.
	for (Index i = 0; i < tournament_size; i++)
	{
		Index id_random = (Index)(CompleteGraphHelper::GetRandomReal(0.0, 1.0) * population.GetPopulationSize());

		if (id_random >= population.GetPopulationSize())
		{
			id_random--;
		}

		tournament.SavePath(i, population.GetPath(id_random));
	}

	//Wybór najlepszego osobnika z grupy turniejowej.
	return tournament.GetPathBest();
}

//Algorytm genetyczny.
//http://www.k0pper.republika.pl/geny.htm
//http://www.theprojectspot.com/tutorial-post/applying-a-genetic-algorithm-to-the-travelling-salesman-problem/5
Path TspAlgorithmGenetic::ResolveTsp()
{
	Path path = *(GetPath());
	Index start = GetStartPoint();

	//Przetwarzanie parametrów.
	Index iterations = GetParameterValue("iterations");
	Index population_size = GetParameterValue("population_size");
	const Index population_size_max = Population::GetPopulationSizeMax();

	if (population_size > population_size_max)
	{
		population_size = population_size_max;
	}

	Index mutation_rate = GetParameterValue("mutation_rate");
	Real mutation_rate_real = 0;

	if (mutation_rate > 0)
	{
		mutation_rate_real = (Real)(1.0) / mutation_rate;
	}

	Index tournament_size = GetParameterValue("tournament_size");

	if (tournament_size > population_size_max)
	{
		tournament_size = population_size_max;
	}

	bool elitism = false;

	if (GetParameterValue("tournament_size") > 0)
	{
		elitism = true;
	}

	if (population_size == 0)
	{
		return path;
	}

	//Tworzenie pocz¹tkowej populacji.
	Population population = Population(this->graph, start, population_size, true);

	//Ewolucja populacji.
	for (Index i = 0; i < iterations; i++)
	{
		population = EvolvePopulation(population, mutation_rate_real, tournament_size, elitism);
	}

	//Wybór najlepszego cz³onka populacji.
	return population.GetPathBest();
}

const std::string TspAlgorithmGenetic::GetName() const
{
	return "TspAlgorithmGenetic";
}

const std::string TspAlgorithmGenetic::GetTitle() const
{
	return "Tsp Algorithm Genetic";
}

const std::string TspAlgorithmGenetic::GetDescription() const
{
	return "TSP algorithm Genetic";
}

const Parameters TspAlgorithmGenetic::GetParametersDefault() const
{
	return { { "iterations", Parameter(GetName(), "iterations", 100, "iteration count") },{ "population_size", Parameter(GetName(), "population_size", 50, "population_size") },{ "mutation_rate", Parameter(GetName(), "mutation_rate", 66, "mutation rate (1/x)") },{ "tournament_size", Parameter(GetName(), "tournament_size", 5, "tournament size") },{ "elitism", Parameter(GetName(), "elitism", 1, "elitism (boolean)") } };
}
