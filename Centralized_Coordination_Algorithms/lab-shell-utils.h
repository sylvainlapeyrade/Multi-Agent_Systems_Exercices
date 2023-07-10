// ------------------------------------------------------------------------------
// Don't change these helper aliases -- use them!
//
// TDDE13 Multi Agent Systems (Linköping University).
// Last update: 15 October 2019.
// ------------------------------------------------------------------------------

#ifndef __LAB_UTILS
#define __LAB_UTILS

#include <bits/stdc++.h>
using namespace std;

// Each agent/player is represented by a unique integer identifier.
using agent = int; 

// A coalition is a set (represented by a vector) of agents.
using coalition = vector<agent>;

// A coalition structure is a set (represented by a vector) of coalitions.
using coalition_structure = vector<coalition>; 

// An ordered coalition structure is a vector of coalitions.
using ordered_coalition_structure = vector<coalition>; 

// Maps a value to every coalition.
using characteristic_function = map<coalition,float>;

// Each task/job is represented by a unique integer identifier.
using task = int;

// Maps a float value to every coalition-task assignment.
using utility_function = map<pair<coalition,task>,float>;
#endif