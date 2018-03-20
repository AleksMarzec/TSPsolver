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

//Zwracanie losowej wartoœci typu Value z zakresu od min do max.
Value CompleteGraphHelper::GetRandomValue(const Value & min, const Value & max)
{
	static std::random_device r;
	static std::default_random_engine e(r());
	uniform_distribution d(min, max);
	return d(e);
}

//Zwracanie losowej wartoœci typu Index z zakresu od min do max.
Index CompleteGraphHelper::GetRandomIndex(const Index & min, const Index & max)
{
	static std::random_device r;
	static std::default_random_engine e(r());
	std::uniform_int_distribution<Index> d(min, max);
	return d(e);
}

//Zwracanie losowej wartoœci typu Real z zakresu od min do max.
Real CompleteGraphHelper::GetRandomReal(const Real & min, const Real & max)
{
	static std::random_device r;
	static std::default_random_engine e(r());
	std::uniform_real_distribution<Real> d(min, max);
	return d(e);
}

//Wyœwietlanie pojedynczego indeksu.
void CompleteGraphHelper::DisplayIndex(const Index & index, std::ostream & stream, bool newline)
{
	DisplayHelper<Index>::DisplayVar(index, stream, newline);
}

//Wyœwietlanie pojedynczej wartoœci.
void CompleteGraphHelper::DisplayValue(const Value & value, std::ostream & stream, bool newline)
{
	DisplayHelper<Value>::DisplayVar(value, stream, newline);
}

//Wyœwietlanie wektora indeksów.
void CompleteGraphHelper::DisplayPath(const Path & path, std::ostream & stream)
{
	DisplayHelper<Index>::DisplayList(path, stream);
}

//Wyœwietlanie wektora wartoœci.
void CompleteGraphHelper::DisplayVector(const Vector & vector, std::ostream & stream)
{
	DisplayHelper<Value>::DisplayList(vector, stream);
}

//Tworzenie scie¿ki.
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

//Tworzenie scie¿ki losowej.
Path CompleteGraphHelper::GetPathRandom(const CompleteGraph & graph, const Index & start)
{
	Path path;

	Index size = graph.GetSize();

	if (size > 0)
	{
		Path vertices = GetPath(graph);

		if (start < size)
		{
			//Upewniamy siê, ¿e na pocz¹tku zawsze bêdzie wierzcho³ek wskazany przez start.
			path.push_back(start);
			vertices[start] = std::move(vertices.back());
			vertices.pop_back();
		}

		while (vertices.size() > 0)
		{
			// Losujemy pozycjê z dostêpnej puli.
			Index index_random = GetRandomIndex(0, vertices.size() - 1);

			// Dodajemy wartoœæ do œcie¿ki wynikowej.
			path.push_back(vertices[index_random]);

			// Jeœli wylosowany indeks nie jest ostatni¹ pozycj¹ to zamieñ go z ostatnim.	
			if (index_random < vertices.size() - 1)
			{
				//Takim spodobem algorytm dzia³a szybciej, bo nie usuwamy elementu ze œroda.
				vertices[index_random] = std::move(vertices.back());
			}
			// Usuwamy wylosowan¹ pozycjê.
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

//Pobieranie w³aœciwej œcie¿ki.
//Zwraca now¹ œcie¿kê sk³adaj¹c¹ siê tylko z punktów które nale¿¹ do grafu.
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

//Sprawdzanie poprawnoœci œcie¿ki.
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

//Sprawdzanie poprawnoœci cyklu.
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

//Sprawdzanie poprawnoœci œcie¿ki Hamiltona.
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

	//Jeœli mamy do czynienia z cyklem to wierzcho³ek pocz¹tkowy i koñcowy musi byæ identyczny.
	if (is_cycle == true)
	{
		if (path.front() != path.back())
		{
			return false;
		}
	}

	//Nale¿y sprawdziæ, czy œcie¿ka/cykl zawiera wszystkie wierzcho³ki grafu.
	std::vector<bool> indexes(size, false);

	for (Index i = 0; i < size; i++)
	{
		Index j = path[i];

		//Jeœli wierzcho³ek nie nale¿y do grafu - zwróæ odpowiedŸ negatywn¹.
		if (j >= size)
		{
			return false;
		}

		//Jeœli wierzcho³ek wystêpuje w œcie¿ce dwa razy - zwróæ odpowiedŸ negatywn¹.
		if (indexes[j] == true)
		{
			return false;
		}
		else
		{
			indexes[j] = true;
		}
	}

	//Jeœli jakiœ wierzcho³ek nie zosta³ odwiedzony - zwróæ odpowiedŸ negatywn¹.
	for (Index i = 0; i < size; i++)
	{
		if (indexes[i] == false)
		{
			return false;
		}
	}
	return true;
}

//Sprawdzanie poprawnoœci cyklu Hamiltona.
bool CompleteGraphHelper::IsValidCycleHamiltonian(const CompleteGraph & graph, const Path & path)
{
	return IsValidPathHamiltonian(graph, path, true);
}

//Tworzenie losowego grafu pe³nego.
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
				//Dziêki temu macierz bêdzie symetryczna.
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

//Wczytywanie grafu ze strumienia wejœciowego.
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

			//Jeœli linia pusta to przejdŸ do nastêpnej.
			if (line.empty()) continue;

			//Analiza wartoœci w konkretnej linii.
			std::stringstream stream_line(line);
			while (!stream_line.eof())
			{
				Value value;

				//Jeœli nie powiod³a siê konwersja na Value - pomiñ œmieci.
				if (!(stream_line >> value)) 
				{
					//Wyrzucenie œmieci.
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

//Pobieranie wektora kosztów dla danej œcie¿ki.
//Metoda zwraca wektor z³o¿ony z wag krawêdzi, wiêc odleg³oœci pomiêdzy wierzcho³kami.
Vector CompleteGraphHelper::GetPathCosts(const CompleteGraph & graph, const Path & path)
{
	Vector vector;

	Index size = graph.GetSize();

	Index prev = 0;
	bool valid_start = false;
	for (Index i = 0; i < path.size(); i++)
	{
		//Jeœli wierzcho³ek znajduje siê w grafie.
		if (path[i] < size)
		{
			prev = i;
			valid_start = true;
			break;
		}
	}

	//Jeœli znaleziono wierzcho³ek nale¿¹cy do grafu.
	if (valid_start)
	{
		//Je¿eli œcie¿ka zawiera jeszcze jakieœ wierzcho³ki znajduj¹ce siê za tym znalezionym.
		if (prev < path.size() - 1)
		{
			for (Index i = prev + 1; i < path.size(); i++)
			{
				//Jeœli wierzcho³ek znajduje siê w grafie.
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

//Sumowanie kosztów œcie¿ki na podstawie wektora wag.
Value CompleteGraphHelper::GetPathCostFromCostsVector(const CompleteGraph & graph, const Vector & costs)
{
	Value cost = 0;

	for (const Value & value : costs)
	{
		cost += value;
	}

	return cost;
}

//Sumowanie kosztów œcie¿ki na podstawie podanej œciê¿ki.
Value CompleteGraphHelper::GetPathCostFromPath(const CompleteGraph & graph, const Path & path)
{
	return GetPathCostFromCostsVector(graph, GetPathCosts(graph, path));
}

Value CompleteGraphHelper::GetPathCost(const CompleteGraph & graph, const Path & path)
{
	return GetPathCostFromPath(graph, path);
}

//Wyœwietlanie œcie¿ki.
//display_indexes odpowiada za wyœwietlanie pozycji.
//display_costs odpowiada za wyœwietlanie wartoœci (kosztów).
//display_cost odpowiada za wyœwietlanie ca³oœciowej wartoœci (kosztu).
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

//Wyœwietlanie grafu na strumieniu wyjœciowym.
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
