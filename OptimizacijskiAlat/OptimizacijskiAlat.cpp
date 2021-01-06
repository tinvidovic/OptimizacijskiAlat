#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "Task.h"
#include "TaskInstance.h"
#include "TaskChain.h"



int main(int, const char* []) {

    try
    {

        Task task1(0, 0, 2, 6);
        
        TaskInstance ti1(&task1, 0);
        TaskInstance ti2(&task1, 1);

        Task task2(1, 2, 3, 6);

        TaskInstance ti3(&task2, 0);

        Task task3(1, 2, 3, 24);

        TaskChain taskChain1;
        taskChain1.addTask(&task1);
        taskChain1.addTasks({ &task2, &task3 });

        std::cout << taskChain1 << std::endl;

    }
    catch (const std::exception& e)
    {
        std::cout << e.what();

    }

    return 0;
}