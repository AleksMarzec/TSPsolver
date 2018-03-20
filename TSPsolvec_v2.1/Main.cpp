#include "Config.h"
#include "CompleteGraph.h"
#include "CompleteGraphHelper.h"
#include "Parameter.h"
#include "ParameterHelper.h"
#include "TspAlgorithm.h"
#include "TspHelper.h"
#include "TspFactory.h"
#include "TspManager.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <iterator>
#include <string>
#include <boost/program_options.hpp>

//http://www.boost.org/doc/libs/1_55_0/libs/program_options/example/options_description.cpp
//A helper function to simplify the main part.
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
	return os;
}

//Wyœwietlanie informacji o wersji programu.
void About(std::ostream & stream = std::cout)
{
	stream << "Tsp" << std::endl;
	stream << PROGRAM_VERSION_MAJOR << "." << PROGRAM_VERSION_MINOR << std::endl;
}

//G³ówna metoda odpowiedzialna za wykonanie algorytmów na podanych danych i wyœwietlenie wyników.
void Process(const std::vector<std::string> & algorithms, const CompleteGraph & graph, const Index & start = 0, const ParametersAll & parameters = {}, const Index & verbose = 0, std::ostream & stream = std::cout, std::ostream & stream_errors = std::cerr)
{
	if (graph.IsValid() == true)
	{
		if (algorithms.size() > 0)
		{
			std::shared_ptr<const std::vector<std::string>> algorithms_ptr = std::make_shared<const std::vector<std::string>>(algorithms);
			std::shared_ptr<const CompleteGraph> graph_ptr = std::make_shared<const CompleteGraph>(graph);
			std::shared_ptr<const Index> start_ptr = std::make_shared<const Index>(start);
			std::shared_ptr<const ParametersAll> parameters_ptr = std::make_shared<const ParametersAll>(parameters);

			bool verbose_bool = false;
			if (verbose > 0)
			{
				verbose_bool = true;
			}

			//Praktycznie ca³oœci¹ zarz¹dza TspManager.
			TspManager * manager = new TspManager(algorithms_ptr, graph_ptr, start_ptr, parameters_ptr);
			manager->Info(stream, stream_errors);
			manager->Execute(verbose_bool, stream, stream_errors);
			delete manager;
		}
		else
		{
			if (verbose > 0)
			{
				stream_errors << "Error: Algorithm list is empty (will be omnited)" << std::endl;
				stream_errors << std::endl;
			}
		}
	}
	else
	{
		if (verbose > 0)
		{
			stream_errors << "Error: Invalid graph (will be omnited)" << std::endl;
			stream_errors << std::endl;
		}
	}
}

int main(int argc, char* argv[])
{
	Index verbose = 0;
	Index start = 0;

	std::vector<std::string> algorithms = {};
	ParametersAll parameters = {};
	std::vector<std::string> input_files = {};

	// http://www.boost.org/doc/libs/1_63_0/doc/html/program_options.html
	// http://www.boost.org/doc/libs/1_63_0/doc/html/program_options/tutorial.html
	// http://www.boost.org/doc/libs/1_55_0/libs/program_options/example/options_description.cpp
	boost::program_options::options_description options_visible("Options");
	// default_value vs implicit_value: http://stackoverflow.com/a/2830056

	options_visible.add_options()
		("help,h", "produce help message")
		("version,V", "show program version")
		// http://stackoverflow.com/a/17093580, http://stackoverflow.com/a/33172979
		("verbose,v", boost::program_options::value<Index>(&verbose)->implicit_value(1)->zero_tokens(), "enable verbosity") //bez mo¿liwoœci podania poziomu gadatliwoœci
		("list,l", "list available algorithms")
		("options,o", "list available parameters")
		("use-algorithm,a", boost::program_options::value< std::vector<std::string> >(), "use algorithm")
		("use-parameter,p", boost::program_options::value< std::vector<std::string> >(), "use parameter (format: \"algorithm:name:value\", e.g. \"TspAlgorithmRandom:iterations:100\")")
		("start,s", boost::program_options::value<Index>(&start)->default_value(0), "set start point");

	boost::program_options::options_description options_hidden("Hidden Options");;
	options_hidden.add_options()
		("input-file", boost::program_options::value< std::vector<std::string> >(), "input file");

	std::string usage_string = "Usage: " + std::string(argv[0]) + " [options] [FILES]";

	//Declare an options description instance which will include all the options.
	boost::program_options::options_description options_all("Options");
	options_all.add(options_visible).add(options_hidden);

	boost::program_options::positional_options_description p;
	p.add("input-file", -1);

	try 
	{
		boost::program_options::variables_map vm;
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(options_all).positional(p).run(), vm);
		boost::program_options::notify(vm);

		//Wyœwietlenie pomocy.
		if (vm.count("help"))
		{
			std::cout << usage_string << std::endl << std::endl << options_visible << std::endl;
			return EXIT_SUCCESS;
		}

		//Wyœwietlenie informacji o wersji programu.
		if (vm.count("version"))
		{
			About(std::cout);
			return EXIT_SUCCESS;
		}

		//Wylistowanie wszystkich dostêpnych algorytmów.
		if (vm.count("list"))
		{
			std::cout << "Algorithms list:" << std::endl;
			TspHelper::DisplayAlgorithmNames(std::cout);
			return EXIT_SUCCESS;
		}

		//Wylistowanie wszystkich dostêpnych parametrów do algorytmów.
		if (vm.count("options"))
		{
			std::cout << "Algorithms parameters:" << std::endl;
			TspHelper::DisplayAlgorithmParametersAll(true, std::cout);
			return EXIT_SUCCESS;
		}

		//Ustawienie gadatliwoœci.
		if (vm.count("verbose"))
		{
			verbose = 1;
		}

		//Wybór algorytmu/algorytmów.
		if (vm.count("use-algorithm"))
		{
			for (const std::string algorithm_name : vm["use-algorithm"].as<std::vector<std::string>>())
			{
				if (TspFactory::CheckAlgorithmName(algorithm_name) == true)
				{
					algorithms.push_back(algorithm_name);
				}
				else
				{
					if (verbose > 0)
					{
						std::cerr << "Error: Unknown algorithm (will be omnited): " << algorithm_name << std::endl;
					}
				}
			}
		}
		else //Jeœli nie wyszczególniono ¿adnego algorytmu - weŸ wszystkie mo¿liwe.
		{
			algorithms = TspFactory::GetAlgorithmNames();
		}

		//Wybór parametru/parametrów do algorytmów.
		if (vm.count("use-parameter"))
		{
			std::vector<Parameter> params = {};
			for (const std::string parameter_text : vm["use-parameter"].as<std::vector<std::string>>())
			{
				Parameter param = ParameterHelper::ParseParameter(parameter_text);

				if (param.IsValid() == true)
				{
					params.push_back(param);
				}
				else
				{
					if (verbose > 0)
					{
						std::cerr << "Error: Unable to parse parameter (will be omnited): " << parameter_text << std::endl;
					}
				}
			}
			parameters = ParameterHelper::ParseParameters(params);
		}

		//Lista nazw plików z grafami wejœciowymi.
		if (vm.count("input-file"))
		{
			for (const std::string input_file : vm["input-file"].as<std::vector<std::string>>())
			{
				input_files.push_back(input_file);
			}
		}
	}
	catch (std::exception & e)
	{
		std::cerr << "Error: " << e.what() << std::endl << std::endl;
		std::cerr << usage_string << std::endl << std::endl << options_visible << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "Unknown error!" << std::endl << std::endl;
		std::cerr << usage_string << std::endl << std::endl << options_visible << std::endl;
		return EXIT_FAILURE;
	}

	//Wyœwietlenie wybranych przez u¿ytkownika algorytmów i parametrów.
	if (verbose > 0)
	{
		if (algorithms.size() > 0)
		{
			std::cout << "Algorithms:" << std::endl;
			for (const std::string & algorithm : algorithms)
			{
				std::cout << algorithm << std::endl;
			}
			std::cout << std::endl;
		}

		if (parameters.size() > 0)
		{
			std::cout << "Parameters:" << std::endl;
			TspHelper::DisplayAlgorithmParametersAll(parameters);
			std::cout << std::endl;
		}
	}

	//Jeœli lista plików nie jest pusta - czytaj dane z plików.
	//W przeciwnym wypadku - ze standardowego wejœcia.
	if (input_files.size() > 0)
	{
		std::cout << input_files[0] << std::endl;
		for (const std::string & input_file : input_files)
		{
			std::fstream file;
			file.open(input_file);
			if (file.is_open())
			{
				CompleteGraph graph = CompleteGraphHelper::ReadGraph(file);
				Process(algorithms, graph, start, parameters, verbose, std::cout, std::cerr);
			}
			else
			{
				if (verbose > 0)
				{
					std::cerr << "Error: Unable to read graph from file (will be omnited): " << input_file << std::endl;
					std::cerr << std::endl;
				}
			}
		}
	}
	else //Jeœli lista argumentów jest pusta - czytaj dane ze standardowego wejœcia.
	{
		CompleteGraph graph = CompleteGraphHelper::ReadGraph(std::cin);
		Process(algorithms, graph, start, parameters, verbose, std::cout, std::cerr);
	}

	return EXIT_SUCCESS;
}

