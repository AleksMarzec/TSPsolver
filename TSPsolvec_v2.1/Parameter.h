#pragma once

#include "CompleteGraph.h"
#include <map>

//Parameter.
//Wszystkie algorytmy korzystaj¹ z takiej samej struktury parametrów.
class Parameter
{
protected:
	std::string algorithm = "";
	std::string name = "";
	Index value = 0;
	std::string description = "";

public:
	Parameter(const std::string & algorithm, const std::string & name, const Index & value, const std::string & description = "");
	Parameter(const std::string & name, const Index & value, const std::string & description = "");
	~Parameter();
	std::string GetAlgorithm() const;
	void SetAlgorithm(const std::string & algorithm);
	std::string GetName() const;
	void SetName(const std::string & name);
	Index GetValue() const;
	void SetValue(const Index & value);
	std::string GetDescription() const;
	void SetDescription(const std::string & description);
	bool IsValid() const;
};

using Parameters = std::map<std::string, Parameter>;
using ParametersAll = std::map<std::string, Parameters>;
