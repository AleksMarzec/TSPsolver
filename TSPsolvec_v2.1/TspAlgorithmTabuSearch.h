#pragma once

#include "TspAlgorithm.h"
#include "CompleteGraph.h"
#include "TabuList.h"
#include <memory>

//Tsp.
//Klasa "impementuj¹ca" TspAlgorithm.
class TspAlgorithmTabuSearch : public TspAlgorithm
{
protected:
	Path ResolveTsp();
	bool GetBestNeighbour(Path & path, Value & cost, TabuList & tabu);

public:
	TspAlgorithmTabuSearch();
	TspAlgorithmTabuSearch(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithmTabuSearch(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithmTabuSearch(const TspAlgorithm & tsp);
	~TspAlgorithmTabuSearch();
	const std::string GetName() const;
	const std::string GetTitle() const;
	const std::string GetDescription() const;
	const Parameters GetParametersDefault() const;
};