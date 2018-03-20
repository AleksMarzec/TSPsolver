#pragma once

#include "TspAlgorithm.h"
#include "CompleteGraph.h"
#include <memory>

//Tsp.
//Przyk³adowa klasa "impementuj¹ca" TspAlgorithm.
class TspAlgorithmRandom : public TspAlgorithm
{
protected:
	Path ResolveTsp();

public:
	TspAlgorithmRandom();
	TspAlgorithmRandom(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithmRandom(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithmRandom(const TspAlgorithm & tsp);
	~TspAlgorithmRandom();
	const std::string GetName() const;
	const std::string GetTitle() const;
	const std::string GetDescription() const;
	const Parameters GetParametersDefault() const;
};