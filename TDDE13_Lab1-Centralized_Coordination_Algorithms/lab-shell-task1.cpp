// ------------------------------------------------------------------------------
// Task 1: Coalition structure generation.
//
// TDDE13 Multi Agent Systems (Linköping University).
// Last update: 15 October 2019.
// ------------------------------------------------------------------------------

#include <bits/stdc++.h>
#include "lab-shell-task1.h"
using namespace std;

// ------------------------------------------------------------------------------
// Task 1.1: Implement the function that evaluates a coalition structure.
// ------------------------------------------------------------------------------
float csg::evaluate_coalition_structure(
	const coalition_structure &CS,
	const characteristic_function &v)
{
	float s = 0;

	// Implementation here using evaluate_coalition ...
	for (auto const &coalition : CS)
	{
		s += evaluate_coalition(coalition, v);
	}

	return s;
}

// ------------------------------------------------------------------------------
// Task 1.2: Implement random search coalition structure generation.
// ------------------------------------------------------------------------------
coalition_structure csg::random_search_CSG(
	const vector<agent> &N,
	const characteristic_function &v,
	const int k /* number of solutions to generate and evaluate */
)
{
	// Initialize the best coalition structure to be the grand coalition.
	coalition_structure CS_best{N};

	// Implementation here using evaluate_coalition ...
	srand(time(NULL));

	for (int sample_nb = 1; sample_nb < k; sample_nb++)
	{
		coalition_structure CS;

		for (auto const &i : N)
		{
			int j = 0;
			if (CS.size() > 0)
			{
				j = rand() % CS.size();
			}

			if (j == 0)
			{
				CS.push_back(coalition{i});
			}
			else
			{
				CS[j - 1].push_back(i); //Append a player to a coalition
			}
		}
		if (evaluate_coalition_structure(CS, v) > evaluate_coalition_structure(CS_best, v))
		{
			CS_best = CS;
		}
	}
	return CS_best;
}

// ------------------------------------------------------------------------------
// Task 1.3: Implement the greedy coalition structure generation algorithm.
// ------------------------------------------------------------------------------
coalition_structure csg::greedy_CSG(
	const vector<agent> &N,
	const characteristic_function &v)
{
	// Initialize an empty coalition structure.
	coalition_structure CS{};

	// Initialize the best coalition structure to be the grand coalition.
	coalition_structure CS_best{};

	// Implement here ...
	for (const auto &i : N)
	{
		CS_best = CS;
		CS_best.push_back(coalition{i});

		if (CS.size() > 0)
		{
			coalition_structure CS2 = CS;
			for (auto &C : CS)
			{
				for (int it = 1; it < (int)CS2.size(); it++)
				{
					if (CS2[it] == C)
					{
						CS2[it].clear();
					}
				}
				C.push_back(i);
				CS2.push_back(C);
				if (evaluate_coalition_structure(CS2, v) > evaluate_coalition_structure(CS_best, v))
				{
					CS_best = CS2;
				}
			}
		}
		CS = CS_best;
	}

	return CS; // Will throw an error, since CS does not contain all agents.
}

// ------------------------------------------------------------------------------
// Evaluates a given coalition using a characteristic function.
// Don't change!
float csg::evaluate_coalition(
	const coalition &c,
	const characteristic_function &value_function)
{
	coalition cc = c;
	sort(cc.begin(), cc.end()); // Coalition needs to be sorted.
	const auto map_pointer = value_function.find(cc);
	if (map_pointer == value_function.end())
	{
		cerr << "Tried to evaluate an invalid coalition: {";
		for (auto i : cc)
			cout << i << ", ";
		cout << "}" << endl;
		cout << "Press any key to continue ... " << endl;
		exit(EXIT_FAILURE);
		return 0;
	}
	return map_pointer->second;
}
