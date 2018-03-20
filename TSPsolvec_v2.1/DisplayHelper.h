#pragma once

#include "CompleteGraph.h"
#include <iostream>
#include <vector>

//Klasa pomocnicza do wy�wietlania pojedynczych warto�ci oraz listy tych warto�ci.
template <typename T>
class DisplayHelper
{
	//W zale�no�ci od tego czy mamy do czynienia z numerami wierzcho�k�w czy te� z ich warto�ciami, u�yj listy z�o�onej z odpowiednich typ�w.
	using List = typename std::conditional<std::is_same<T, Index>::value,Path,Vector>::type;

protected:
	DisplayHelper() {};
	~DisplayHelper() {};

public:
	//Wy�wietlanie pojedynczej zmiennej.
	static void DisplayVar(const T & var, std::ostream & stream = std::cout, bool newline = true)
	{
		stream << var;

		if (newline)
		{
			stream << std::endl;
		}
	}

	//Wy�wietlanie listy zmiennych.
	static void DisplayList(const List & list, std::ostream & stream = std::cout)
	{
		bool first_value = true;

		for (const auto & var : list)
		{
			//Separator na pocz�tku nowej linii.
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
