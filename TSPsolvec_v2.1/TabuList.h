#pragma once
#include "CompleteGraph.h"
#include <vector>

//Lista tabu.
//Klasa pomocnicza dla TspAlgorithmTabuSearch.
class TabuList
{
protected:
	Index size = 0;
	Index max = 0;
	std::vector<std::vector<Index>> tabu = {};
	void TabuDecrement();
public:
	TabuList(const Index & size, const Index & max);
	TabuList(const TabuList & tabulist);
	~TabuList();
	Index GetSize() const;
	Index GetMax() const;
	bool TabuAdd(const Index & i, const Index & j);
	bool TabuCheck(const Index & i, const Index & j);
	void TabuClear();
};