#include "TspHelper.h"
#include "TspFactory.h"
#include "Singleton.h"
#include <string>

TspHelper::TspHelper()
{

}

TspHelper::~TspHelper()
{

}


//Wy�wietlanie nazw dost�pnych algorytm�w.
void TspHelper::DisplayAlgorithmNames(std::ostream & stream)
{
	for (const std::string & algorithm_name : TspFactory::GetAlgorithmNames())
	{
		stream << algorithm_name << std::endl;
	}
}

//Wy�wietlanie parametr�w algorytmu.
void TspHelper::DisplayAlgorithmParameters(const Parameters & parameters, bool display_description, std::ostream & stream)
{
	for (const auto & kv : parameters)
	{
		stream << "- " << kv.second.GetName() << "(" << kv.second.GetValue() << ")";
		if (display_description == true && kv.second.GetDescription() != "")
		{
			stream << ": " << kv.second.GetDescription();
		}
		stream << std::endl;
	}
}

//Wy�wietlanie parametr�w algorytmu.
void TspHelper::DisplayAlgorithmParameters(const TspAlgorithm & tsp, bool display_description, std::ostream & stream)
{
	DisplayAlgorithmParameters(tsp.GetParametersResult(), display_description, stream);
}

//Wy�wietlanie parametr�w wszystkich dost�pnych algorytm�w.
void TspHelper::DisplayAlgorithmParametersAll(const ParametersAll & parameters, bool display_description, std::ostream & stream)
{
	for (const auto & kv : parameters)
	{
		stream << kv.first << std::endl;
		DisplayAlgorithmParameters(kv.second, display_description, stream);
	}
}

//Wy�wietlanie parametr�w dla wszystkich dost�pnych algorytm�w.
void TspHelper::DisplayAlgorithmParametersAll(bool display_description, std::ostream & stream)
{
	DisplayAlgorithmParametersAll(Singleton<TspFactory>::Instance().GetAlgorithmParametersAll(), display_description, stream);
}

