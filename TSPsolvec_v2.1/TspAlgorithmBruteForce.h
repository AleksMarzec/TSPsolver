#pragma once
#include "TspAlgorithm.h"
#include "CompleteGraph.h"
#include <memory>

//Tsp.
//Klasa "impementuj¹ca" TspAlgorithm.
class TspAlgorithmBruteForce : public TspAlgorithm
{
protected:
	Path ResolveTsp();

public:
	TspAlgorithmBruteForce();
	TspAlgorithmBruteForce(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithmBruteForce(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithmBruteForce(const TspAlgorithm & tsp);
	~TspAlgorithmBruteForce();
	const std::string GetName() const;
	const std::string GetTitle() const;
	const std::string GetDescription() const;
	const Parameters GetParametersDefault() const;
};