#pragma once

#include <vector>
#include <array>

using Real = float; // Typ u¿ywany jako liczba zmiennoprzecinkowa.
using Index = unsigned int; // Typ u¿ywany jako wartoœæ pozycji i rozmiaru.
using Value = unsigned int; // Typ u¿ywany jako wartoœæ wektora i macierzy.
using Vector = std::vector<Value>;
using Matrix = std::vector<Vector>;
using MinMax = std::pair<Value, Value>;
using Path = std::vector<Index>;

//Graf Pe³ny
//Jest reprezentowany przez macierz kwadratow¹ definiuj¹c¹ odleg³oœci pomiêdzy poszczególnymi krawêdziami.
class CompleteGraph
{
protected:
	Matrix matrix;
	bool valid = false;
	bool Check();

public:
	CompleteGraph();
	CompleteGraph(const Matrix & matrix);
	CompleteGraph(const CompleteGraph & graph);
	virtual ~CompleteGraph();
	bool IsValid() const;
	bool IsSymmetrical() const;
	Index GetSize() const;
	MinMax GetMinMax() const;
	const Matrix * GetMatrix() const;
	const Vector * GetVector(const Index & i) const;
	const Value * GetValue(const Index & i, const Index & j) const;
	const Value GetCost(const Index & i, const Index & j) const;
};
