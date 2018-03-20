#include "TabuList.h"

TabuList::TabuList(const Index & size, const Index & max)
{
	if (size > 0)
	{
		this->tabu = std::vector<std::vector<Index>>(size, std::vector<Index>(size, 0));
		this->size = size;
	}
	else
	{
		this->tabu = {};
		this->size = 0;
	}
	this->max = max;
}

TabuList::TabuList(const TabuList & tabulist)
{
	this->tabu = tabulist.tabu;
	this->size = tabulist.size;
	this->max = tabulist.max;
}

TabuList::~TabuList()
{

}


//Zwraca rozmiar macierzy.
Index TabuList::GetSize() const
{
	return this->size;
}

//Zwraca maksymalny rozmiar tabu.
Index TabuList::GetMax() const
{
	return this->max;
}

//Dodaje tabu.
bool TabuList::TabuAdd(const Index & i, const Index & j)
{
	if (i > j)
	{
		return TabuAdd(j, i);
	}

	if (i < this->size && j < this->size)
	{
		if (i != j)
		{
			if (this->tabu[i][j] == 0)
			{
				TabuDecrement();
				this->tabu[i][j] = max;
				return true;
			}
		}
	}
	return false;
}

// Sprawdza czy istnieje tabu.
// Zwraca true jeœli tak.
// Zwraca false w przeciwnym wypadku.
bool TabuList::TabuCheck(const Index & i, const Index & j)
{
	if (i > j)
	{
		return TabuCheck(j, i);
	}

	if (i < this->size && j < this->size)
	{
		if (i != j)
		{
			if (this->tabu[i][j] > 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

//Czyœci tabu.
void TabuList::TabuClear()
{
	this->tabu = std::vector<std::vector<Index>>(size, std::vector<Index>(size, 0));
}

//Redukuje tabu.
void TabuList::TabuDecrement()
{
	for (Index i = 0; i < this->size; i++)
	{
		for (Index j = i + 1; j < this->size; j++)
		{
			if (this->tabu[i][j] > 0)
			{
				this->tabu[i][j]--;
			}
		}
	}
}
