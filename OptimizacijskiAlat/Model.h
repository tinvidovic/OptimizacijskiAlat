#include <string>
#include <cstring>
#include <vector>
#include "Task.h"
#include "TaskInstance.h"
#include "TaskSet.h"
#include "Helper.h"
#include "TaskChain.h"
#include <chrono>
#include <sstream>
#include <fstream>
#include <string>
#include "ortools/sat/cp_model.h"
#include "ortools/sat/model.h"
#include "ortools/sat/sat_parameters.pb.h"
#include "ortools/constraint_solver/constraint_solver.h"




#pragma once

using namespace operations_research;


// The function that creates the name of interval variable
string createIntervalVariableName(string instanceName, string phase);

// The function that creates CPLEX model based on task sets
double createAndSolveModel(std::vector<TaskSet>& taskSets, std::vector<TaskChain>& taskChains, int numberOfSolutions, int& status, int& numberOfConstraints, int timeLimit = 60, int maximumInterCoreDelay = -1, bool minimizeResponseTimes = false);






