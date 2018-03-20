#pragma once

#include "CompleteGraph.h"
#include <iostream>
#include <random>

//Klasa pomocnicza do obs³ugi grafu.
class CompleteGraphHelper
{
	//Ujednolicenie funkcji losuj¹cej zarówno dla liczb ca³kowitych jak i zmiennoprzecinkowych.
	using uniform_distribution = typename std::conditional<std::is_integral<Value>::value,
		std::uniform_int_distribution<Value>,
		std::uniform_real_distribution<Value>
	>::type;

protected:
	CompleteGraphHelper();
	~CompleteGraphHelper();

public:
	static Value GetRandomValue(const Value & min, const Value & max);
	static Index GetRandomIndex(const Index & min, const Index & max);
	static Real GetRandomReal(const Real & min = 0.0, const Real & max = 1.0);
	static void DisplayIndex(const Index & index, std::ostream & stream = std::cout, bool newline = true);
	static void DisplayValue(const Value & value, std::ostream & stream = std::cout, bool newline = true);
	static void DisplayPath(const Path & path, std::ostream & stream = std::cout);
	static void DisplayVector(const Vector & vector, std::ostream & stream = std::cout);
	static Path GetPath(const CompleteGraph & graph, const Index & start = 0);
	static Path GetWalk(const CompleteGraph & graph, const Index & start = 0);
	static Path GetCycle(const CompleteGraph & graph, const Index & start = 0);
	static Path GetPathRandom(const CompleteGraph & graph, const Index & start = 0);
	static Path GetWalkRandom(const CompleteGraph & graph, const Index & start = 0);
	static Path GetCycleRandom(const CompleteGraph & graph, const Index & start = 0);
	static Path GetRealPath(const CompleteGraph & graph, const Path & path);
	static Path ShiftPath(const Path & path, const Index & start = 0);
	static bool PathSwapVerticesHere(Path & path, const Index & i, const Index & j);
	static Path PathSwapVertices(const Path & path, const Index & i, const Index & j);
	static bool IsValidPath(const CompleteGraph & graph, const Path & path);
	static bool IsValidCycle(const CompleteGraph & graph, const Path & path);
	static bool IsValidPathHamiltonian(const CompleteGraph & graph, const Path & path, const bool & is_cycle = false);
	static bool IsValidCycleHamiltonian(const CompleteGraph & graph, const Path & path);
	static CompleteGraph GenerateRandomGraph(const Index & size = 8, const Value & min = 1, const Value & max = 127);
	static CompleteGraph ReadGraph(std::istream & stream = std::cin);
	static CompleteGraph ReadGraphFromFile(std::string & filename);
	static Vector GetPathCosts(const CompleteGraph & graph, const Path & path);
	static Value GetPathCostFromCostsVector(const CompleteGraph & graph, const Vector & costs);
	static Value GetPathCostFromPath(const CompleteGraph & graph, const Path & path);
	static Value GetPathCost(const CompleteGraph & graph, const Path & path);
	static void DisplayPath(const CompleteGraph & graph, const Path & path, const bool & display_indexes = true, const bool & display_costs = true, const bool & display_cost = true, std::ostream & stream = std::cout);
	static void DisplayGraph(const CompleteGraph & graph, std::ostream & stream = std::cout);
};