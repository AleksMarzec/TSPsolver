#include "ParameterHelper.h"
#include <map>
#include <regex>
#include <sstream>

ParameterHelper::ParameterHelper()
{

}

ParameterHelper::~ParameterHelper()
{

}

//Dzielenie podanego tekstu na podstawie podanego separatora.
std::vector<std::string> ParameterHelper::SplitText(const std::string & text, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss;
	ss.str(text);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		result.push_back(item);
	}
	return result;
}

//Parsowanie Parametru w postaci tekstowej, np. "TspAlgorithmRandom:iterations:100" (format: "<Algorytm>:<Nazwa>:<Wartoœæ>").
Parameter ParameterHelper::ParseParameter(const std::string & text)
{
	bool ok = false;
	std::string algorithm_str = "";
	std::string name_str = "";
	std::string value_str = "";

	std::regex r("^([^:]+):([^:]+):([0-9]+)$", std::regex_constants::extended);
	std::smatch m;
	std::regex_search(text, m, r);
	
	//Jeœli mamy dok³adnie 1+3 pola.
	if (m.size() == 4)
	{
		algorithm_str = m[1];
		name_str = m[2];
		value_str = m[3];
		ok = true;
	}

	if (ok == true)
	{
		std::stringstream ss(value_str);
		Index value;
		ss >> value;
		
		//Jeœli uda³o siê poprawnie skonwertowaæ tekst na liczbê to kontynuuj - https://stackoverflow.com/a/14900108.
		if (!ss.fail() && ss.eof())
		{
			return Parameter(algorithm_str, name_str, value);
		}
	}

	return Parameter("", "", 0);
}

//Parsowanie wekora parametrów w postaci tekstowej.
ParametersAll ParameterHelper::ParseParameters(const std::vector<std::string> & texts)
{
	std::vector<Parameter> parameters = {};
	for (const std::string & text : texts)
	{
		Parameter parameter = ParseParameter(text);

		if (parameter.IsValid() == true)
		{
			parameters.push_back(parameter);
		}
	}

	return ParseParameters(parameters);
}

//Parsowanie wekora parametrów.
ParametersAll ParameterHelper::ParseParameters(const std::vector<Parameter> & parameters)
{
	ParametersAll parameters_all = {};
	for (const Parameter & parameter : parameters)
	{
		if (parameter.IsValid() == true)
		{
			auto p = parameters_all.find(parameter.GetAlgorithm());
			if (p != parameters_all.end())
			{
				auto r = p->second.find(parameter.GetName()); 
				if (r != p->second.end())
				{
					r->second.SetValue(parameter.GetValue());
				}
				else
				{
					p->second.insert({ parameter.GetName(), parameter });
				}
			}
			else
			{
				Parameters parameters_new = { { parameter.GetName(), parameter } };
				parameters_all.insert({ parameter.GetAlgorithm(), parameters_new });
			}
		}
	}
	return parameters_all;
}
