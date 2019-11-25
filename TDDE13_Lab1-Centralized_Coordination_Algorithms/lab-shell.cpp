// ------------------------------------------------------------------------------
// Don't change this!!
//
// TDDE13 Multi Agent Systems (Linköping University).
// Last update: 15 October 2019.
// ------------------------------------------------------------------------------

#include <bits/stdc++.h>
#include "lab-shell-task1.h"
#include "lab-shell-task2.h"
#include "lab-shell-utils.h"
using namespace std;

// ------------------------------------------------------------------------------
namespace benchmark
{
	// Returns true if the coalition structure contains no empty coalitions.
	bool sanity_check_empty(const vector<coalition> & CS)
	{
		for(const auto & C : CS)
		{
			if(C.size() <= 0)
			{
				return false;
			}
		}
		return true;
	}

	// Returns true if the coalition structure contains only disjoint coalitions.
	bool sanity_check_disjoint
	(
		const vector<coalition> & CS, 
		const vector<agent> & N
	)
	{
		std::unordered_set<agent> found_agents;
		for(const coalition &  C : CS)
		{
			for(const agent i : C)
			{
				if(found_agents.find(i) == found_agents.end())
				{
					found_agents.insert(i);
				}
				else 
				{
					return false;
				}
			}
		}
		return true;
	}
	
	// Returns true if the coalition structure contains only exhaustive coalitions.
	bool sanity_check_exhaustive
	(
		const vector<coalition> & CS, 
		const vector<agent> & N
	)
	{
		std::unordered_set<agent> found_agents;
		for(const coalition &  C : CS)
		{
			for(const agent i : C)
			{
				found_agents.insert(i);
			}
		}
		for(const agent i : N)
		{
			if(found_agents.find(i) == found_agents.end())
			{
				return false;
			}
		}
		return true; 
	}
	
	// Returns true if only valid agents are in the coalition structure.
	bool sanity_check_no_spies
	(
		const vector<coalition> & CS, 
		const vector<agent> & N
	)
	{
		std::unordered_set<agent> valid_agents;
		for(const agent i : N)
		{
			valid_agents.insert(i);
		}
		std::vector<agent> potential_spies;
		for(const coalition & C : CS)
		{
			for(const agent i : C)
			{
				potential_spies.push_back(i);
			}
		}
		for(const agent i : potential_spies)
		{
			if(valid_agents.find(i) == valid_agents.end())
			{
				return false;
			}
		}
		return true; 
	}
	
	// Checks if a coalition structure is valid. Returns a vector with all errors.
	vector<string> sanity_check_valid_solution
	(
		const vector<coalition> & CS, 
		const vector<agent> & N, 
		const int expected_size = -1
	)
	{
		string error_string = "";
		vector<string> errors;
		
		// Check size.
		if(expected_size >= 0)
		{
			if(CS.size() != (uint32_t)expected_size)
			{
				error_string = 
					"The coalition structure's size is invalid (expected " +
					to_string(expected_size) + " but got " + to_string(CS.size()) + ")";
				
				errors.push_back(error_string);
			}
		}
		
		if(expected_size == -1 && !sanity_check_empty(CS)) // SCSGA can have empty coalitions.
		{
			error_string = 
				"The coalition structure contains empty coalitions";
				
			errors.push_back(error_string);
		}
		
		if(!sanity_check_disjoint(CS, N))
		{
			error_string = 
				"The coalition structure is not disjoint";
				
			errors.push_back(error_string);
		}
		
		if(!sanity_check_exhaustive(CS, N))
		{
			error_string = 
				"The coalition structure is not exhaustive";
				
			errors.push_back(error_string);
		}
		
		if(!sanity_check_no_spies(CS, N))
		{
			error_string = 
				string("The coalition structure contains invalid agents ") +
				"(i.e., agents that are not part of the agent set)";
				
			errors.push_back(error_string);
		}
		
		return errors;
	}
	
	characteristic_function load_characteristic_function_from_file(const string & filepath, int & n)
	{	
		characteristic_function v;
		ifstream input_file(filepath); 
		if(!input_file.is_open())
		{
			return v;
		}
		
		int m,d;
		input_file >> n >> m >> d;
		if(m != -1 || n <= 0 || n > 20)
		{
			return v;
		}
		
		coalition c;
		for(uint32_t mask = 1ULL; mask < (1ULL << (uint32_t)n); ++mask)
		{
			float value;
			input_file >> value;
			c.clear();
			for(uint32_t i = 0ULL; i < (uint32_t)n; ++i)
			{
				if(((1ULL << i) & mask) != 0ULL)
				{
					c.push_back(i);
				}
			}
			v[c] = value;
		}
		return v;
	}
	
	utility_function load_utility_function_from_file(const string & filepath, int & n, int & m)
	{
		utility_function v;
		ifstream input_file(filepath); 
		
		if(!input_file.is_open())
		{
			return v;
		}
		
		int d;
		input_file >> n >> m >> d;
		if(m <= 0 || m > 2000 || n <= 0 || n > 20)
		{
			return v;
		}
		
		coalition c;
		for(uint32_t mask = 0ULL; mask < (1ULL << n); ++mask)
		{
			c.clear();
			for(uint32_t i = 0ULL; i < (uint32_t)n; ++i)
			{
				if(((1ULL << i) & mask) != 0ULL)
				{
					c.push_back(i);
				}
			}
			
			for(uint32_t t = 0; t < (uint32_t)m; ++t)
			{
				float value;
				input_file >> value;
				v[make_pair(c,t)] = value;
			}
		}
		return v;
	}
}

// Don't change main.
int main(int argc, char** argv)
{
	cout << endl << "--------------------------------------------------------------------------" << endl;
	if(argc != 2)
	{
		cerr << "Invalid number of arguments and missing filepath." << endl;
		return -1;
	}
	
	cout << "Loading and parsing problem file ... " << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	string filepath = string(argv[1]);
	
	int n, m;
	characteristic_function cf = benchmark::load_characteristic_function_from_file(filepath, n);
	utility_function uf = benchmark::load_utility_function_from_file(filepath, n, m);
	int correct_functions = (cf.size() != 0) + (uf.size() != 0);
	if(correct_functions != 1)
	{
		cerr << "Could not load and generate a correct value function (error code: " << correct_functions << ")." << endl;
		return -1;
	}
	vector<agent> N;
	for(int i = 0; i < n; ++i)
		N.push_back(i);	
	vector<task> T;
	for(int i = 0; i < m; ++i)
		T.push_back(i);
	
	const vector<int> RANDOM_SEARCH_ITERATIONS_TO_RUN = {100, 1000, 10000, 100000};
	cout << endl;
	
	// Run CSG.
	if(cf.size() != 0)
	{
		cout << "Correctly loaded a coalition structure generation problem with " << n 
			<< " agents and " << cf.size() << " coalitional values. " << endl;
		
		// ------------------------------------------------------------------------------
		// Student's random search.
		// ------------------------------------------------------------------------------
		{
			cout << endl << "--------------------------------------------------------------------------" << endl;
			cout << "Random search results: " << endl;
			cout << "--------------------------------------------------------------------------" << endl;
			for(const int iters : RANDOM_SEARCH_ITERATIONS_TO_RUN)
			{
				const auto solution = csg::random_search_CSG(N, cf, iters);
				const auto errors = benchmark::sanity_check_valid_solution(solution, N);
				if(errors.size() > 0)
				{
					cout << "- with errors: " << endl;
					for(const auto & e : errors)
					{
						cout << "--- " << e << ". " << endl;
					}
					cout << endl;
				}
				else 
				{
					cout << "- coalition structure's value after " << iters << " evaluations: " << 
						csg::evaluate_coalition_structure(solution, cf) << endl;
				}
			}
		}
		
		// ------------------------------------------------------------------------------
		// Student's greedy algorithm.
		// ------------------------------------------------------------------------------
		{
			cout << endl << "--------------------------------------------------------------------------" << endl;
			cout << "Your algorithm's result: " << endl;
			cout << "--------------------------------------------------------------------------" << endl;
			const auto solution = csg::greedy_CSG(N, cf);
			const auto errors = benchmark::sanity_check_valid_solution(solution, N);
			if(errors.size() > 0)
			{
				cout << "- with errors: " << endl;
				for(const auto & e : errors)
				{
					cout << "--- " << e << ". " << endl;
				}
				cout << endl;
			}
			else 
			{
				cout << "- with coalition structure's value: " <<
					csg::evaluate_coalition_structure(solution, cf) << endl;
			}
		}
		// ------------------------------------------------------------------------------
	}
	
	// Run SCSGA.
	else if(uf.size() != 0)
	{
		cout << "Correctly loaded a simultaneous coalition structure generation and\nassignment problem with " << n 
			<< " agents, " << m << " tasks, and " << uf.size() << " coalitional values." << endl;
		
		// ------------------------------------------------------------------------------
		// Student's random search.
		// ------------------------------------------------------------------------------
		{
			cout << endl << "--------------------------------------------------------------------------" << endl;
			cout << "Random search results: " << endl;
			cout << "--------------------------------------------------------------------------" << endl;
			for(const int iters : RANDOM_SEARCH_ITERATIONS_TO_RUN)
			{
				const auto solution = scsga::random_search_SCSGA(N, T, uf, iters);
				const auto errors = benchmark::sanity_check_valid_solution(solution, N, m);
				if(errors.size() > 0)
				{
					cout << "- with errors: " << endl;
					for(const auto & e : errors)
					{
						cout << "--- " << e << ". " << endl;
					}
					cout << endl;
				}
				else 
				{
					cout << "- ordered coalition structure's value after " << iters << " evaluations: " << 
						scsga::evaluate_ordered_coalition_structure(solution, T, uf) << endl;
				}
			}
		}
		
		// ------------------------------------------------------------------------------
		// Student's greedy algorithm.
		// ------------------------------------------------------------------------------
		{
			cout << endl << "--------------------------------------------------------------------------" << endl;
			cout << "Your algorithm's result: " << endl;
			cout << "--------------------------------------------------------------------------" << endl;
			const auto solution = scsga::greedy_SCSGA(N, T, uf);
			const auto errors = benchmark::sanity_check_valid_solution(solution, N, m);
			if(errors.size() > 0)
			{
				cout << "- with errors: " << endl;
				for(const auto & e : errors)
				{
					cout << "--- " << e << ". " << endl;
				}
				cout << endl;
			}
			else 
			{
				cout << "- with ordered coalition structure's value: " <<
					scsga::evaluate_ordered_coalition_structure(solution, T, uf) << endl;
			}
		}
		// ------------------------------------------------------------------------------
	}
}