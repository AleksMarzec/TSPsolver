#include "Population.h"
#include "CompleteGraphHelper.h"

Population::Population(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const Index & population_size, const bool & initialise)
{
	this->graph = graph;
	this->start = start;
	Index population_size_actual = population_size;
	Index population_size_max = GetPopulationSizeMax();

	if (population_size_max > this->paths.max_size())
	{
		population_size_max = this->paths.max_size();
	}
	if (population_size_actual > population_size_max)
	{
		population_size_actual = population_size_max;
	}

	this->paths = std::vector<Path>(population_size_actual);

	if (initialise == true)
	{
		for (Index i = 0; i < population_size_actual; i++)
		{
			this->paths[i] = CompleteGraphHelper::GetCycleRandom(*(this->graph), start);
		}
	}
}

Population::Population(const Population & population)
{
	this->graph = population.graph;
	this->start = population.start;
	this->paths = population.paths;
}

Population::~Population()
{

}

std::shared_ptr<const CompleteGraph> Population::GetGraph() const
{
	return this->graph;
}

Index Population::GetStartPoint() const
{
	return this->start;
}

bool Population::SavePath(const Index & index, const Path & path)
{
	if (index < GetPopulationSize())
	{
		this->paths[index] = path;
		return true;
	}
	else
	{
		return false;
	}
}

Path Population::GetPath(const Index & index) const
{
	if (index < GetPopulationSize())
	{
		return this->paths[index];
	}
	else
	{
		return {};
	}
}

Path Population::GetPathBest() const
{
	if (GetPopulationSize() < 1)
	{
		return {};
	}

	if (this->graph == nullptr)
	{
		return this->paths[0];
	}

	Index i_best = 0;
	Value cost_best = CompleteGraphHelper::GetPathCost(*(this->graph), this->paths[i_best]);

	for (Index i = 1; i < GetPopulationSize(); i++)
	{
		Value cost_new = CompleteGraphHelper::GetPathCost(*(this->graph), this->paths[i]);
		if (cost_new < cost_best)
		{
			i_best = i;
			cost_best = cost_new;
		}
	}

	return this->paths[i_best];
}

Index Population::GetPopulationSize() const
{
	return this->paths.size();
}

Index Population::GetPopulationSizeMax()
{
	return 1000;
}
