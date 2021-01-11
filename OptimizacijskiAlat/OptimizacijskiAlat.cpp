#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "Task.h"
#include "TaskInstance.h"
#include "TaskChain.h"
#include "TaskSet.h"



int main(int, const char* []) {

    try
    {

        Task task1(0, 0, 2, 6);
        Task task2(1, 2, 3, 6);


        Task task3(1, 2, 3, 24);

        TaskChain taskChain1;
        taskChain1.addTask(&task1);
        taskChain1.addTasks({ &task2, &task3 });

        TaskSet taskSet1(0);
        taskSet1.addTasks({ &task1});
        
        TaskSet taskSet2(1);
        taskSet2.addTasks({ &task2 , &task3 });

        std::cout << taskSet1 << std::endl << taskSet2;

    }
    catch (const std::exception& e)
    {
        std::cout << e.what();

    }

    return 0;
}