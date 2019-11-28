// ---------------------------------------------------------------------------------
// Task 2: Simultaneous coalition structure generation and assignment.
//
// TDDE13 Multi Agent Systems (Linköping University).
// Last update: 15 October 2019.
// ---------------------------------------------------------------------------------

#include <bits/stdc++.h>
#include "lab-shell-task2.h"
using namespace std;

// ---------------------------------------------------------------------------------
// Task 2.1: Implement evaluation of ordered coalition structures.
// ---------------------------------------------------------------------------------
float scsga::evaluate_ordered_coalition_structure(
	const ordered_coalition_structure &S,
	const vector<task> &T,
	const utility_function &v)
{
	float s = 0;

	// Implement here by using evaluate_coalition_assignment ...

	return s;
}

// ---------------------------------------------------------------------------------
// Task 2.2: Implement the random search simultaneous coalition structure
// generation and assignment algorithm.
// ---------------------------------------------------------------------------------
ordered_coalition_structure scsga::random_search_SCSGA(
	const vector<agent> &N,
	const vector<task> &T,
	const utility_function &v,
	const int k /* number of solutions to generate and evaluate */
)
{
	// Initialize the best coalition structure to be the solution with
	// the grand coalition assigned to the "first" task.
	ordered_coalition_structure CS_best(T.size(), coalition());

	// Implement here ...
	srand(time(NULL));

	for (int i = 1; i < k; i++)
	{
		ordered_coalition_structure CS = CS_best;
		for (auto const &i : N)
		{
			coalition C = rand() % CS.size();
			C.pushback(i);
		}
	}

	return CS_best;
}

// ---------------------------------------------------------------------------------
// Task 2.3: Implement the greedy simultaneous coalition structure generation and
// assignment algorithm.
// ---------------------------------------------------------------------------------
coalition_structure scsga::greedy_SCSGA(
	const vector<agent> &N,
	const vector<task> &T,
	const utility_function &v)
{
	// Initialize a size-|T| ordered coalition structure of empty coalitions.
	ordered_coalition_structure CS(T.size(), coalition{});

	// Implement here ...

	return CS;
}

// ------------------------------------------------------------------------------
// Evaluates a given coalition-task assignment using a utility function.
// Don't change!
float scsga::evaluate_coalition_assignment(
	const coalition &c,
	const task &t,
	const utility_function &value_function)
{
	coalition cc = c;
	sort(cc.begin(), cc.end()); // Coalition needs to be sorted.
	const auto assignment_pair = make_pair(cc, t);
	const auto map_pointer = value_function.find(assignment_pair);
	if (map_pointer == value_function.end())
	{
		cerr << "Tried to evaluate a coalition-task assignment for task " << t << " that is not valid: {";
		for (auto i : cc)
			cout << i << ", ";
		cout << "}" << endl;
		exit(EXIT_FAILURE);
		return 0;
	}
	return map_pointer->second;
}