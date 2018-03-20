#pragma once

#include "CompleteGraph.h"
#include <iostream>
#include <vector>

//Klasa pomocnicza do wyœwietlania pojedynczych wartoœci oraz listy tych wartoœci.
template <typename T>
class DisplayHelper
{
	//W zale¿noœci od tego czy mamy do czynienia z numerami wierzcho³ków czy te¿ z ich wartoœciami, u¿yj listy z³o¿onej z odpowiednich typów.
	using List = typename std::conditional<std::is_same<T, Index>::value,Path,Vector>::type;

protected:
	DisplayHelper() {};
	~DisplayHelper() {};

public:
	//Wyœwietlanie pojedynczej zmiennej.
	static void DisplayVar(const T & var, std::ostream & stream = std::cout, bool newline = true)
	{
		stream << var;

		if (newline)
		{
			stream << std::endl;
		}
	}

	//Wyœwietlanie listy zmiennych.
	static void DisplayList(const List & list, std::ostream & stream = std::cout)
	{
		bool first_value = true;

		for (const auto & var : list)
		{
			//Separator na pocz¹tku nowej linii.
			if (!first_value)
			{
				stream << "\t";
			}
			else
			{
				first_value = false;
			}

			DisplayVar(var, stream, false);
		}
		stream << std::endl;
	}
};
