#pragma once

#include "TspAlgorithm.h"
#include "CompleteGraph.h"
#include <vector>
#include <iostream>

//Klasa odpowiada za zarz¹dzanie zbiorem obiektów TspAlgorithm.
class TspManager
{
protected:
	std::shared_ptr<const std::vector<std::string>> algorithm_names = nullptr; //Nazwy algorytmów.
	std::shared_ptr<const CompleteGraph> graph = nullptr; //Graf.
	std::shared_ptr<const Index> start = nullptr; //Punkt pocz¹tkowy.
	std::shared_ptr<const ParametersAll> parameters = nullptr; //Parametry.

public:
	TspManager(const std::shared_ptr<const std::vector<std::string>> & algorithm_names, const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Index> & start, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	~TspManager();
	void SetAlgorithms(std::shared_ptr<const std::vector<std::string>> algorithm_names);
	std::shared_ptr<const std::vector<std::string>> GetAlgorithms() const;
	void SetGraph(std::shared_ptr<const CompleteGraph> graph);
	std::shared_ptr<const CompleteGraph> GetGraph() const;
	void SetStartPoint(std::shared_ptr<const Index> start);
	std::shared_ptr<const Index> GetStartPoint() const;
	void SetParameters(std::shared_ptr<const ParametersAll> parameters);
	std::shared_ptr<const ParametersAll> GetParameters() const;
	void Info(std::ostream & stream = std::cout, std::ostream & stream_errors = std::cerr);
	void Execute(const bool & verbose = true, std::ostream & stream = std::cout, std::ostream & stream_errors = std::cerr);
};