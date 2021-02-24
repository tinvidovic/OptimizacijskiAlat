#include "Model.h"


char* createIntervalVariableName(int taskID, int numberOfInstance, char phase)
{
    // The default name of interval variable: tau taskID instanceNumber phaseIdentifier
    char defaultIntervalVariableName[16] = "tau 0000 0000 X";

    char intervalVariableName[16];
    strcpy_s(intervalVariableName, defaultIntervalVariableName);

    // Set taskID
    intervalVariableName[4] = getFirstDigit(taskID) + '0';
    intervalVariableName[5] = getSecondDigit(taskID) + '0';
    intervalVariableName[6] = getThirdDigit(taskID) + '0';
    intervalVariableName[7] = getFourthDigit(taskID) + '0';


    // Set instanceNumber
    intervalVariableName[9] = getFirstDigit(numberOfInstance) + '0';
    intervalVariableName[10] = getSecondDigit(numberOfInstance) + '0';
    intervalVariableName[11] = getThirdDigit(numberOfInstance) + '0';
    intervalVariableName[12] = getFourthDigit(numberOfInstance) + '0';


    // Set phase identifier
    intervalVariableName[14] = phase;


    return intervalVariableName;
}

double createAndSolveModel(std::vector<TaskSet> taskSets, std::vector<TaskChain> taskChains, int numberOfSolutions, std::string logFile, int& status, int& numberOfConstraints, int timeLimit, int maximumInterCoreDelay, bool minimizeResponseTimes, int maximumNumberOfCommunicatingPairs)
{

    sat::CpModelBuilder cpModelBuilder;


    long long int hyperPeriod = 0;


    if (taskSets.at(0).getHyperperiod() != 0 && taskSets.at(1).getHyperperiod() != 0)
    {
        // The hyperperiods of individual task sets
        std::vector<long long int> hyperperiodsOfTaskSets;

        hyperperiodsOfTaskSets.push_back(taskSets.at(0).getHyperperiod());
        hyperperiodsOfTaskSets.push_back(taskSets.at(1).getHyperperiod());

        // The common hyperperiod needs to be considered
        hyperPeriod = findLeastCommonMultiple(hyperperiodsOfTaskSets);
        taskSets.at(0).setHyperperiod(hyperPeriod);
        taskSets.at(1).setHyperperiod(hyperPeriod);

    }
    else
    {
        hyperPeriod = taskSets.at(0).getHyperperiod();

        if (taskSets.at(1).getHyperperiod() > hyperPeriod) hyperPeriod = taskSets.at(1).getHyperperiod();

        taskSets.at(0).setHyperperiod(hyperPeriod);
        taskSets.at(1).setHyperperiod(hyperPeriod);


    }

    // Show application being scheduled

    // Show tasks on both cores

    for (int i = 0; i < taskSets.size(); i++)
    {
        std::cout << "Tasks on core " << i << ": " << std::endl;

        for (int j = 0; j < taskSets.at(i).getTasks().size(); j++)
        {
            std::cout << taskSets.at(i).getTasks().at(j);
        }
    }

    // Show Hyperperiod
    std::cout << std::endl << "Total hyperperiod: " << hyperPeriod << std::endl << std::endl;

    // Show Taskchains

    for (int i = 0; i < taskChains.size(); i++)
    {
        std::cout << "Chain " << i << ": " << std::endl;

        std::cout << taskChains.at(i);

    }

    // The vector that holds the number of task instances for each of the cores
    std::vector<int> numberInstancesCore;

    for (int i = 0; i < NUMBER_OF_CORES; i++)
    {

        numberInstancesCore.push_back(taskSets.at(i).getInstances().size());


    }


    // The Array of interval variables holding interval variables representing all the phases of all the instances
    std::vector<sat::IntervalVar> allPhasesOfInstances;

    // The vector that holds arrays of interval variables for each of the phases of each of the task instances for each of the cores
    std::vector<std::vector<sat::IntervalVar>> phasesOfInstancesOnCore;

    // The vector that holds arrays of interval variables for each of the phases of each of the task instances for each of the cores
    std::vector<std::vector<sat::IntervalVar>> instancesOnCore;

    for (int i = 0; i < NUMBER_OF_CORES; i++)
    {
        // The number of interval variables is equal to the number of task instances for each of the cores multiplied by the number of phases

        phasesOfInstancesOnCore.push_back(std::vector<sat::IntervalVar>(numberInstancesCore.at(i) * (int)NUMBER_OF_PHASES));
    }


    for (int i = 0; i < NUMBER_OF_CORES; i++)
    {
        // The number of interval variables is equal to the number of task instances for each of the cores multiplied by the number of phases
        instancesOnCore.push_back(std::vector<sat::IntervalVar>());
    }

    // The variable that holds the total number of interval variables for READ and WRITE phases for all cores
    int totalNumberOfRWPhases = 0;

    for (int i = 0; i < NUMBER_OF_CORES; i++)
    {
        // Only READ and WRITE phases are considered
        totalNumberOfRWPhases += numberInstancesCore.at(i) * (NUMBER_OF_PHASES - 1);
    }

    //std::cout << totalNumberOfRWPhases;

    // The array that holds interval variables for all READ and WRITE phases
    std::vector<sat::IntervalVar> ReadAndWriteInstaces(totalNumberOfRWPhases);

    // The variable that holds all helper H variables
    std::vector<int> helper();

    // The variable that keeps track of the number of interval variables
    int numberOfIntervalVar = 0;

    // The variable that keeps track of the number of interval variables for all READ and WRITE phases
    int numberOfReadAndWriteIntervalVar = 0;

    // The array of Zi expressions
    std::vector<sat::IntVar> consumerProducerPairVariablesForConsumerGlobal;

    //Variables used for minimizing response time
    std::vector<sat::IntVar> responseTimeDecisionVariables;

    // Array that holds interval variables for extra instances TODO
    std::vector<std::vector<sat::IntervalVar>> extraWriteInstances;

    // Array that holds interval variables for extra instances TODO
    std::vector<sat::IntVar> helperVariables;

    for (int i = 0; i < NUMBER_OF_CORES; i++)
    {
        extraWriteInstances.push_back(std::vector<sat::IntervalVar>());
    }


    std::cout << "CREATING DEICISON INTERVAL VARIABLES FOR TASKS..." << std::endl << std::endl;
    for (int core = 0; core < NUMBER_OF_CORES; core++)
    {
        for (int i = 0; i < numberInstancesCore.at(core); i++)
        {
            TaskInstance currentInstance = taskSets.at(core).getInstances().at(i);


            for (int j = 0; j < NUMBER_OF_PHASES; j++)
            {
                if (j == 0) // Create the interval variable representing the read phase
                {

                    // The start and end point is presented in detail in the master thesis

                    const Domain startDomain(currentInstance.getAbsoluteReleaseTime(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseExecutionTime());
                    const sat::IntVar startRead = cpModelBuilder.NewIntVar(startDomain);

                    const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead(), currentInstance.getAbsoluteDeadline() - (currentInstance.getTask().getWorstCaseExecute() + currentInstance.getTask().getWorstCaseWrite()));
                    const sat::IntVar endRead = cpModelBuilder.NewIntVar(endDomain);

                    const Domain lengthDomain(currentInstance.getTask().getWorstCaseRead(), currentInstance.getTask().getWorstCaseRead());
                    const sat::IntVar lengthRead = cpModelBuilder.NewIntVar(lengthDomain);


                    const sat::IntervalVar readPhase = cpModelBuilder.NewIntervalVar(startRead, lengthRead, endRead).WithName(createIntervalVariableName(currentInstance.getTask().getTaskId(), currentInstance.getNumberOfInstance(), 'R'));


                    // add to appropriate arrays
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = readPhase;

                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];
                    allPhasesOfInstances.push_back(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);
                    numberOfIntervalVar++;
                    numberOfReadAndWriteIntervalVar++;







                }

                else if (j == 1) // Create the interval variable representing the execute phase
                {
                    // The start and end point is presented in detail in the master thesis

                    const Domain startDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead(), currentInstance.getAbsoluteDeadline() - (currentInstance.getTask().getWorstCaseExecute() + currentInstance.getTask().getWorstCaseWrite()));
                    const sat::IntVar startExecute = cpModelBuilder.NewIntVar(startDomain);

                    const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + currentInstance.getTask().getWorstCaseExecute(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite());
                    const sat::IntVar endExecute = cpModelBuilder.NewIntVar(endDomain);

                    const Domain lengthDomain(currentInstance.getTask().getWorstCaseExecute(), currentInstance.getTask().getWorstCaseExecute());
                    const sat::IntVar lengthExecute = cpModelBuilder.NewIntVar(lengthDomain);


                    const sat::IntervalVar ExecutePhase = cpModelBuilder.NewIntervalVar(startExecute, lengthExecute, endExecute).WithName(createIntervalVariableName(currentInstance.getTask().getTaskId(), currentInstance.getNumberOfInstance(), 'E'));



                    // add to appropriate arrays
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = ExecutePhase;

                    allPhasesOfInstances.push_back(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    numberOfIntervalVar++;



                }

                else // Create the interval variable representing the write phase
                {
                    // The start and end point is presented in detail in the master thesis

                    const Domain startDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite());
                    const sat::IntVar startWrite = cpModelBuilder.NewIntVar(startDomain);

                    const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime(), currentInstance.getAbsoluteDeadline());
                    const sat::IntVar endWrite = cpModelBuilder.NewIntVar(endDomain);

                    const Domain lengthDomain(currentInstance.getTask().getWorstCaseWrite(), currentInstance.getTask().getWorstCaseWrite());
                    const sat::IntVar lengthWrite = cpModelBuilder.NewIntVar(lengthDomain);


                    const sat::IntervalVar WritePhase = cpModelBuilder.NewIntervalVar(startWrite, lengthWrite, endWrite).WithName(createIntervalVariableName(currentInstance.getTask().getTaskId(), currentInstance.getNumberOfInstance(), 'W'));

                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = WritePhase;



                    allPhasesOfInstances.push_back(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];





                    // If the response time minimization flag is set, create R variables
                    if (minimizeResponseTimes)
                    {
                        //responseTimeDecisionVariables.

                       // model.add(responseTimeDecisionVariables[responseTimeDecisionVariables.getSize() - 1] >= 0);
                       //model.add(responseTimeDecisionVariables[responseTimeDecisionVariables.getSize() - 1] <= currentInstance.getTask().getPeriod());

                        const Domain responseDomain(currentInstance.getTask().getWorstCaseExecutionTime(), currentInstance.getAbsoluteDeadline());
                        const sat::IntVar responseVariable = cpModelBuilder.NewIntVar(responseDomain).WithName(createIntervalVariableName(currentInstance.getTask().getTaskId(), currentInstance.getNumberOfInstance(), 'X'));

                        // add response time constraints
                        //sat::LinearExpr helperExpression;
                        //helperExpression.AddVar(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].EndVar());
                        //helperExpression.AddConstant(-currentInstance.getAbsoluteReleaseTime());

                        cpModelBuilder.AddEquality(responseVariable, sat::LinearExpr(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].EndVar()).AddConstant(-currentInstance.getAbsoluteReleaseTime()));

                        responseTimeDecisionVariables.push_back(responseVariable);


                    }

                    numberOfReadAndWriteIntervalVar++;

                    numberOfIntervalVar++;


                }

            }



            //std::cout << std::endl << "Number of interval var: " << numberOfIntervalVar << std::endl << std::endl;
            //std::cout << std::endl << "Size of phases: " << phasesOfInstancesOnCore.at(0).size() << std::endl << std::endl;



            // Execute phase must not start before read phase

            cpModelBuilder.AddGreaterOrEqual(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 2].StartVar(), phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3].EndVar());


            // Write phase must not start before execute phase

            cpModelBuilder.AddGreaterOrEqual(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].StartVar(), phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 2].EndVar());

            //std::cout << "TU Smo" << std::endl;


            // Add an interval variable representing the entire exectuion of currentInstance

            const Domain startDomain(currentInstance.getAbsoluteReleaseTime(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseExecutionTime());
            const sat::IntVar startInstance = cpModelBuilder.NewIntVar(startDomain);

            const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime(), currentInstance.getAbsoluteDeadline());
            const sat::IntVar endInstance = cpModelBuilder.NewIntVar(endDomain);

            const Domain lengthDomain(currentInstance.getTask().getWorstCaseExecutionTime(), currentInstance.getTask().getPeriod());
            const sat::IntVar lengthInstance = cpModelBuilder.NewIntVar(lengthDomain);


            const sat::IntervalVar instanceVariable = cpModelBuilder.NewIntervalVar(startInstance, lengthInstance, endInstance);

            // The instance starts when the corresponding Read Phase starts
            cpModelBuilder.AddEquality(instanceVariable.StartVar(), phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3].StartVar());


            // The instance ends when the corresponding Write Phase ends
            cpModelBuilder.AddEquality(instanceVariable.EndVar(), phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].EndVar());
            // add to appropriate array
            instancesOnCore.at(core).push_back(instanceVariable);

            // check to see if the instance is part of a chain
            bool isInAnyChain = false;
            for (int chain = 0; chain < taskChains.size(); chain++)
            {
                if (taskChains.at(chain).isInChain(currentInstance.getTask().getTaskId()))
                {
                    isInAnyChain = true;
                    break;
                }
            }

            // Create the final instance of the same task in the previous hyperperiod
            // The first instance of a consumer task in this hyperperiod can potentially communicate with the final instance in the previous hyperperiod
            if (i != numberInstancesCore.at(core) - 1)
            {


                if (taskSets.at(core).getInstances().at(i + 1).getTask().getTaskId() != currentInstance.getTask().getTaskId())
                {


                    if (isInAnyChain)
                    {

                        //std::cout << "Tu smo za i = " << i;
                        char name[21] = "extraInstanceTau0000";

                        name[16] = getFirstDigit(currentInstance.getTask().getTaskId()) + '0';
                        name[17] = getSecondDigit(currentInstance.getTask().getTaskId()) + '0';
                        name[18] = getThirdDigit(currentInstance.getTask().getTaskId()) + '0';
                        name[19] = getFourthDigit(currentInstance.getTask().getTaskId()) + '0';

                        const Domain startDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute() - taskSets.at(core).getHyperperiod(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite() - taskSets.at(core).getHyperperiod());
                        const sat::IntVar startExtraInstance = cpModelBuilder.NewIntVar(startDomain);

                        const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime() - taskSets.at(core).getHyperperiod(), 0);
                        const sat::IntVar endExtraInstance = cpModelBuilder.NewIntVar(endDomain);

                        const Domain lengthDomain(currentInstance.getTask().getWorstCaseWrite(), currentInstance.getTask().getWorstCaseWrite());
                        const sat::IntVar lengthExtraInstance = cpModelBuilder.NewIntVar(lengthDomain);


                        const sat::IntervalVar extraInstance = cpModelBuilder.NewIntervalVar(startExtraInstance, lengthExtraInstance, endExtraInstance).WithName(name);

                        // add to appropriate arrays
                        extraWriteInstances.at(core).push_back(extraInstance);

                        const Domain hyperperiodDomain(taskSets.at(core).getHyperperiod(), taskSets.at(core).getHyperperiod());
                        const sat::IntVar hyperperiodVar = cpModelBuilder.NewIntVar(hyperperiodDomain);

                        cpModelBuilder.AddEquality(hyperperiodVar, taskSets.at(core).getHyperperiod());

                        //sat::LinearExpr helperExpression;

                        //helperExpression.AddVar(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].StartVar());
                        //helperExpression.AddConstant(-taskSets.at(core).getHyperperiod());


                        cpModelBuilder.AddEquality(extraInstance.StartVar(), sat::LinearExpr(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].StartVar()).AddConstant(-taskSets.at(core).getHyperperiod()));




                    }


                }
            }

            else
            {

                if (isInAnyChain)
                {
                    //std::cout << "Tu smo za i = " << i;
                    char name[21] = "extraInstanceTau0000";

                    name[16] = getFirstDigit(currentInstance.getTask().getTaskId()) + '0';
                    name[17] = getSecondDigit(currentInstance.getTask().getTaskId()) + '0';
                    name[18] = getThirdDigit(currentInstance.getTask().getTaskId()) + '0';
                    name[19] = getFourthDigit(currentInstance.getTask().getTaskId()) + '0';

                    const Domain startDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute() - taskSets.at(core).getHyperperiod(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite() - taskSets.at(core).getHyperperiod());
                    const sat::IntVar startExtraInstance = cpModelBuilder.NewIntVar(startDomain);

                    const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime() - taskSets.at(core).getHyperperiod(), 0);
                    const sat::IntVar endExtraInstance = cpModelBuilder.NewIntVar(endDomain);

                    const Domain lengthDomain(currentInstance.getTask().getWorstCaseWrite(), currentInstance.getTask().getWorstCaseWrite());
                    const sat::IntVar lengthExtraInstance = cpModelBuilder.NewIntVar(lengthDomain);


                    const sat::IntervalVar extraInstance = cpModelBuilder.NewIntervalVar(startExtraInstance, lengthExtraInstance, endExtraInstance).WithName(name);

                    // add to appropriate arrays
                    extraWriteInstances.at(core).push_back(extraInstance);


                    const Domain hyperperiodDomain(taskSets.at(core).getHyperperiod(), taskSets.at(core).getHyperperiod());
                    const sat::IntVar hyperperiodVar = cpModelBuilder.NewIntVar(hyperperiodDomain);

                    cpModelBuilder.AddEquality(hyperperiodVar, taskSets.at(core).getHyperperiod());

                    //sat::LinearExpr helperExpression;

                    //helperExpression.AddVar(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].StartVar());
                    //helperExpression.AddConstant(-taskSets.at(core).getHyperperiod());


                    cpModelBuilder.AddEquality(extraInstance.StartVar(), sat::LinearExpr(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].StartVar()).AddConstant(-taskSets.at(core).getHyperperiod()));
                }

            }

        }
        numberOfIntervalVar = 0;
    }

    // Interval variables that correspond to phases of tasks instances should not overlap on each of the cores individually
    for (int i = 0; i < NUMBER_OF_CORES; i++)
    {
        //model.add(IloNoOverlap(environment, instancesOnCore.at(i)));
        cpModelBuilder.AddNoOverlap(instancesOnCore.at(i));
    }

    // To avoid crossbar-switch contetion, interval variables that correspond to READ and WRITE phases on all cores should not overlap
    //model.add(IloNoOverlap(environment, ReadAndWriteInstaces));
    cpModelBuilder.AddNoOverlap(ReadAndWriteInstaces);

    // number of communicating pairs
    int counter = 1;

    for (int chain = 0; chain < taskChains.size(); chain++)
    {
        // Chain Hyperperiod
        long long int chainHyperPeriod = taskChains.at(chain).getHyperperiod();

        for (int consumerTaskIndex = 1; consumerTaskIndex < taskChains.at(chain).getTasks().size(); consumerTaskIndex++) // Loop through all of the tasks in the chain except for the first one (has no producers)
        {

            // the consumer
            int consumerTaskId = taskChains.at(chain).getTasks().at(consumerTaskIndex).getTaskId();
            long long int consumerTaskPeriod = taskChains.at(chain).getTasks().at(consumerTaskIndex).getPeriod();
            int consumerCoreAssignedTo = taskChains.at(chain).getTasks().at(consumerTaskIndex).getCoreAssignedTo() - 1;
            long long int consumerExecutionTime = taskChains.at(chain).getTasks().at(consumerTaskIndex).getWorstCaseExecutionTime();



            //the producer
            int producerTaskIndex = consumerTaskIndex - 1;
            int producerTaskId = taskChains.at(chain).getTasks().at(producerTaskIndex).getTaskId();
            long long int producerTaskPeriod = taskChains.at(chain).getTasks().at(producerTaskIndex).getPeriod();
            int producerCoreAssignedTo = taskChains.at(chain).getTasks().at(producerTaskIndex).getCoreAssignedTo() - 1;
            long long int producerExecutionTime = taskChains.at(chain).getTasks().at(producerTaskIndex).getWorstCaseExecutionTime();

            // Get all instances on producer's core
            std::vector<TaskInstance> instancesOnProducersCore = taskSets.at(producerCoreAssignedTo).getInstances();

            // Get all instances on consumer's core
            std::vector<TaskInstance> instancesOnConsumersCore = taskSets.at(consumerCoreAssignedTo).getInstances();

            for (int consumerInstanceIndex = 0; consumerInstanceIndex < instancesOnConsumersCore.size(); consumerInstanceIndex++) // Loop through all the instances on the consumer's core
            {
                bool firstTime = true;

                //Select only instances of the consumer
                TaskInstance currentInstanceOnConsumersCore = instancesOnConsumersCore.at(consumerInstanceIndex);

                if (currentInstanceOnConsumersCore.getTask().getTaskId() == consumerTaskId)
                {


                    // The right Instance of consumer is selected

                    long long int startOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod;
                    long long int endOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod + consumerTaskPeriod;

                    // Create vector that holds all producer consumer communicating pairs for the current consumer

                    std::vector<sat::IntVar> consumerProducerPairVariablesForConsumer;

                    consumerProducerPairVariablesForConsumer.clear();

                    // Check if the interval of consumer overlaps with the interval of first instance of producer

                    for (int producerInstanceIndex = 0; producerInstanceIndex < instancesOnProducersCore.size(); producerInstanceIndex++) // Loop through all the instances on the producer's core
                    {

                        //Select only instances of the producer
                        TaskInstance currentInstanceOnProducersCore = instancesOnProducersCore.at(producerInstanceIndex);
                        if (currentInstanceOnProducersCore.getTask().getTaskId() == producerTaskId)
                        {

                            // The right instance of producer is seletcted

                            if (consumerCoreAssignedTo != producerCoreAssignedTo)
                            {
                                if (intervalsOverlap(0, producerTaskPeriod - producerExecutionTime, startOfConsumer + consumerExecutionTime, endOfConsumer) && firstTime)
                                {

                                    //std::cout << "Tu smo za: " << producerInstanceIndex << " i " << consumerInstanceIndex << std::endl;

                                    // The communication between the producer from the previous hyperperiod has been added already
                                    firstTime = false;

                                    int lastProducerInstanceIndex = producerInstanceIndex;
                                    while (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() * instancesOnProducersCore.at(lastProducerInstanceIndex).getTask().getPeriod() != taskSets.at(0).getHyperperiod())
                                    {
                                        lastProducerInstanceIndex++;
                                    }

                                    long long int startOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod;
                                    long long int endOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                    int indexOfProducerTaskOnCore = 0;

                                    for (int k = 0; k < taskSets.at(producerCoreAssignedTo).getTasks().size(); k++)
                                    {
                                        if (taskSets.at(producerCoreAssignedTo).getTasks().at(k).getTaskId() == producerTaskId)
                                        {
                                            indexOfProducerTaskOnCore = k;
                                        }
                                    }


                                    // For the extra instances in the previous hyperperiod:

                                    int indexOfExtraInstance = 0;

                                    for (int indexOfExtraWriteInstance = 0; indexOfExtraWriteInstance < extraWriteInstances.at(producerCoreAssignedTo).size(); indexOfExtraWriteInstance++)
                                    {

                                        // Create name for compariosn
                                        char name[21] = "extraInstanceTau0000";

                                        name[16] = getFirstDigit(producerTaskId) + '0';
                                        name[17] = getSecondDigit(producerTaskId) + '0';
                                        name[18] = getThirdDigit(producerTaskId) + '0';
                                        name[19] = getFourthDigit(producerTaskId) + '0';

                                        if (name[16] == extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraWriteInstance].Name()[16] && name[17] == extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraWriteInstance].Name()[17] && name[18] == extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraWriteInstance].Name()[18] && name[19] == extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraWriteInstance].Name()[19])
                                        {
                                            indexOfExtraInstance = indexOfExtraWriteInstance;
                                        }
                                    }

                                    // Create Zi constraints as described in the master thesis



                                    if (consumerProducerPairVariablesForConsumerGlobal.size() < maximumNumberOfCommunicatingPairs)
                                    {
                                        //TODO: Determine zi boundaries 

                                        //std::cout << "Extra smo za: " << hyperPeriod << " i " << consumerInstanceIndex << std::endl;

                                        const Domain startZi(-40 * hyperPeriod, 40 * hyperPeriod);
                                        const sat::IntVar zi = cpModelBuilder.NewIntVar(startZi);

                                        //IloExpr zi(environment);

                                        cpModelBuilder.AddEquality(zi, sat::LinearExpr::ScalProd({ phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex].StartVar(), extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraInstance].EndVar() }, { 1, -1 }));

                                        //zi = IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex]) - (IloEndOf(extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraInstance]));

                                        //model.add(zi);

                                        consumerProducerPairVariablesForConsumer.push_back(zi);

                                        consumerProducerPairVariablesForConsumerGlobal.push_back(zi);
                                    }


                                }
                                // Create Zi constraints as described in the master thesis

                                if (consumerProducerPairVariablesForConsumerGlobal.size() < maximumNumberOfCommunicatingPairs)
                                {

                                    //std::cout << "Tu smo za: " << producerInstanceIndex << " i " << consumerInstanceIndex << std::endl;
                                    //IloExpr zi(environment);

                                    //zi = IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex]) - IloEndOf(phasesOfInstancesOnCore.at(producerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * producerInstanceIndex + 2]);

                                   // model.add(zi);

                                    //consumerProducerPairVariablesForConsumer.add(zi);

                                   // consumerProducerPairVariablesForConsumerGlobal.add(zi);


                                    //TODO: Determine zi boundaries 

                                    const Domain startZi(-40 * hyperPeriod, 40 * hyperPeriod);
                                    const sat::IntVar zi = cpModelBuilder.NewIntVar(startZi);

                                    //IloExpr zi(environment);

                                    cpModelBuilder.AddEquality(zi, sat::LinearExpr::ScalProd({ phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex].StartVar(), phasesOfInstancesOnCore.at(producerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * producerInstanceIndex + 2].EndVar() }, { 1, -1 }));

                                    //zi = IloStartOf(phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex]) - (IloEndOf(extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraInstance]));

                                    //model.add(zi);

                                    consumerProducerPairVariablesForConsumer.push_back(zi);

                                    consumerProducerPairVariablesForConsumerGlobal.push_back(zi);

                                }
                                // Check if the instance of the producer can communicate with the instance of the consumer

                                long long int startOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod;
                                long long int endOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                if (canCommunicate(currentInstanceOnProducersCore, currentInstanceOnConsumersCore))
                                {
                                    long long int lowerBound = startOfConsumer - endOfProducer;



                                }

                            }


                        }

                    }

                    // Create additional MinusOne helper variable to help with selection


                    //const Domain startHelper(0, 2 * hyperPeriod);
                    //const sat::IntVar Helper = cpModelBuilder.NewIntVar(startHelper);

                    //cpModelBuilder.AddGreaterOrEqual(Helper, 0);

                    //cpModelBuilder.AddMinEquality(Helper, consumerProducerPairVariablesForConsumer);

                    //helperVariables.push_back(Helper);

                    const Domain minusOneDomain(-1, -1);
                    const sat::IntVar  minusOne = cpModelBuilder.NewIntVar(minusOneDomain);

                    cpModelBuilder.AddEquality(minusOne, -1);

                    consumerProducerPairVariablesForConsumer.push_back(minusOne);

                    for (int consumerProducerPairIndex = 0; consumerProducerPairIndex < consumerProducerPairVariablesForConsumer.size() - 1; consumerProducerPairIndex++)
                    {
                        const Domain startHelper(-40 * hyperPeriod, 40 * hyperPeriod);
                        const sat::IntVar helper = cpModelBuilder.NewIntVar(startHelper);

                        const sat::BoolVar b = cpModelBuilder.NewBoolVar();

                        cpModelBuilder.AddLessThan(consumerProducerPairVariablesForConsumer[(long long int) consumerProducerPairIndex + (long long int)1], 0).OnlyEnforceIf(b);
                        cpModelBuilder.AddGreaterOrEqual(consumerProducerPairVariablesForConsumer[(long long int) consumerProducerPairIndex + (long long int)1], 0).OnlyEnforceIf(Not(b));

                        const Domain startHelper2(-40 * hyperPeriod, 40 * hyperPeriod);
                        const sat::IntVar helper2 = cpModelBuilder.NewIntVar(startHelper2);

                        cpModelBuilder.AddAbsEquality(helper2, consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]);

                        //sat::LinearExpr helperValue;
                        //helperValue.AddVar(helper2);
                        //helperValue.AddVar(consumerProducerPairVariablesForConsumer[consumerProducerPairIndex]);

                        cpModelBuilder.AddEquality(helper, sat::LinearExpr::Sum({ consumerProducerPairVariablesForConsumer[consumerProducerPairIndex], helper2 })).OnlyEnforceIf(b);
                        cpModelBuilder.AddEquality(helper, 0).OnlyEnforceIf(Not(b));

                        helperVariables.push_back(helper);
                    }

                }

            }
        }

    }


    const Domain objVarDomain(0, consumerProducerPairVariablesForConsumerGlobal.size() * hyperPeriod);
    const sat::IntVar  objVar = cpModelBuilder.NewIntVar(objVarDomain);

    cpModelBuilder.AddEquality(objVar, sat::LinearExpr::Sum(helperVariables));

    cpModelBuilder.Minimize(objVar);

    // Solving part.
    sat::Model model;

    //model.TakeOwnership(&cpModelBuilder);

    // Sets search parameters.
    sat::SatParameters parameters;
    //parameters.set_use_sat_inprocessing(true);
    parameters.set_num_search_workers(4);
    //parameters.set_cp_model_presolve(true);
    parameters.set_cp_model_use_sat_presolve(true);
    //parameters.set_search_branching(sat::SatParameters::FIXED_SEARCH);
    //parameters.set_exploit_objective(true);
    //parameters.set_instantiate_all_variables(true);

    // Sets time limit
    parameters.set_max_time_in_seconds(timeLimit);

    model.Add(NewSatParameters(parameters));


    // Solve.
    std::cout << std::endl << "SOLVING..." << std::endl;

    // Initialize time
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point end;

    numberOfConstraints = cpModelBuilder.Build().constraints().size();

    std::cout << "CONSTRAINTS: " << numberOfConstraints;

    sat::CpSolverResponse response = SolveCpModel(cpModelBuilder.Build(), &model);

    if (minimizeResponseTimes)
    {

        std::cout << "Solved, MINIMIZING RESPONSE TIMES!" << std::endl;
        // Add constraint to keep schedules optimal from the perspective of inter-core data-propagation delays
        cpModelBuilder.AddEquality(objVar, response.objective_value());

        // Add new objective function
        const Domain objVarResponseDomain(0, 1000000000000);
        const sat::IntVar  objVarResponse = cpModelBuilder.NewIntVar(objVarResponseDomain);
        cpModelBuilder.AddEquality(objVarResponse, sat::LinearExpr::Sum(responseTimeDecisionVariables));

        cpModelBuilder.Minimize(objVarResponse);

        // Solving part.
        sat::Model model2;

        //model.TakeOwnership(&cpModelBuilder);

        // Sets search parameters.
        sat::SatParameters parameters;
        //parameters.set_use_sat_inprocessing(true);
        parameters.set_num_search_workers(4);
        //parameters.set_cp_model_presolve(true);
        parameters.set_cp_model_use_sat_presolve(true);
        //parameters.set_search_branching(sat::SatParameters::FIXED_SEARCH);
        //parameters.set_exploit_objective(true);
        //parameters.set_instantiate_all_variables(true);

        // Sets time limit
        parameters.set_max_time_in_seconds(timeLimit);

        model2.Add(NewSatParameters(parameters));



        response = SolveCpModel(cpModelBuilder.Build(), &model2);
    }

    LOG(INFO) << sat::CpSolverResponseStats(response);

    end = std::chrono::steady_clock::now();

    if (response.status() == sat::CpSolverStatus::OPTIMAL)
    {
        status = 0;
    }
    else if (response.status() == sat::CpSolverStatus::FEASIBLE)
    {
        status = 1;
    }
    else
    {
        status = 2;

    }


    if (response.status() == sat::CpSolverStatus::OPTIMAL || response.status() == sat::CpSolverStatus::FEASIBLE)
    {

        for (int core = 0; core < NUMBER_OF_CORES; core++)
        {
            bool first = true;

            for (int i = 0; i < numberInstancesCore.at(core) * NUMBER_OF_PHASES; i++)
            {
                if (first)
                {

                    first = false;

                    std::cout << "************ CORE " << core << " ************" << std::endl;
                }

                LOG(INFO) << phasesOfInstancesOnCore.at(core)[i].Name() << ": " << SolutionIntegerValue(response, phasesOfInstancesOnCore.at(core)[i].StartVar()) << " - " << SolutionIntegerValue(response, phasesOfInstancesOnCore.at(core)[i].EndVar()) << std::endl;

            }

        }

        bool first = true;
        for (int i = 0; i < consumerProducerPairVariablesForConsumerGlobal.size(); i++)
        {
            if (first)
            {
                first = false;

                std::cout << "************ Z_i: " << " ************" << std::endl;
            }

            LOG(INFO) << consumerProducerPairVariablesForConsumerGlobal[i].Name() << ": " << SolutionIntegerValue(response, consumerProducerPairVariablesForConsumerGlobal[i]) << std::endl;

        }

        first = true;
        for (int i = 0; i < helperVariables.size(); i++)
        {
            if (first)
            {
                first = false;

                std::cout << "************ helper: " << " ************" << std::endl;
            }

            LOG(INFO) << helperVariables[i].Name() << ": " << SolutionIntegerValue(response, helperVariables[i]) << std::endl;

        }

        first = true;
        for (int i = 0; i < responseTimeDecisionVariables.size(); i++)
        {
            if (first)
            {
                first = false;

                std::cout << "************ responseTimes: " << " ************" << std::endl;
            }

            LOG(INFO) << responseTimeDecisionVariables[i].Name() << ": " << SolutionIntegerValue(response, responseTimeDecisionVariables[i]) << std::endl;

        }

    }

    //std::cout << response.solution_info();

    //model.~Model();
    //solver.~Solver();

    //model.~Model();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

}