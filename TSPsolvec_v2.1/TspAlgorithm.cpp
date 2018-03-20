#include "TspAlgorithm.h"
#include "CompleteGraphHelper.h"

//https://isocpp.org/wiki/faq/strange-inheritance#calling-virtuals-from-ctors
TspAlgorithm::TspAlgorithm()
{
	this->graph = nullptr;
	this->path = nullptr;
	this->parameters = nullptr;
}

TspAlgorithm::TspAlgorithm(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm()
{
	this->graph = graph;
	this->path = path;
	this->parameters = parameters;
}

TspAlgorithm::TspAlgorithm(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters) : TspAlgorithm::TspAlgorithm()
{
	this->graph = graph;
	if (graph != nullptr)
	{
		Path path = CompleteGraphHelper::GetCycle(*graph.get(), start);
		this->path = std::make_shared<const Path>(path);
	}
	else
	{
		this->path = nullptr;
	}
	this->parameters = parameters;
}

TspAlgorithm::TspAlgorithm(const TspAlgorithm & tsp) : TspAlgorithm::TspAlgorithm()
{
	this->graph = tsp.graph;
	this->path = tsp.path;
	this->parameters = tsp.parameters;
}


TspAlgorithm::~TspAlgorithm()
{

}

//W�a�ciwa metoda rozwi�zywania problemu komiwoja�era.
Path TspAlgorithm::ResolveTsp()
{
	return CompleteGraphHelper::GetCycle(*(this->graph), GetStartPoint());
}

//Sprawdzanie poprawno�ci.
bool TspAlgorithm::IsValid() const
{
	if (this->graph == nullptr || this->path == nullptr)
	{
		return false;
	}

	if (!this->graph.get()->IsValid())
	{
		return false;
	}

	if (!CompleteGraphHelper::IsValidCycleHamiltonian(*(this->graph).get(), *(this->path).get()))
	{
		return false;
	}

	return true;
}

//Wywo�uje w�a�ciw� metod� ResolveTsp.
//Tutaj rozwi�zujemy jedynie najprostsze przypadki, aby nie musie� robi� tego ju� p�niej we w�a�ciwej metodzie.
Path TspAlgorithm::Resolve()
{
	if (IsValid() == true)
	{
		Index size = this->graph.get()->GetSize();
		if (size <= 2)
		{
			if (size == 0)
			{
				return {};
			}
			else if (size == 1)
			{
				return  { 0, 0 };
			}
			else
			{
				return CompleteGraphHelper::GetCycle(*(this->graph).get(), GetStartPoint());
			}
		}

		return ResolveTsp();
	}
	else
	{
		return {};
	}
}

const std::string TspAlgorithm::GetName() const
{
	return "TSP";
}

const std::string TspAlgorithm::GetTitle() const
{
	return "TSP";
}

const std::string TspAlgorithm::GetDescription() const
{
	return "Klasa abstrakcyjna dla TSP";
}

void TspAlgorithm::SetGraph(std::shared_ptr<const CompleteGraph> graph)
{
	this->graph = graph;
}

void TspAlgorithm::SetPath(std::shared_ptr<const Path> path)
{
	this->path = path;
}

std::shared_ptr<const CompleteGraph> TspAlgorithm::GetGraph() const
{
	return this->graph;
}

std::shared_ptr<const Path> TspAlgorithm::GetPath() const
{
	return this->path;
}

//Pobieranie punktu pocz�tkowego.
Index TspAlgorithm::GetStartPoint() const
{
	if (this->path.get()->size() > 0)
	{
		return this->path.get()->front();
	}
	else
	{
		return 0;
	}
}

//Pobieranie domy�lnych parametr�w dla algorytmu.
const Parameters TspAlgorithm::GetParametersDefault() const
{
	return {};
}

//Pobieranie parametr�w wprowadzonych przez u�ytkownika.
std::shared_ptr<const ParametersAll> TspAlgorithm::GetParametersInput() const
{
	return this->parameters;
}

//Ustawianie parametr�w wprowadzonych przez u�ytkownika.
void TspAlgorithm::SetParametersInput(const std::shared_ptr<const ParametersAll> & parameters)
{
	this->parameters = parameters;
}

//Zwraca parametry przeznaczone tylko i wy��cznie do tego algorytmu.
const std::shared_ptr<const Parameters> TspAlgorithm::GetParameters() const
{
	if (this->parameters != nullptr)
	{
		auto parameters = this->parameters.get()->find(GetName());

		// Je�li zbi�r zawiera parametry dla tego algorytmu
		if (parameters != this->parameters.get()->end())
		{
			return std::make_shared<const Parameters>(parameters->second);
		}
	}

	// Zwr�� null je�li niczego nie znaleziono.
	return nullptr;
}

//Pobieranie parametru po jego nazwie.
const std::shared_ptr<const Parameter> TspAlgorithm::GetParameter(const std::string & name) const
{
	if (this->parameters != nullptr)
	{
		auto parameters = this->parameters.get()->find(GetName());

		//Je�li zbi�r zawiera parametry dla tego algorytmu
		if (parameters != this->parameters.get()->end())
		{
			auto parameter = parameters->second.find(name);
			if (parameter != parameters->second.end())
			{
				return std::make_shared<const Parameter>(parameter->second);
			}
		}
	}

	//Je�li nie znaleziono parametru o podanej nazwie to szukaj w domy�lnych
	auto parameters_default = GetParametersDefault();
	auto parameter_default = parameters_default.find(name);

	if (parameter_default != parameters_default.end())
	{
		return std::make_shared<const Parameter>(parameter_default->second);
	}

	// Zwr�� null je�li niczego nie znaleziono.
	return nullptr;
}

//Pobieranie warto�ci parametru po jego nazwie.
Index TspAlgorithm::GetParameterValue(const std::string & name) const
{
	const std::shared_ptr<const Parameter> parameter = GetParameter(name);
	if (parameter != nullptr)
	{
		return parameter->GetValue();
	}

	return 0;
}

//Pobieranie parametr�w wynikowych (tzn. domy�lnych + wprowadzonych przez u�ytkownika).
const Parameters TspAlgorithm::GetParametersResult() const
{
	Parameters parameters;
	parameters = GetParametersDefault();

	std::shared_ptr<const Parameters> parameters_input = GetParameters();

	if (parameters_input != nullptr)
	{
		for (const auto & kv : *parameters_input)
		{
			auto parameter = parameters.find(kv.first);

			if (parameter != parameters.end())
			{
				parameter->second.SetValue(kv.second.GetValue());
			}
			else
			{
				parameters.insert({ kv.first, kv.second });
			}
		}
	}

	return parameters;
}

