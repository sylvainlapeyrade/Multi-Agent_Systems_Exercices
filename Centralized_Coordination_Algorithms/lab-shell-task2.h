// ------------------------------------------------------------------------------
// Header for lab-shell-task2.cpp  -- you don't need to change this file.
//
// TDDE13 Multi Agent Systems (Linköping University).
// Last update: 15 October 2019.
// ------------------------------------------------------------------------------

#ifndef __LAB_TASK2
#define __LAB_TASK2

#include <bits/stdc++.h>
#include "lab-shell-utils.h"
using namespace std;

namespace scsga
{
	// Returns the value of a given ordered coalition structure.
	float evaluate_ordered_coalition_structure
	(
		const ordered_coalition_structure & S, 
		const vector<task> & T,
		const utility_function & v
	);
	

	// Random search implementation. Don't change this.
	ordered_coalition_structure random_search_SCSGA
	(
		const vector<agent> & N,
		const vector<task> & T,
		const utility_function & v,
		const int k /* number of solutions to generate and evaluate */
	);
	
	// Returns a greedily generated ordered coalition structure.
	coalition_structure greedy_SCSGA
	(
		const vector<agent> & N, 
		const vector<task> & T,
		const utility_function & v
	);
	
	// Evaluates a given coalition-task assignment using a utility function.
	float evaluate_coalition_assignment
	(
		const coalition & C, 
		const task & t,
		const utility_function & value_function
	);
}
#endif