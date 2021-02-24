#include "Data.h"
#include <iostream>

std::vector<TaskSet>  TestCase1(std::vector<TaskChain>& chains)
{
    Task task1(1, 1, 1, 12);
    Task task2(1, 1, 1, 6);
    Task task3(1, 1, 1, 12);


    TaskSet taskSet0(0);

    TaskSet taskSet1(1);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);


    return taskSets;
}

std::vector<TaskSet>  TestCase2(std::vector<TaskChain>& chains)
{

    Task task1(1, 1, 1, 12);
    Task task2(1, 1, 1, 12);
    Task task3(1, 1, 1, 12);
    




    TaskSet taskSet0(0);

    TaskSet taskSet1(1);

    taskSet0.addTask(&task1);
    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);
    //taskSet0.addTask(&task4);


    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);

    return taskSets;

}

std::vector<TaskSet>  TestCase3(std::vector<TaskChain>& chains)
{

    Task task1(2, 2, 2, 42);
    Task task2(2, 2, 2, 42);
    Task task3(2, 2, 2, 42);

    Task task4(2, 2, 2, 42);
    Task task5(4, 6, 4, 42);
    Task task6(2, 2, 2, 42);

    TaskSet taskSet0(0);

    TaskSet taskSet1(1);

    taskSet0.addTask(&task1);
    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);

    taskSet1.addTask(&task4);
    taskSet1.addTask(&task5);
    taskSet1.addTask(&task6);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task5);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);

    return taskSets;

}

std::vector<TaskSet>  TestCase4(std::vector<TaskChain>& chains)
{
    Task task1(1, 1, 1, 6);
    Task task2(1, 1, 1, 12);
    Task task3(1, 1, 1, 24);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);

    chains.push_back(taskChain1);

    TaskSet taskSet0(0);

    TaskSet taskSet1(1);


    taskSet0.addTask(&task1);
    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);


    return taskSets;
}

std::vector<TaskSet>  TestCase5(std::vector<TaskChain>& chains)
{
    Task task1(1, 1, 1, 12);
    Task task2(1, 1, 1, 12);
    Task task3(1, 1, 1, 12);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);

    TaskSet taskSet0(0);

    TaskSet taskSet1(1);


    taskSet0.addTask(&task1);
    taskSet1.addTask(&task2);
    taskSet1.addTask(&task3);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);


    return taskSets;
}

std::vector<TaskSet>  TestCase6_1(std::vector<TaskChain>& chains)
{

    Task task1(1, 2, 1, 10);
    Task task2(2, 6, 2, 40);
    Task task3(1, 3, 1, 20);

    Task task4(2, 3, 1, 20);
    Task task5(2, 8, 2, 40);


    TaskSet taskSet0(0);

    TaskSet taskSet1(1);

    taskSet0.addTask(&task1);
    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);

    taskSet1.addTask(&task4);
    taskSet1.addTask(&task5);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;

}

std::vector<TaskSet>  TestCase6_2(std::vector<TaskChain>& chains)
{

    Task task1(2, 3, 1, 12);
    Task task2(1, 4, 1, 36);
    Task task3(2, 2, 2, 24);

    Task task4(1, 1, 1, 12);
    Task task5(1, 3, 1, 24);
    Task task6(1, 2, 1, 24);

    TaskSet taskSet0(0);

    TaskSet taskSet1(1);

    taskSet0.addTask(&task1);
    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);

    taskSet1.addTask(&task4);
    taskSet1.addTask(&task5);
    taskSet1.addTask(&task6);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;

}

std::vector<TaskSet>  TestCase6_3(std::vector<TaskChain>& chains)
{


    Task task1(2, 12, 2, 48);
    Task task2(1, 2, 1, 48);
    Task task3(1, 1, 1, 12);

    Task task4(3, 20, 2, 96);
    Task task5(1, 1, 1, 24);
    Task task6(2, 4, 2, 48);
    Task task7(2, 2, 2, 48);

    TaskSet taskSet0(0);

    TaskSet taskSet1(1);

    taskSet0.addTask(&task1);
    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);

    taskSet1.addTask(&task4);
    taskSet1.addTask(&task5);
    taskSet1.addTask(&task6);
    taskSet1.addTask(&task7);


    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;

}

std::vector<TaskSet>  TestCase7(std::vector<TaskChain>& chains)
{
    Task task1(1, 0, 1, 6);
    Task task2(1, 0, 1, 12);
    Task task3(1, 0, 1, 6);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    chains.push_back(taskChain1);

    TaskSet taskSet0(0);

    TaskSet taskSet1(1);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;
}

std::vector<TaskSet>  TestCase8(std::vector<TaskChain>& chains)
{
    Task task1(1, 0, 1, 5);
    Task task2(1, 1, 1, 8);

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);

    chains.push_back(taskChain1);

    TaskSet taskSet0(0);

    TaskSet taskSet1(1);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    return taskSets;
}

std::vector<TaskSet>  TestCase10_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 1, 12);
    Task task2(1, 2, 1, 12);
    Task task3(1, 1, 1, 12);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task3);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase10_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 16);
    Task task2(1, 1, 1, 16);
    Task task3(1, 2, 1, 16);
    Task task4(1, 1, 1, 16);
    Task task5(1, 1, 1, 16);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task5);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase10_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 16);
    Task task2(1, 1, 1, 16);
    Task task3(1, 1, 1, 16);
    Task task4(1, 1, 1, 16);
    Task task5(1, 1, 1, 16);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task3);

    taskSet0.addTask(&task5);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);

    taskSet1.addTask(&task4);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase10_4(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 2, 20);
    Task task2(2, 1, 2, 20);
    Task task3(1, 5, 1, 20);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task2);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task1);

    taskSet1.addTask(&task3);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase10_5(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 1, 100);
    Task task2(2, 2, 1, 100);
    Task task3(1, 2, 1, 100);
    Task task4(1, 1, 1, 100);
    Task task5(1, 5, 2, 100);
    Task task6(1, 2, 1, 100);
    Task task7(1, 2, 2, 100);
    Task task8(1, 1, 1, 100);
    Task task9(1, 2, 1, 100);
    Task task10(1, 2, 1, 100);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);
    taskChain1.addTask(task6);
    taskChain1.addTask(task7);
    taskChain1.addTask(task8);
    taskChain1.addTask(task9);
    taskChain1.addTask(task10);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);
    taskSet0.addTask(&task2);
    taskSet0.addTask(&task4);
    taskSet0.addTask(&task8);
    taskSet0.addTask(&task10);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task6);

    taskSet1.addTask(&task7);

    taskSet1.addTask(&task9);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase11_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 24);
    Task task2(1, 1, 1, 12);
    Task task3(1, 1, 1, 6);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase11_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 100);
    Task task2(1, 1, 1, 50);
    Task task3(1, 1, 1, 20);
    Task task4(1, 0, 1, 10);
    Task task5(1, 0, 1, 5);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase11_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 6);
    Task task2(1, 0, 1, 9);
    Task task3(1, 2, 1, 36);
    Task task4(1, 1, 1, 18);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);



    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase12_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 8);
    Task task2(1, 0, 1, 7);
    Task task3(1, 0, 1, 6);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase12_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 2, 13);
    Task task2(1, 2, 1, 15);
    Task task3(1, 3, 1, 17);
    Task task4(1, 2, 1, 19);
    Task task5(1, 1, 1, 21);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task5);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase12_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 11);
    Task task2(1, 2, 1, 13);
    Task task3(1, 1, 2, 17);
    Task task4(1, 0, 1, 19);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task4);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}



std::vector<TaskSet>  TestCase13_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 3);
    Task task2(1, 0, 1, 24);
    Task task3(1, 0, 1, 12);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase13_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 3);
    Task task2(1, 0, 1, 24);
    Task task3(1, 0, 1, 12);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase13_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 5);
    Task task2(1, 0, 1, 10);
    Task task3(1, 1, 1, 20);
    Task task4(1, 1, 1, 50);
    Task task5(1, 1, 1, 100);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);
    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);
    taskSet1.addTask(&task4);
    taskSet1.addTask(&task5);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase13_4(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 2, 1, 36);
    Task task2(1, 1, 1, 18);
    Task task3(1, 0, 1, 6);
    Task task4(1, 0, 1, 9);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task1);
    taskSet1.addTask(&task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase13_5(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 7);
    Task task2(1, 0, 1, 14);
    Task task3(1, 0, 1, 28);
    Task task4(1, 0, 1, 28);
    Task task5(1, 1, 1, 56);
    Task task6(1, 1, 1, 14);


    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);
    taskSet0.addTask(&task2);
    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);
    taskSet1.addTask(&task5);
    taskSet1.addTask(&task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task4);
    taskChain1.addTask(task6);


    // Add Chains

    chains.push_back(taskChain1);

    // Return Task Sets

    return taskSets;


}



std::vector<TaskSet>  TestCase14_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(3, 5, 2, 21);
    Task task2(2, 6, 1, 23);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase14_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(3, 2, 1, 19);
    Task task2(2, 3, 1, 21);
    Task task3(2, 3, 2, 23);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase14_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 7);
    Task task2(1, 0, 1, 9);
    Task task3(1, 0, 1, 11);
    Task task4(1, 0, 1, 13);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);

    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase15_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 6);
    Task task2(1, 0, 1, 7);
    Task task3(1, 0, 1, 8);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase15_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 3, 2, 21);
    Task task2(1, 2, 1, 19);
    Task task3(1, 3, 1, 17);
    Task task4(1, 2, 1, 15);
    Task task5(1, 1, 1, 13);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);
    taskChain1.addTask(task5);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task5);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase15_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 19);
    Task task2(1, 2, 1, 17);
    Task task3(1, 1, 2, 13);
    Task task4(1, 0, 1, 11);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task4);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase16_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 7);
    Task task2(1, 0, 1, 6);
    Task task3(1, 0, 1, 8);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase16_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 19);
    Task task2(1, 2, 1, 17);
    Task task3(1, 1, 1, 19);
    Task task4(1, 0, 1, 11);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task4);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task3);

    taskSet0.addTask(&task4);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase17_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 80);
    Task task2(1, 0, 1, 20);
    Task task3(1, 0, 1, 20);
    Task task4(1, 0, 1, 40);
    Task task5(1, 0, 1, 10);
    Task task6(1, 0, 1, 40);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task5);
    taskChain2.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase17_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 7);
    Task task2(1, 1, 1, 28);
    Task task3(1, 1, 1, 14);
    Task task4(1, 0, 1, 28);
    Task task5(1, 0, 1, 56);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);




    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase17_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 100);
    Task task2(1, 0, 1, 100);
    Task task3(1, 0, 1, 50);
    Task task4(1, 1, 1, 200);
    Task task5(1, 0, 1, 25);
    Task task6(1, 1, 1, 50);
    Task task7(1, 0, 1, 20);

    Task task8(1, 2, 1, 50);
    Task task9(0, 1, 1, 20);
    Task task10(1, 1, 1, 200);
    Task task11(1, 0, 1, 25);
    Task task12(1, 1, 1, 100);
    Task task13(1, 2, 1, 200);
    Task task14(1, 0, 1, 50);
    Task task15(1, 1, 1, 100);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);
    taskChain1.addTask(task10);
    taskChain1.addTask(task5);

    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task8);
    taskChain2.addTask(task9);
    taskChain2.addTask(task4);


    TaskChain taskChain3;
    taskChain3.addTask(task15);
    taskChain3.addTask(task7);
    taskChain3.addTask(task14);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);

    taskSet0.addTask(&task4);

    taskSet0.addTask(&task5);

    taskSet0.addTask(&task6);

    taskSet0.addTask(&task7);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task8);

    taskSet1.addTask(&task9);

    taskSet1.addTask(&task10);

    taskSet1.addTask(&task11);

    taskSet1.addTask(&task12);

    taskSet1.addTask(&task13);

    taskSet1.addTask(&task14);

    taskSet1.addTask(&task15);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase18_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(0, 1, 0, 7);
    Task task2(1, 0, 1, 8);
    Task task3(1, 0, 1, 9);

    Task task4(0, 1, 0, 7);
    Task task5(1, 0, 1, 8);
    Task task6(1, 0, 1, 9);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task5);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);
    taskChain2.addTask(task6);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase19_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(0, 1, 0, 7);
    Task task2(1, 0, 1, 8);
    Task task3(1, 0, 1, 9);

    Task task4(0, 1, 0, 7);
    Task task5(1, 0, 1, 8);
    Task task6(1, 0, 1, 9);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task3);
    taskChain1.addTask(task5);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task6);
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase19_2(std::vector<TaskChain>& chains)
{

    // Declare Tasks

    Task task1(0, 1, 0, 8);
    Task task2(1, 0, 1, 7);

    Task task3(0, 1, 0, 6);
    Task task4(1, 0, 1, 9);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);
    taskChain2.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task3);

    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;

}

std::vector<TaskSet>  TestCase20_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(0, 1, 0, 7);
    Task task2(1, 0, 1, 8);
    Task task3(1, 0, 1, 9);

    Task task4(0, 1, 0, 7);
    Task task5(1, 0, 1, 8);
    Task task6(1, 0, 1, 9);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task6);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task5);
    taskChain2.addTask(task3);
    taskChain2.addTask(task4);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase20_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(0, 1, 0, 6);
    Task task2(1, 0, 1, 8);

    Task task3(0, 1, 0, 7);
    Task task4(1, 0, 1, 9);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task3);
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);
    taskChain2.addTask(task1);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase21_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 80);
    Task task2(1, 0, 1, 20);
    Task task3(1, 0, 1, 10);
    Task task4(1, 0, 1, 40);
    Task task5(1, 0, 1, 20);
    Task task6(1, 0, 1, 40);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task5);
    taskChain2.addTask(task3);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);
    taskSet1.addTask(&task5);
    taskSet1.addTask(&task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase21_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 7);
    Task task2(1, 1, 1, 56);
    Task task3(1, 1, 1, 14);
    Task task4(1, 0, 1, 28);
    Task task5(1, 0, 1, 56);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);
    taskChain2.addTask(task1);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase21_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 100);
    Task task2(1, 0, 1, 100);
    Task task3(1, 0, 1, 50);
    Task task4(1, 1, 1, 200);
    Task task5(1, 0, 1, 25);
    Task task6(1, 1, 1, 50);
    Task task7(1, 0, 1, 20);

    Task task8(1, 2, 1, 50);
    Task task9(0, 1, 1, 20);
    Task task10(1, 1, 1, 200);
    Task task11(1, 0, 1, 25);
    Task task12(1, 1, 1, 100);
    Task task13(1, 2, 1, 200);
    Task task14(1, 0, 1, 50);
    Task task15(1, 1, 1, 100);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);
    taskChain1.addTask(task11);
    taskChain1.addTask(task7);

    TaskChain taskChain2;
    taskChain2.addTask(task10);
    taskChain2.addTask(task15);
    taskChain2.addTask(task6);
    taskChain2.addTask(task9);


    TaskChain taskChain3;
    taskChain3.addTask(task14);
    taskChain3.addTask(task5);
    taskChain3.addTask(task9);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);

    taskSet0.addTask(&task4);

    taskSet0.addTask(&task5);

    taskSet0.addTask(&task6);

    taskSet0.addTask(&task7);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task8);

    taskSet1.addTask(&task9);

    taskSet1.addTask(&task10);

    taskSet1.addTask(&task11);

    taskSet1.addTask(&task12);

    taskSet1.addTask(&task13);

    taskSet1.addTask(&task14);

    taskSet1.addTask(&task15);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase22_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 80);
    Task task2(1, 0, 1, 20);
    Task task3(1, 0, 1, 10);
    Task task4(1, 0, 1, 40);
    Task task5(1, 0, 1, 20);
    Task task6(1, 0, 1, 40);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task4);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task5);
    taskChain2.addTask(task1);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase22_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 7);
    Task task2(1, 1, 1, 56);
    Task task3(1, 1, 1, 14);
    Task task4(1, 0, 1, 28);
    Task task5(1, 0, 1, 56);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase22_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 100);
    Task task2(1, 0, 1, 100);
    Task task3(1, 0, 1, 50);
    Task task4(1, 1, 1, 200);
    Task task5(1, 0, 1, 25);
    Task task6(1, 1, 1, 50);
    Task task7(1, 0, 1, 20);

    Task task8(1, 2, 1, 50);
    Task task9(0, 1, 1, 20);
    Task task10(1, 1, 1, 200);
    Task task11(1, 0, 1, 25);
    Task task12(1, 1, 1, 100);
    Task task13(1, 2, 1, 200);
    Task task14(1, 0, 1, 50);
    Task task15(1, 1, 1, 100);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task7);
    taskChain1.addTask(task11);
    taskChain1.addTask(task3);
    taskChain1.addTask(task1);

    TaskChain taskChain2;
    taskChain2.addTask(task9);
    taskChain2.addTask(task6);
    taskChain2.addTask(task15);
    taskChain2.addTask(task10);


    TaskChain taskChain3;
    taskChain3.addTask(task9);
    taskChain3.addTask(task5);
    taskChain3.addTask(task14);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);

    taskSet0.addTask(&task4);

    taskSet0.addTask(&task5);

    taskSet0.addTask(&task6);

    taskSet0.addTask(&task7);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task8);

    taskSet1.addTask(&task9);

    taskSet1.addTask(&task10);

    taskSet1.addTask(&task11);

    taskSet1.addTask(&task12);

    taskSet1.addTask(&task13);

    taskSet1.addTask(&task14);

    taskSet1.addTask(&task15);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase23_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 6);
    Task task2(1, 0, 1, 7);

    Task task3(0, 1, 0, 8);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);




    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase23_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 6);
    Task task2(0, 0, 1, 7);

    Task task3(0, 1, 0, 8);
    Task task4(1, 0, 1, 9);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task4);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase23_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(0, 1, 0, 6);
    Task task2(1, 0, 1, 7);
    Task task3(1, 0, 1, 8);

    Task task4(0, 1, 0, 9);
    Task task5(1, 0, 1, 10);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);

    TaskChain taskChain3;
    taskChain3.addTask(task3);
    taskChain3.addTask(task5);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);


    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase24_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 7);
    Task task2(1, 0, 1, 8);

    Task task3(0, 1, 0, 6);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);




    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase24_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 6);
    Task task2(0, 0, 1, 7);

    Task task3(0, 1, 0, 8);
    Task task4(1, 0, 1, 9);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task4);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task1);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase24_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(0, 1, 0, 6);
    Task task2(1, 0, 1, 7);

    Task task3(1, 0, 1, 8);
    Task task4(0, 1, 0, 9);
    Task task5(1, 0, 1, 10);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task4);
    taskChain1.addTask(task1);


    TaskChain taskChain2;
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);

    TaskChain taskChain3;
    taskChain3.addTask(task5);
    taskChain3.addTask(task3);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);


    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);



    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task4);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase25_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(0, 1, 0, 6);
    Task task2(0, 1, 0, 7);

    Task task3(1, 0, 1, 7);
    Task task4(1, 0, 1, 8);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task4);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase25_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(0, 1, 0, 6);
    Task task2(0, 1, 0, 7);
    Task task3(0, 1, 0, 7);

    Task task4(1, 0, 1, 7);
    Task task5(1, 0, 1, 7);
    Task task6(0, 1, 0, 6);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task4);


    TaskChain taskChain2;
    taskChain2.addTask(task2);
    taskChain2.addTask(task5);

    TaskChain taskChain3;
    taskChain3.addTask(task5);
    taskChain3.addTask(task6);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase26_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 40);
    Task task2(1, 0, 1, 20);
    Task task3(1, 0, 1, 20);
    Task task4(1, 0, 1, 40);
    Task task5(1, 0, 1, 20);
    Task task6(1, 0, 1, 40);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task5);
    taskChain1.addTask(task3);


    TaskChain taskChain2;
    taskChain2.addTask(task6);
    taskChain2.addTask(task1);
    taskChain2.addTask(task4);

    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);

    taskSet1.addTask(&task6);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase26_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 1, 1, 56);
    Task task2(1, 1, 1, 56);
    Task task3(1, 1, 1, 56);
    Task task4(1, 0, 1, 56);
    Task task5(1, 0, 1, 14);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task1);
    taskChain2.addTask(task4);
    taskChain2.addTask(task2);



    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);

    taskSet1.addTask(&task4);

    taskSet1.addTask(&task5);



    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase26_3(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(1, 0, 1, 100);
    Task task2(1, 0, 1, 100);
    Task task3(1, 0, 1, 50);
    Task task4(1, 1, 1, 200);
    Task task5(1, 0, 1, 25);
    Task task6(1, 1, 1, 50);
    Task task7(1, 0, 1, 20);

    Task task8(1, 2, 1, 50);
    Task task9(0, 1, 1, 20);
    Task task10(1, 1, 1, 200);
    Task task11(1, 0, 1, 25);
    Task task12(1, 1, 1, 100);
    Task task13(1, 2, 1, 200);
    Task task14(1, 0, 1, 50);
    Task task15(1, 1, 1, 100);

    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task15);
    taskChain1.addTask(task2);


    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task6);
    taskChain2.addTask(task14);
    taskChain2.addTask(task8);


    TaskChain taskChain3;
    taskChain3.addTask(task13);
    taskChain3.addTask(task12);
    taskChain3.addTask(task4);
    taskChain3.addTask(task10);


    // Add Chains

    chains.push_back(taskChain1);
    chains.push_back(taskChain2);
    chains.push_back(taskChain3);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);

    taskSet0.addTask(&task3);

    taskSet0.addTask(&task4);

    taskSet0.addTask(&task5);

    taskSet0.addTask(&task6);

    taskSet0.addTask(&task7);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task8);

    taskSet1.addTask(&task9);

    taskSet1.addTask(&task10);

    taskSet1.addTask(&task11);

    taskSet1.addTask(&task12);

    taskSet1.addTask(&task13);

    taskSet1.addTask(&task14);

    taskSet1.addTask(&task15);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase27_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(3, 5, 2, 23);
    Task task2(2, 6, 1, 21);


    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task2);


    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    TaskSet taskSet1(1);

    taskSet1.addTask(&task2);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase27_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(3, 2, 1, 19);
    Task task2(2, 3, 1, 21);
    Task task3(2, 3, 2, 23);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task3);
    taskChain1.addTask(task2);
    taskChain1.addTask(task1);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}


std::vector<TaskSet>  TestCase28_1(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(3, 2, 1, 19);
    Task task2(2, 3, 1, 21);
    Task task3(2, 3, 2, 23);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task2);
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);

    taskSet0.addTask(&task2);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

std::vector<TaskSet>  TestCase28_2(std::vector<TaskChain>& chains)
{
    // Declare Tasks

    Task task1(0, 1, 0, 6);

    Task task3(0, 1, 0, 8);



    // Create Chains

    TaskChain taskChain1;
    taskChain1.addTask(task1);
    taskChain1.addTask(task3);



    // Add Chains

    chains.push_back(taskChain1);

    // Create Tasks Sets

    TaskSet taskSet0(0);

    taskSet0.addTask(&task1);


    TaskSet taskSet1(1);

    taskSet1.addTask(&task3);


    // Add Task Sets

    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    // Return Task Sets

    return taskSets;


}

// Industrial Test-Case (Engine Managment System)

std::vector<TaskSet>  TestCaseIndustrial(std::vector<TaskChain>& chains)
{
    Task task1(908, 573000, 25, 1000000000);
    Task task2(958, 2461000, 195, 1000000000);
    Task task3(908, 86000, 28, 50000000);

    Task task4(908, 169000, 55, 50000000);
    Task task5(908, 482000, 55, 50000000);
    Task task6(55, 144000, 28, 100000000);

    Task task7(990, 2892000, 55, 100000000);
    Task task8(1013, 2957000, 83, 100000000);
    Task task9(990, 2892000, 55, 100000000);

    Task task10(1013, 2957000, 83, 100000000);
    Task task11(1148, 3188000, 28, 100000000);
    Task task12(1060, 2269000, 25, 1000000000);

    Task task13(988, 677000, 28, 100000000);
    Task task14(965, 19641000, 390, 200000000);
    Task task15(833, 843000, 240, 200000000);

    Task task16(908, 118000, 0, 1000000000);
    Task task17(28, 274000, 28, 1000000000);
    Task task18(985, 1651000, 195, 1000000000);



    TaskSet taskSet0(0);

    TaskSet taskSet1(1);


    taskSet0.addTask(&task1);
    taskSet0.addTask(&task3);
    taskSet0.addTask(&task5);
    taskSet0.addTask(&task6);
    taskSet0.addTask(&task8);
    taskSet0.addTask(&task10);
    taskSet0.addTask(&task12);
    taskSet0.addTask(&task13);
    taskSet0.addTask(&task15);
    taskSet0.addTask(&task16);
    taskSet0.addTask(&task17);

    taskSet1.addTask(&task2);
    taskSet1.addTask(&task4);
    taskSet1.addTask(&task7);
    taskSet1.addTask(&task9);
    taskSet1.addTask(&task11);
    taskSet1.addTask(&task14);
    taskSet1.addTask(&task18);




    std::vector<TaskSet> taskSets;

    taskSets.push_back(taskSet0);
    taskSets.push_back(taskSet1);

    TaskChain taskChain1;
    taskChain1.addTask(task5);
    taskChain1.addTask(task6);
    taskChain1.addTask(task7);
    taskChain1.addTask(task8);
    chains.push_back(taskChain1);

    TaskChain taskChain2;
    taskChain2.addTask(task3);
    taskChain2.addTask(task9);
    taskChain2.addTask(task11);
    taskChain2.addTask(task13);
    taskChain2.addTask(task18);

    chains.push_back(taskChain2);


    TaskChain taskChain3;
    taskChain3.addTask(task4);
    taskChain3.addTask(task7);
    taskChain3.addTask(task8);

    chains.push_back(taskChain3);


    return taskSets;
}