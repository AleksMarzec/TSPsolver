#pragma once

#include "TspAlgorithm.h"
#include <iostream>

//Klasa pomocnicza do obs³ugi algorytmów TSP.
class TspHelper
{
protected:
	TspHelper();
	~TspHelper();

public:
	static void DisplayAlgorithmNames(std::ostream & stream = std::cout);
	static void DisplayAlgorithmParameters(const Parameters & parameters, bool display_description = true, std::ostream & stream = std::cout);
	static void DisplayAlgorithmParameters(const TspAlgorithm & tsp, bool display_description = true, std::ostream & stream = std::cout);
	static void DisplayAlgorithmParametersAll(const ParametersAll & parameters, bool display_description = true, std::ostream & stream = std::cout);
	static void DisplayAlgorithmParametersAll(bool display_description = true, std::ostream & stream = std::cout);
};
