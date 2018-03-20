#include "CompleteGraph.h"
#include <limits>

CompleteGraph::CompleteGraph()
{
	this->valid = false;
}

CompleteGraph::CompleteGraph(const Matrix & matrix) : CompleteGraph()
{
	this->matrix = matrix;

	this->Check();
}

CompleteGraph::CompleteGraph(const CompleteGraph & graph) : CompleteGraph()
{
	this->matrix = graph.matrix;

	this->valid = graph.valid;
}

CompleteGraph::~CompleteGraph()
{

}


bool CompleteGraph::Check()
{
	bool valid = true;

	auto size = this->matrix.size();
	if (size < 1)
	{
		valid = false;
	}

	if (valid)
	{
		for (const auto & vector : this->matrix)
		{
			if (vector.size() != size)
			{
				valid = false;
				break;
			}
		}
	}

	if (valid)
	{
		for (Index i = 0; i < this->matrix.size(); i++)
		{
			if (this->matrix[i][i] != 0)
			{
				valid = false;
				break;
			}
		}
	}

	this->valid = valid;
	return valid;
}

bool CompleteGraph::IsValid() const
{
	return this->valid;
}

bool CompleteGraph::IsSymmetrical() const
{
	if (!this->valid)
	{
		return false;
	}
	else
	{
		auto size = this->matrix.size();

		if (size < 2)
		{
			return true;
		}

		for (Index i = 0; i < size; i++)
		{
			for (Index j = i + 1; j < size; j++)
			{
				if (this->matrix[i][j] < this->matrix[j][i])
				{
					return false;
				}
			}
		}

		return true;
	}
}

Index CompleteGraph::GetSize() const
{
	if (!this->valid)
	{
		return 0;
	}
	else
	{
		return this->matrix.size();
	}
}

MinMax CompleteGraph::GetMinMax() const
{
	Value value_min = 0;
	Value value_max = 0;

	if (!this->valid)
	{
		value_min = std::numeric_limits<Value>::lowest();
		value_max = std::numeric_limits<Value>::max();
	}
	else
	{
		auto size = this->matrix.size();
		if (size < 2)
		{
			//Wartoœci na diagonali s¹ równe zero (w przeciwnym razie graf jest niepoprawny). Dlatego bez this->matrix[0][0].
			value_min = 0;
			value_max = 0;
		}
		else
		{
			value_min = this->matrix[0][1];
			value_max = this->matrix[0][1];

			// Musimy przeanalizowaæ n * n - n wartoœci. Ich liczba jest zawsze parzysta.
			for (Index i = 0; i < size; i++)
			{
				for (Index j = 0; j < size; j++)
				{
					//Pomijamy wartoœci na diagonali.
					if (i == j)
					{
						continue;
					}
					if (this->matrix[i][j] < value_min)
					{
						value_min = this->matrix[i][j];
					}
					if (this->matrix[i][j] > value_max)
					{
						value_max = this->matrix[i][j];
					}
				}
			}
		}
	}

	MinMax minmax{ value_min, value_max };
	return minmax;
}

const Matrix * CompleteGraph::GetMatrix() const
{
	if (!this->valid)
	{
		return nullptr;
	}
	else
	{
		return &this->matrix;
	}
}

const Vector * CompleteGraph::GetVector(const Index & i) const
{
	if (!this->valid)
	{
		return nullptr;
	}
	else
	{
		auto size = this->matrix.size();
		if (i >= 0 && i < size)
		{
			return &this->matrix[i];
		}
		else
		{
			return nullptr;
		}
	}
}

const Value * CompleteGraph::GetValue(const Index & i, const Index & j) const
{
	if (!this->valid)
	{
		return nullptr;
	}
	else
	{
		auto size = this->matrix.size();
		if (i >= 0 && i < size && j >= 0 && j < size)
		{
			return &this->matrix[i][j];
		}
		else
		{
			return nullptr;
		}
	}
}

const Value CompleteGraph::GetCost(const Index & i, const Index & j) const
{
	const Value * value = GetValue(i, j);
	if (value != nullptr)
	{
		return *value;
	}
	else
	{
		return 0;
	}
}

