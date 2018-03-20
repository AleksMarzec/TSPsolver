#pragma once

#include "CompleteGraph.h"
#include <vector>
#include <memory>

//Populacja.
//Klasa pomocnicza dla TspAlgorithmGenetic.
class Population
{
protected:
	std::shared_ptr<const CompleteGraph> graph = nullptr; // Graf.
	std::vector<Path> paths = {};
	Index start = 0;

public:
	Population(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const Index & population_size, const bool & initialise = true);
	Population(const Population & population);
	~Population();
	std::shared_ptr<const CompleteGraph> GetGraph() const;
	Index GetStartPoint() const;
	bool SavePath(const Index & index, const Path & path);
	Path GetPath(const Index & index) const;
	Path GetPathBest() const;
	Index GetPopulationSize() const;
	static Index GetPopulationSizeMax();
};
