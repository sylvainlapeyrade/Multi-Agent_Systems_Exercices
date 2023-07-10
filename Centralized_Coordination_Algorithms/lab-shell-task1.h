// ------------------------------------------------------------------------------
// Header for lab-shell-task1.cpp -- you don't need to change this file.
//
// TDDE13 Multi Agent Systems (Linköping University).
// Last update: 15 October 2019.
// ------------------------------------------------------------------------------

#ifndef __LAB_TASK1
#define __LAB_TASK1

#include <bits/stdc++.h>
#include "lab-shell-utils.h"
using namespace std;

namespace csg
{
	// Returns the value of a given coalition structure.
	float evaluate_coalition_structure
	(
		const coalition_structure & CS,
		const characteristic_function & v
	);

	// Returns a greedily generated coalition structure.
	coalition_structure greedy_CSG
	(
		const vector<agent> & N, 
		const characteristic_function & v
	);
	
	// Random search implementation. Don't change this.
	coalition_structure random_search_CSG
	(
		const vector<agent> & N,
		const characteristic_function & v,
		const int k /* number of solutions to generate and evaluate */
	);
	
	// Evaluates a given coalition using a characteristic function.
	float evaluate_coalition
	(
		const coalition & C, 
		const characteristic_function & value_function
	);
}
#endif