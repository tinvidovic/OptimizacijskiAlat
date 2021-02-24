// OptimizacijskiAlat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Task.h"
#include "TaskInstance.h"
#include "TaskChain.h"
#include "TaskSet.h"
#include "TestGenerator.h"
#include "Model.h"
#include "Data.h"

int main(int, const char* []) {

    try
    {

        std::vector<TaskSet> taskSets;
        std::vector<TaskChain> taskChains;

        int numberOfTasks = 4;
        int numberOfChains = 1;

        std::vector<double> coreUtilizations = { 0.5, 0.5};


        taskSets = TestCaseIndustrial(taskChains);

        int status;
        int constraints;
        createAndSolveModel(taskSets, taskChains, 1, status, constraints, 600);

        generateTestCase(taskSets, taskChains, 4, 1, coreUtilizations);
        createAndSolveModel(taskSets, taskChains, 1, status, constraints, 600);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();

    }

    return 0;
}

