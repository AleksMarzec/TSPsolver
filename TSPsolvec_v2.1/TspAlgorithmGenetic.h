#pragma once

#include "TspAlgorithm.h"
#include "CompleteGraph.h"
#include "Population.h"
#include <memory>

//Tsp.
//Klasa "impementuj¹ca" TspAlgorithm.
class TspAlgorithmGenetic : public TspAlgorithm
{
protected:
	Path ResolveTsp();
	Population EvolvePopulation(const Population & population, const Real & mutation_rate_real, const Index & tournament_size, const bool & elitism = true);
	Path Crossover(const Path & parent1, const Path & parent2);
	bool MutateHere(Path & path, const Real & mutation_rate_real);
	Path Mutate(const Path & path, const Real & mutation_rate_real);
	Path TournamentSelection(const Population & population, const Index & tournament_size);

public:
	TspAlgorithmGenetic();
	TspAlgorithmGenetic(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithmGenetic(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithmGenetic(const TspAlgorithm & tsp);
	~TspAlgorithmGenetic();
	const std::string GetName() const;
	const std::string GetTitle() const;
	const std::string GetDescription() const;
	const Parameters GetParametersDefault() const;
};