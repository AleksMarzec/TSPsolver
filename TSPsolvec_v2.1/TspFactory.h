#pragma once

#include "Singleton.h"
#include "TspAlgorithm.h"
#include <vector>
#include <memory>

//Metoda wytwórcza dla algorytmów TSP (factory method), https://en.wikipedia.org/wiki/Factory_method_pattern.
class TspFactory
{
	friend class Singleton<TspFactory>; //Ze wzglêdu na funkcjê GetAlgorithmParametersAll().

protected:
	TspFactory();
	~TspFactory();
	ParametersAll parameters = {}; //GetAlgorithmParametersAll()

public:
	static const std::vector<std::string> GetAlgorithmNames();
	static const bool CheckAlgorithmName(const std::string & name);
	static std::shared_ptr<TspAlgorithm> CreateAlgorithm(const std::string & name, const std::shared_ptr<const CompleteGraph> & graph, const Index & start = 0, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	static std::vector<std::shared_ptr<TspAlgorithm>> CreateAlgorithms(const std::vector<std::string> & names, const std::shared_ptr<const CompleteGraph> & graph, const Index & start = 0, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	static std::vector<std::shared_ptr<TspAlgorithm>> CreateAlgorithmsAll(const std::shared_ptr<const CompleteGraph> & graph, const Index & start = 0, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	const ParametersAll GetAlgorithmParametersAll() const;
};