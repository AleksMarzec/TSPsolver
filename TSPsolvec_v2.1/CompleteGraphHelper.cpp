#include "CompleteGraphHelper.h"
#include "DisplayHelper.h"
#include <sstream>
#include <fstream>
#include <algorithm>

CompleteGraphHelper::CompleteGraphHelper()
{

}

CompleteGraphHelper::~CompleteGraphHelper()
{

}

//Zwracanie losowej warto�ci typu Value z zakresu od min do max.
Value CompleteGraphHelper::GetRandomValue(const Value & min, const Value & max)
{
	static std::random_device r;
	static std::default_random_engine e(r());
	uniform_distribution d(min, max);
	return d(e);
}

//Zwracanie losowej warto�ci typu Index z zakresu od min do max.
Index CompleteGraphHelper::GetRandomIndex(const Index & min, const Index & max)
{
	static std::random_device r;
	static std::default_random_engine e(r());
	std::uniform_int_distribution<Index> d(min, max);
	return d(e);
}

//Zwracanie losowej warto�ci typu Real z zakresu od min do max.
Real CompleteGraphHelper::GetRandomReal(const Real & min, const Real & max)
{
	static std::random_device r;
	static std::default_random_engine e(r());
	std::uniform_real_distribution<Real> d(min, max);
	return d(e);
}

//Wy�wietlanie pojedynczego indeksu.
void CompleteGraphHelper::DisplayIndex(const Index & index, std::ostream & stream, bool newline)
{
	DisplayHelper<Index>::DisplayVar(index, stream, newline);
}

//Wy�wietlanie pojedynczej warto�ci.
void CompleteGraphHelper::DisplayValue(const Value & value, std::ostream & stream, bool newline)
{
	DisplayHelper<Value>::DisplayVar(value, stream, newline);
}

//Wy�wietlanie wektora indeks�w.
void CompleteGraphHelper::DisplayPath(const Path & path, std::ostream & stream)
{
	DisplayHelper<Index>::DisplayList(path, stream);
}

//Wy�wietlanie wektora warto�ci.
void CompleteGraphHelper::DisplayVector(const Vector & vector, std::ostream & stream)
{
	DisplayHelper<Value>::DisplayList(vector, stream);
}

//Tworzenie scie�ki.
Path CompleteGraphHelper::GetPath(const CompleteGraph & graph, const Index & start)
{
	Path path;

	Index size = graph.GetSize();
	Index start_real = start;
	if (start_real >= size)
	{
		start_real = 0;
	}

	if (size > 0)
	{
		path.push_back(start_real);
		for (Index i = 0; i < size; i++)
		{
			if (i == start_real)
			{
				continue;
			}
			path.push_back(i);
		}
	}

	return path;
}

//Tworzenie drogi.
Path CompleteGraphHelper::GetWalk(const CompleteGraph & graph, const Index & start)
{
	return GetPath(graph, start);
}

//Tworzenie cyklu.
Path CompleteGraphHelper::GetCycle(const CompleteGraph & graph, const Index & start)
{
	Path cycle = GetPath(graph, start);

	if (cycle.size() > 0)
	{
		cycle.push_back(cycle[0]);
	}

	return cycle;
}

//Tworzenie scie�ki losowej.
Path CompleteGraphHelper::GetPathRandom(const CompleteGraph & graph, const Index & start)
{
	Path path;

	Index size = graph.GetSize();

	if (size > 0)
	{
		Path vertices = GetPath(graph);

		if (start < size)
		{
			//Upewniamy si�, �e na pocz�tku zawsze b�dzie wierzcho�ek wskazany przez start.
			path.push_back(start);
			vertices[start] = std::move(vertices.back());
			vertices.pop_back();
		}

		while (vertices.size() > 0)
		{
			// Losujemy pozycj� z dost�pnej puli.
			Index index_random = GetRandomIndex(0, vertices.size() - 1);

			// Dodajemy warto�� do �cie�ki wynikowej.
			path.push_back(vertices[index_random]);

			// Je�li wylosowany indeks nie jest ostatni� pozycj� to zamie� go z ostatnim.	
			if (index_random < vertices.size() - 1)
			{
				//Takim spodobem algorytm dzia�a szybciej, bo nie usuwamy elementu ze �roda.
				vertices[index_random] = std::move(vertices.back());
			}
			// Usuwamy wylosowan� pozycj�.
			vertices.pop_back();
		}
	}

	return path;
}

//Tworzenie drogi losowej.
Path CompleteGraphHelper::GetWalkRandom(const CompleteGraph & graph, const Index & start)
{
	return GetPathRandom(graph, start);
}

//Tworzenie cyklu losowego.
Path CompleteGraphHelper::GetCycleRandom(const CompleteGraph & graph, const Index & start)
{
	Path cycle = GetPathRandom(graph, start);

	if (cycle.size() > 0)
	{
		cycle.push_back(cycle[0]);
	}

	return cycle;
}

//Pobieranie w�a�ciwej �cie�ki.
//Zwraca now� �cie�k� sk�adaj�c� si� tylko z punkt�w kt�re nale�� do grafu.
Path CompleteGraphHelper::GetRealPath(const CompleteGraph & graph, const Path & path)
{
	Path path_real;

	Index size = graph.GetSize();

	if (size > 0)
	{
		for (const Index & index : path)
		{
			if (index >= 0 && index < size)
			{
				path_real.push_back(index);
			}
		}
	}

	return path_real;
}

Path CompleteGraphHelper::ShiftPath(const Path & path, const Index & start)
{
	if (path.size() > 0)
	{
		bool found = false;
		Index index = 0;
		for (Index i = 0; i < path.size(); i++)
		{
			if (path[i] == start)
			{
				index = i;
				found = true;
				break;
			}
		}
		if (found == true)
		{
			if (index == 0)
			{
				return path;
			}
			else
			{
				Path path_new = {};
				for (Index i = index; i < path.size(); i++)
				{
					path_new.push_back(path[i]);
				}
				for (Index i = 0; i < index; i++)
				{
					path_new.push_back(path[i]);
				}
				return path_new;
			}
		}
		else
		{
			return path;
		}
	}
	else
	{
		return {};
	}
}

bool CompleteGraphHelper::PathSwapVerticesHere(Path & path, const Index & i, const Index & j)
{
	if (i >= 0 && i < path.size() && j >= 0 && j < path.size() && i != j)
	{
		Index temp = path[i];
		path[i] = path[j];
		path[j] = temp;
		return true;
	}
	else
	{
		return false;
	}
}

Path CompleteGraphHelper::PathSwapVertices(const Path & path, const Index & i, const Index & j)
{
	Path path_new = path;
	PathSwapVerticesHere(path_new, i, j);
	return path_new;
}

//Sprawdzanie poprawno�ci �cie�ki.
bool CompleteGraphHelper::IsValidPath(const CompleteGraph & graph, const Path & path)
{
	if (!graph.IsValid())
	{
		return false;
	}

	Index size = graph.GetSize();

	for (const Index & vector : path)
	{
		if (vector >= size)
		{
			return false;
		}
	}
	return true;
}

//Sprawdzanie poprawno�ci cyklu.
bool CompleteGraphHelper::IsValidCycle(const CompleteGraph & graph, const Path & path)
{
	if (IsValidPath(graph, path))
	{
		if (path.size() >= 2 && path.front() == path.back())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//Sprawdzanie poprawno�ci �cie�ki Hamiltona.
bool CompleteGraphHelper::IsValidPathHamiltonian(const CompleteGraph & graph, const Path & path, const bool & is_cycle)
{
	if (!graph.IsValid())
	{
		return false;
	}

	Index size = graph.GetSize();
	if (size < 1)
	{
		return false;
	}

	Index size_path;
	size_path = size;
	if (is_cycle == true)
	{
		size_path++;
	}

	if (path.size() != size_path)
	{
		return false;
	}

	//Je�li mamy do czynienia z cyklem to wierzcho�ek pocz�tkowy i ko�cowy musi by� identyczny.
	if (is_cycle == true)
	{
		if (path.front() != path.back())
		{
			return false;
		}
	}

	//Nale�y sprawdzi�, czy �cie�ka/cykl zawiera wszystkie wierzcho�ki grafu.
	std::vector<bool> indexes(size, false);

	for (Index i = 0; i < size; i++)
	{
		Index j = path[i];

		//Je�li wierzcho�ek nie nale�y do grafu - zwr�� odpowied� negatywn�.
		if (j >= size)
		{
			return false;
		}

		//Je�li wierzcho�ek wyst�puje w �cie�ce dwa razy - zwr�� odpowied� negatywn�.
		if (indexes[j] == true)
		{
			return false;
		}
		else
		{
			indexes[j] = true;
		}
	}

	//Je�li jaki� wierzcho�ek nie zosta� odwiedzony - zwr�� odpowied� negatywn�.
	for (Index i = 0; i < size; i++)
	{
		if (indexes[i] == false)
		{
			return false;
		}
	}
	return true;
}

//Sprawdzanie poprawno�ci cyklu Hamiltona.
bool CompleteGraphHelper::IsValidCycleHamiltonian(const CompleteGraph & graph, const Path & path)
{
	return IsValidPathHamiltonian(graph, path, true);
}

//Tworzenie losowego grafu pe�nego.
//Jest on symetryczny i posiada zera na diagonali.
CompleteGraph CompleteGraphHelper::GenerateRandomGraph(const Index & size, const Value & min, const Value & max)
{
	Matrix matrix;

	for (Index i = 0; i < size; i++)
	{
		Vector vector;
		for (Index j = 0; j < size; j++)
		{
			if (i == j)
			{
				//Zera na diagonali.
				vector.push_back(0);
			}
			else
			{
				//Dzi�ki temu macierz b�dzie symetryczna.
				if (j > i)
				{
					vector.push_back(GetRandomValue(min, max));
				}
				else
				{
					vector.push_back(matrix[j][i]);
				}
			}
		}
		matrix.push_back(vector);
	}

	return CompleteGraph(matrix);
}

//Wczytywanie grafu ze strumienia wej�ciowego.
CompleteGraph CompleteGraphHelper::ReadGraph(std::istream & stream)
{
	Matrix matrix;

	if (stream)
	{
		std::string line;
		while (stream.good())
		{
			Vector vector;

			//Analiza linia po linii.
			if (!std::getline(stream, line)) continue;

			//Je�li linia pusta to przejd� do nast�pnej.
			if (line.empty()) continue;

			//Analiza warto�ci w konkretnej linii.
			std::stringstream stream_line(line);
			while (!stream_line.eof())
			{
				Value value;

				//Je�li nie powiod�a si� konwersja na Value - pomi� �mieci.
				if (!(stream_line >> value)) 
				{
					//Wyrzucenie �mieci.
					stream_line.clear();
					std::string trash;
					stream_line >> trash;
					continue;
				}
				vector.push_back(value);
			}
			matrix.push_back(vector);
		}
	}

	return CompleteGraph(matrix);
}

//Wczytywanie grafu z pliku.
CompleteGraph CompleteGraphHelper::ReadGraphFromFile(std::string & filename)
{
	std::fstream file;
	file.open(filename);
	if (file.is_open())
	{
		return ReadGraph(file);
	}
	else
	{
		return CompleteGraph();
	}
	file.close();
}

//Pobieranie wektora koszt�w dla danej �cie�ki.
//Metoda zwraca wektor z�o�ony z wag kraw�dzi, wi�c odleg�o�ci pomi�dzy wierzcho�kami.
Vector CompleteGraphHelper::GetPathCosts(const CompleteGraph & graph, const Path & path)
{
	Vector vector;

	Index size = graph.GetSize();

	Index prev = 0;
	bool valid_start = false;
	for (Index i = 0; i < path.size(); i++)
	{
		//Je�li wierzcho�ek znajduje si� w grafie.
		if (path[i] < size)
		{
			prev = i;
			valid_start = true;
			break;
		}
	}

	//Je�li znaleziono wierzcho�ek nale��cy do grafu.
	if (valid_start)
	{
		//Je�eli �cie�ka zawiera jeszcze jakie� wierzcho�ki znajduj�ce si� za tym znalezionym.
		if (prev < path.size() - 1)
		{
			for (Index i = prev + 1; i < path.size(); i++)
			{
				//Je�li wierzcho�ek znajduje si� w grafie.
				if (path[i] < size)
				{
					auto value = graph.GetValue(path[prev], path[i]);
					if (value != nullptr)
					{
						vector.push_back(*value);
						prev = i;
					}
				}
			}
		}
	}

	return vector;
}

//Sumowanie koszt�w �cie�ki na podstawie wektora wag.
Value CompleteGraphHelper::GetPathCostFromCostsVector(const CompleteGraph & graph, const Vector & costs)
{
	Value cost = 0;

	for (const Value & value : costs)
	{
		cost += value;
	}

	return cost;
}

//Sumowanie koszt�w �cie�ki na podstawie podanej �ci�ki.
Value CompleteGraphHelper::GetPathCostFromPath(const CompleteGraph & graph, const Path & path)
{
	return GetPathCostFromCostsVector(graph, GetPathCosts(graph, path));
}

Value CompleteGraphHelper::GetPathCost(const CompleteGraph & graph, const Path & path)
{
	return GetPathCostFromPath(graph, path);
}

//Wy�wietlanie �cie�ki.
//display_indexes odpowiada za wy�wietlanie pozycji.
//display_costs odpowiada za wy�wietlanie warto�ci (koszt�w).
//display_cost odpowiada za wy�wietlanie ca�o�ciowej warto�ci (kosztu).
void CompleteGraphHelper::DisplayPath(const CompleteGraph & graph, const Path & path, const bool & display_indexes, const bool & display_costs, const bool & display_cost, std::ostream & stream)
{
	if (display_indexes)
	{
		DisplayPath(path, stream);
	}

	if (display_costs || display_cost)
	{
		Vector vector = GetPathCosts(graph, path);

		if (display_costs)
		{
			DisplayVector(vector, stream);
		}

		if (display_cost)
		{
			Value cost = GetPathCostFromCostsVector(graph, vector);

			DisplayValue(cost, stream);
		}
	}
}

//Wy�wietlanie grafu na strumieniu wyj�ciowym.
void CompleteGraphHelper::DisplayGraph(const CompleteGraph & graph, std::ostream & stream)
{
	if (graph.IsValid())
	{
		const Matrix * matrix;
		matrix = graph.GetMatrix();
		if (matrix != nullptr)
		{
			if ((*matrix).size() > 0)
			{
				for (const auto & vector : *matrix)
				{
					DisplayVector(vector, stream);
				}
			}
		}
	}
}
