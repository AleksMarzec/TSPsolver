#include "Parameter.h"

Parameter::Parameter(const std::string & algorithm, const std::string & name, const Index & value, const std::string & description)
{
	this->algorithm = algorithm;
	this->name = name;
	this->value = value;
	this->description = description;
}

Parameter::Parameter(const std::string & name, const Index & value, const std::string & description)
{
	this->algorithm = "";
	this->name = name;
	this->value = value;
	this->description = description;
}

Parameter::~Parameter()
{

}


std::string Parameter::GetAlgorithm() const
{
	return this->algorithm;
}

void Parameter::SetAlgorithm(const std::string & algorithm)
{
	this->algorithm = algorithm;
}

std::string Parameter::GetName() const
{
	return this->name;
}

void Parameter::SetName(const std::string & name)
{
	this->name = name;
}

Index Parameter::GetValue() const
{
	return this->value;
}

void Parameter::SetValue(const Index & value)
{
	this->value = value;
}

std::string Parameter::GetDescription() const
{
	return this->description;
}

void Parameter::SetDescription(const std::string & description)
{
	this->description = description;
}

// Parametr jest prawid³owy gdy jego nazwa jest niepusta.
bool Parameter::IsValid() const
{
	if (this->name != "")
	{
		return true;
	}
	else
	{
		return false;
	}
}

