#pragma once

#include "CompleteGraph.h"
#include "Parameter.h"
#include <memory>
#include <map>

//Tsp.
//Klasa bazowa do rozwi¹zywania problemu komiwoja¿era - TSP.
class TspAlgorithm
{
protected:
	std::shared_ptr<const CompleteGraph> graph = nullptr; //Graf.
	std::shared_ptr<const Path> path = nullptr; //Œcie¿ka pocz¹tkowa (a w zasadzie cykl). Zawiera równiez punkt startowy.
	std::shared_ptr<const ParametersAll> parameters = nullptr; //Parametry. Przechowuje parametry wprowadzone przez u¿ytkownika dla wszystkich wybranych algorytmów.
	virtual Path ResolveTsp() = 0; // W³aœciwa funkcja rozwi¹zuj¹ca problem komiwoja¿era.

public:
	TspAlgorithm();
	TspAlgorithm(const std::shared_ptr<const CompleteGraph> & graph, const std::shared_ptr<const Path> & path, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithm(const std::shared_ptr<const CompleteGraph> & graph, const Index & start, const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	TspAlgorithm(const TspAlgorithm & tsp);
	virtual ~TspAlgorithm();
	bool IsValid() const;
	Path Resolve();
	virtual const std::string GetName() const;
	virtual const std::string GetTitle() const;
	virtual const std::string GetDescription() const;
	void SetGraph(std::shared_ptr<const CompleteGraph> graph);
	void SetPath(std::shared_ptr<const Path> path);
	std::shared_ptr<const CompleteGraph> GetGraph() const;
	std::shared_ptr<const Path> GetPath() const;
	Index GetStartPoint() const;
	virtual const Parameters GetParametersDefault() const;
	std::shared_ptr<const ParametersAll> GetParametersInput() const;
	void SetParametersInput(const std::shared_ptr<const ParametersAll> & parameters = nullptr);
	const std::shared_ptr<const Parameters> GetParameters() const;
	const std::shared_ptr<const Parameter> GetParameter(const std::string & name) const;
	Index GetParameterValue(const std::string & name) const;
	const Parameters GetParametersResult() const;
};