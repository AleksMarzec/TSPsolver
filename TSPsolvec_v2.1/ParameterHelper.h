#pragma once

#include "Parameter.h"
#include <vector>

//Klasa pomocnicza do obs³ugi parametrów.
class ParameterHelper
{

protected:
	ParameterHelper();
	~ParameterHelper();
	static std::vector<std::string> SplitText(const std::string & text, char delim = ':');

public:
	static Parameter ParseParameter(const std::string & text);
	static ParametersAll ParseParameters(const std::vector<std::string> & texts);
	static ParametersAll ParseParameters(const std::vector<Parameter> & parameters);
};


