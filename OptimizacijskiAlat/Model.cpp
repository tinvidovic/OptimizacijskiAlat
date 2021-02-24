#include "Model.h"


string createIntervalVariableName(string instanceName, string phase)
{
    string intervalVariableName;

    intervalVariableName = instanceName + " " + phase;


    return intervalVariableName;
}

double createAndSolveModel(std::vector<TaskSet>& taskSets, std::vector<TaskChain>& taskChains, int numberOfSolutions, int& status, int& numberOfConstraints, int timeLimit, int maximumInterCoreDelay, bool minimizeResponseTimes)
{

    sat::CpModelBuilder cpModelBuilder;


    long long int hyperPeriod = 0;

    
   

    // Treba razmatrati ukupni hiperperiod
    hyperPeriod = getTotalHyperperiod(taskSets);

    // Broj jezgri
    int numberOfCores = taskSets.size();

    // Vektor koji cuva broj intanci na svakoj od jezgri
    std::vector<int> numberInstancesCore;

    for (int i = 0; i < numberOfCores; i++)
    {
        numberInstancesCore.push_back(taskSets.at(i).getInstances().size());
        
    }


    // Vektor intervalskih varijabli koji cuva sve faze svih instanci u ugradbenoj aplikaciji
    std::vector<sat::IntervalVar> allPhasesOfInstances;

    // Vektor koji cuva intervalske varijable faza instanci na pojedinacim jezgrima
    std::vector<std::vector<sat::IntervalVar>> phasesOfInstancesOnCore;

    for (int i = 0; i < numberOfCores; i++)
    {
        // Broj intervalskih varijabli je jednak broju instanci na jezgri * broj faza REW modela
        phasesOfInstancesOnCore.push_back(std::vector<sat::IntervalVar>(numberInstancesCore.at(i) * (int)NUMBER_OF_PHASES));
    }

    // Vektor koji cuva intervalske varijable instanci na pojedinacnim jezgrima
    std::vector<std::vector<sat::IntervalVar>> instancesOnCore;

    for (int i = 0; i < numberOfCores; i++)
    {
        instancesOnCore.push_back(std::vector<sat::IntervalVar>());
    }

    // Varijabla koja cuva broj RW faza na svim jezgrima
    int totalNumberOfRWPhases = 0;

    for (int i = 0; i < numberOfCores; i++)
    {
        // Ne racuna se execute faza
        totalNumberOfRWPhases += numberInstancesCore.at(i) * (NUMBER_OF_PHASES - 1);
    }

    // Vektor koji cuva intervalkse varijable svih RW faza
    std::vector<sat::IntervalVar> ReadAndWriteInstaces(totalNumberOfRWPhases);

    int numberOfIntervalVar = 0;

    int numberOfReadAndWriteIntervalVar = 0;

    // Vektor koji cuva Zi integer varijable
    std::vector<sat::IntVar> consumerProducerPairVariablesForConsumerGlobal;

    // Vektor koji cuva Ri integer varijable
    std::vector<sat::IntVar> responseTimeDecisionVariables;

    // Vektor koji cuva intervalske varijable dodatnih instanci iz prethodnog hiperperioda
    std::vector<std::vector<sat::IntervalVar>> extraWriteInstances;

    for (int i = 0; i < numberOfCores; i++)
    {
        extraWriteInstances.push_back(std::vector<sat::IntervalVar>());
    }

    // VEktor koji cuva pomocne integer varijable H
    std::vector<sat::IntVar> helperVariables;


    std::cout << "Creating interval decision variables for tasks..." << std::endl << std::endl;
    for (int core = 0; core < numberOfCores; core++)
    {

        
        for (int i = 0; i < numberInstancesCore.at(core); i++)
        {
            TaskInstance currentInstance = taskSets.at(core).getInstances().at(i);


            for (int j = 0; j < NUMBER_OF_PHASES; j++)
            {
                if (j == 0) // Kreiraj intervalske varijable za READ fazu
                {

                    // vrijednosti objasnjene u tezi u sekciji implementacija

                    const Domain startDomain(currentInstance.getAbsoluteReleaseTime(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseExecutionTime());
                    const sat::IntVar startRead = cpModelBuilder.NewIntVar(startDomain);

                    const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead(), currentInstance.getAbsoluteDeadline() - (currentInstance.getTask().getWorstCaseExecute() + currentInstance.getTask().getWorstCaseWrite()));
                    const sat::IntVar endRead = cpModelBuilder.NewIntVar(endDomain);

                    const Domain lengthDomain(currentInstance.getTask().getWorstCaseRead(), currentInstance.getTask().getWorstCaseRead());
                    const sat::IntVar lengthRead = cpModelBuilder.NewIntVar(lengthDomain);


                    const sat::IntervalVar readPhase = cpModelBuilder.NewIntervalVar(startRead, lengthRead, endRead).WithName(createIntervalVariableName(currentInstance.getName(), "READ"));


                    // dodaj intervalsku varijablu u adekvatne vektore
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = readPhase;
                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];
                    allPhasesOfInstances.push_back(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    numberOfIntervalVar++;
                    numberOfReadAndWriteIntervalVar++;


                }

                else if (j == 1) // Kreiraj intervalske varijable za EXECUTE fazu
                {
                    // vrijednosti objasnjene u tezi u sekciji implementacija

                    const Domain startDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead(), currentInstance.getAbsoluteDeadline() - (currentInstance.getTask().getWorstCaseExecute() + currentInstance.getTask().getWorstCaseWrite()));
                    const sat::IntVar startExecute = cpModelBuilder.NewIntVar(startDomain);

                    const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + currentInstance.getTask().getWorstCaseExecute(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite());
                    const sat::IntVar endExecute = cpModelBuilder.NewIntVar(endDomain);

                    const Domain lengthDomain(currentInstance.getTask().getWorstCaseExecute(), currentInstance.getTask().getWorstCaseExecute());
                    const sat::IntVar lengthExecute = cpModelBuilder.NewIntVar(lengthDomain);


                    const sat::IntervalVar ExecutePhase = cpModelBuilder.NewIntervalVar(startExecute, lengthExecute, endExecute).WithName(createIntervalVariableName(currentInstance.getName(), "EXECUTE"));



                    // dodaj intervalsku varijablu u adekvatne vektore
                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = ExecutePhase;

                    allPhasesOfInstances.push_back(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    numberOfIntervalVar++;



                }

                else // Kreiraj intervalske varijable za WRITE fazu
                {
                    // vrijednosti objasnjene u tezi u sekciji implementacija

                    const Domain startDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite());
                    const sat::IntVar startWrite = cpModelBuilder.NewIntVar(startDomain);

                    const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime(), currentInstance.getAbsoluteDeadline());
                    const sat::IntVar endWrite = cpModelBuilder.NewIntVar(endDomain);

                    const Domain lengthDomain(currentInstance.getTask().getWorstCaseWrite(), currentInstance.getTask().getWorstCaseWrite());
                    const sat::IntVar lengthWrite = cpModelBuilder.NewIntVar(lengthDomain);


                    const sat::IntervalVar WritePhase = cpModelBuilder.NewIntervalVar(startWrite, lengthWrite, endWrite).WithName(createIntervalVariableName(currentInstance.getName(), "WRITE"));



                    // dodaj intervalsku varijablu u adekvatne vektore

                    phasesOfInstancesOnCore.at(core)[numberOfIntervalVar] = WritePhase;

                    allPhasesOfInstances.push_back(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar]);

                    ReadAndWriteInstaces[numberOfReadAndWriteIntervalVar] = phasesOfInstancesOnCore.at(core)[numberOfIntervalVar];


                    // Ako je postavljen flag za minimizaciju vremena odziva, kreiraj R varijable
                    if (minimizeResponseTimes)
                    {

                        const Domain responseDomain(currentInstance.getTask().getWorstCaseExecutionTime(), currentInstance.getAbsoluteDeadline());
                        const sat::IntVar responseVariable = cpModelBuilder.NewIntVar(responseDomain).WithName(createIntervalVariableName(currentInstance.getName(), "RESPONSE"));

                        // vrijednosti objasnjene u tezi u sekciji implementacija
                        cpModelBuilder.AddEquality(responseVariable, sat::LinearExpr(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar].EndVar()).AddConstant(-1 * currentInstance.getAbsoluteReleaseTime()));

                        responseTimeDecisionVariables.push_back(responseVariable);


                    }

                    numberOfReadAndWriteIntervalVar++;

                    numberOfIntervalVar++;


                }

            }


            // Execute faza ne smije poceti prije kraja Read faze

            cpModelBuilder.AddGreaterOrEqual(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 2].StartVar(), phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3].EndVar());


            // Write faza ne smije poceti prije kraja Execute faze

            cpModelBuilder.AddGreaterOrEqual(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].StartVar(), phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 2].EndVar());

            // Kreiraj intervalsku varijablu koja predstavlja cijelu instancu

            const Domain startDomain(currentInstance.getAbsoluteReleaseTime(), currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseExecutionTime());
            const sat::IntVar startInstance = cpModelBuilder.NewIntVar(startDomain);

            const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime(), currentInstance.getAbsoluteDeadline());
            const sat::IntVar endInstance = cpModelBuilder.NewIntVar(endDomain);

            const Domain lengthDomain(currentInstance.getTask().getWorstCaseExecutionTime(), currentInstance.getTask().getPeriod());
            const sat::IntVar lengthInstance = cpModelBuilder.NewIntVar(lengthDomain);


            const sat::IntervalVar instanceVariable = cpModelBuilder.NewIntervalVar(startInstance, lengthInstance, endInstance);

            // Ogranici na pocetak Read faze
            cpModelBuilder.AddEquality(instanceVariable.StartVar(), phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 3].StartVar());


            // Ogranici na kraj Write faze
            cpModelBuilder.AddEquality(instanceVariable.EndVar(), phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].EndVar());

            // dodaj intervalsku varijablu u adekvatne vektore
            instancesOnCore.at(core).push_back(instanceVariable);
            // Provjeri da li je dio lanca
            bool isInAnyChain = false;
            for (int chain = 0; chain < taskChains.size(); chain++)
            {


                if (taskChains.at(chain).isInChain(currentInstance.getTask().getId()))
                {
                    isInAnyChain = true;
                    break;
                }
            }

            // Kreiraj ekstra varijablu iz prethodnog hiperperioda za zadatke u lancima
            if (i != numberInstancesCore.at(core) - 1)
            {


                if (taskSets.at(core).getInstances().at(i + 1).getTask().getId() != currentInstance.getTask().getId())
                {


                    if (isInAnyChain)
                    {


                        const Domain startDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute() - hyperPeriod, currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite() - hyperPeriod);
                        const sat::IntVar startExtraInstance = cpModelBuilder.NewIntVar(startDomain);

                        const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime() - hyperPeriod, 0);
                        const sat::IntVar endExtraInstance = cpModelBuilder.NewIntVar(endDomain);

                        const Domain lengthDomain(currentInstance.getTask().getWorstCaseWrite(), currentInstance.getTask().getWorstCaseWrite());
                        const sat::IntVar lengthExtraInstance = cpModelBuilder.NewIntVar(lengthDomain);


                        const sat::IntervalVar extraInstance = cpModelBuilder.NewIntervalVar(startExtraInstance, lengthExtraInstance, endExtraInstance).WithName(createIntervalVariableName(currentInstance.getName(), "EXTRA"));

                        // dodaj u adekvatne vektore
                        extraWriteInstances.at(core).push_back(extraInstance);

                        const Domain hyperperiodDomain(hyperPeriod, hyperPeriod);
                        const sat::IntVar hyperperiodVar = cpModelBuilder.NewIntVar(hyperperiodDomain);

                        cpModelBuilder.AddEquality(hyperperiodVar, hyperPeriod);

                        cpModelBuilder.AddEquality(extraInstance.StartVar(), sat::LinearExpr(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].StartVar()).AddConstant(-1 * hyperPeriod));

                    }


                }
            }

            else
            {

                if (isInAnyChain)
                {


                    const Domain startDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseRead() + taskSets.at(core).getInstances().at(i).getTask().getWorstCaseExecute() - hyperPeriod, currentInstance.getAbsoluteDeadline() - currentInstance.getTask().getWorstCaseWrite() - hyperPeriod);
                    const sat::IntVar startExtraInstance = cpModelBuilder.NewIntVar(startDomain);

                    const Domain endDomain(currentInstance.getAbsoluteReleaseTime() + currentInstance.getTask().getWorstCaseExecutionTime() - hyperPeriod, 0);
                    const sat::IntVar endExtraInstance = cpModelBuilder.NewIntVar(endDomain);

                    const Domain lengthDomain(currentInstance.getTask().getWorstCaseWrite(), currentInstance.getTask().getWorstCaseWrite());
                    const sat::IntVar lengthExtraInstance = cpModelBuilder.NewIntVar(lengthDomain);


                    const sat::IntervalVar extraInstance = cpModelBuilder.NewIntervalVar(startExtraInstance, lengthExtraInstance, endExtraInstance).WithName(createIntervalVariableName(currentInstance.getName(), "EXTRA"));

                    // add to appropriate arrays
                    extraWriteInstances.at(core).push_back(extraInstance);


                    const Domain hyperperiodDomain(hyperPeriod, hyperPeriod);
                    const sat::IntVar hyperperiodVar = cpModelBuilder.NewIntVar(hyperperiodDomain);

                    cpModelBuilder.AddEquality(hyperperiodVar, hyperPeriod);


                    cpModelBuilder.AddEquality(extraInstance.StartVar(), sat::LinearExpr(phasesOfInstancesOnCore.at(core)[numberOfIntervalVar - 1].StartVar()).AddConstant(-1 * hyperPeriod));
                }

            }

        }

            
        numberOfIntervalVar = 0;
    }

    // Instance na jednoj jezgri se ne smiju preklapati
    for (int i = 0; i < numberOfCores; i++)
    {
        cpModelBuilder.AddNoOverlap(instancesOnCore.at(i));
    }

    // Memorijske faze se ne smiju preklapati
    cpModelBuilder.AddNoOverlap(ReadAndWriteInstaces);

    // Broj komunikacijskih parova
    int counter = 1;

    for (int chain = 0; chain < taskChains.size(); chain++)
    {
        // hiperperiod lanca
        long long int chainHyperPeriod = taskChains.at(chain).getHyperperiod();

        for (int consumerTaskIndex = 1; consumerTaskIndex < taskChains.at(chain).getTasks().size(); consumerTaskIndex++) // prodji kroz sve zadatke lanca osim prvog )nema proizvodjaca
        {

            // the consumer
            int consumerTaskId = taskChains.at(chain).getTasks().at(consumerTaskIndex).getId();
            long long int consumerTaskPeriod = taskChains.at(chain).getTasks().at(consumerTaskIndex).getPeriod();
            int consumerCoreAssignedTo = taskChains.at(chain).getTasks().at(consumerTaskIndex).getCore();
            long long int consumerExecutionTime = taskChains.at(chain).getTasks().at(consumerTaskIndex).getWorstCaseExecutionTime();



            //the producer
            int producerTaskIndex = consumerTaskIndex - 1;
            int producerTaskId = taskChains.at(chain).getTasks().at(producerTaskIndex).getId();
            long long int producerTaskPeriod = taskChains.at(chain).getTasks().at(producerTaskIndex).getPeriod();
            int producerCoreAssignedTo = taskChains.at(chain).getTasks().at(producerTaskIndex).getCore();
            long long int producerExecutionTime = taskChains.at(chain).getTasks().at(producerTaskIndex).getWorstCaseExecutionTime();

            // Dobavi sve instance sa jezgre proizvodjaca
            std::vector<TaskInstance> instancesOnProducersCore = taskSets.at(producerCoreAssignedTo).getInstances();

            // Dobavi sve instance sa jezgre potrosaca
            std::vector<TaskInstance> instancesOnConsumersCore = taskSets.at(consumerCoreAssignedTo).getInstances();

            for (int consumerInstanceIndex = 0; consumerInstanceIndex < instancesOnConsumersCore.size(); consumerInstanceIndex++) // Loop through all the instances on the consumer's core
            {
                bool firstTime = true;

                // Biraj samo instance potrosaca
                TaskInstance currentInstanceOnConsumersCore = instancesOnConsumersCore.at(consumerInstanceIndex);

                if (currentInstanceOnConsumersCore.getTask().getId() == consumerTaskId)
                {


                    // Odabrana je tacna instanca potrosaca

                    long long int startOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod;
                    long long int endOfConsumer = (currentInstanceOnConsumersCore.getNumberOfInstance() - 1) * consumerTaskPeriod + consumerTaskPeriod;

                    // Kreiraj vektor koji drzi sve komunicirajuce parove za trenutnog potrosaca

                    std::vector<sat::IntVar> consumerProducerPairVariablesForConsumer;

                    consumerProducerPairVariablesForConsumer.clear();

                    // Da li potencijalno komuniciraju?

                    for (int producerInstanceIndex = 0; producerInstanceIndex < instancesOnProducersCore.size(); producerInstanceIndex++) // Prodji kroz sve instance na proizvodjacevoj jezgri
                    {

                        //Select only instances of the producer
                        TaskInstance currentInstanceOnProducersCore = instancesOnProducersCore.at(producerInstanceIndex);
                        if (currentInstanceOnProducersCore.getTask().getId() == producerTaskId)
                        {

                            // Odabrana je tacna instanca proizvodjaca

                            if (consumerCoreAssignedTo != producerCoreAssignedTo)
                            {
                                if (intervalsOverlap(0, producerTaskPeriod - producerExecutionTime, startOfConsumer + consumerExecutionTime, endOfConsumer) && firstTime)
                                {


                                    // komunicirajuci par je vec modeliran
                                    firstTime = false;

                                    int lastProducerInstanceIndex = producerInstanceIndex;
                                    while (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance()  * instancesOnProducersCore.at(lastProducerInstanceIndex).getTask().getPeriod() != taskSets.at(producerCoreAssignedTo).getHyperperiod())
                                    {
                                        lastProducerInstanceIndex++;
                                    }

                                    long long int startOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod;
                                    long long int endOfLastProducer = (instancesOnProducersCore.at(lastProducerInstanceIndex).getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                    int indexOfProducerTaskOnCore = 0;

                                    for (int k = 0; k < taskSets.at(producerCoreAssignedTo).getTasks().size(); k++)
                                    {
                                        if (taskSets.at(producerCoreAssignedTo).getTasks().at(k).getId() == producerTaskId)
                                        {
                                            indexOfProducerTaskOnCore = k;
                                        }
                                    }


                                    // Za dodatne instance u prethodnom periodu:

                                    int indexOfExtraInstance = 0;

                                    for (int indexOfExtraWriteInstance = 0; indexOfExtraWriteInstance < extraWriteInstances.at(producerCoreAssignedTo).size(); indexOfExtraWriteInstance++)
                                    {

                                        // Kreiraj ime za poredjenje

                                        string name = createIntervalVariableName(instancesOnProducersCore.at(lastProducerInstanceIndex).getName(), "EXTRA");

                                        string extraInstanceName = extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraWriteInstance].Name();
                                        if (name == extraInstanceName)
                                        {
                                            indexOfExtraInstance = indexOfExtraWriteInstance;
                                        }
                                    }

                                    // Kreiraj Zi constraintove

                                    const Domain startZi(-40 * hyperPeriod, 40 * hyperPeriod);
                                    const sat::IntVar zi = cpModelBuilder.NewIntVar(startZi);



                                    cpModelBuilder.AddEquality(zi, sat::LinearExpr::ScalProd({ phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex].StartVar(), extraWriteInstances.at(producerCoreAssignedTo)[indexOfExtraInstance].EndVar() }, { 1, -1 }));


                                    consumerProducerPairVariablesForConsumer.push_back(zi);

                                    consumerProducerPairVariablesForConsumerGlobal.push_back(zi);



                                }
                                // Kreiraj Zi constraintove

                                const Domain startZi(-40 * hyperPeriod, 40 * hyperPeriod);
                                const sat::IntVar zi = cpModelBuilder.NewIntVar(startZi);



                                cpModelBuilder.AddEquality(zi, sat::LinearExpr::ScalProd({ phasesOfInstancesOnCore.at(consumerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * consumerInstanceIndex].StartVar(), phasesOfInstancesOnCore.at(producerCoreAssignedTo)[(long long int) NUMBER_OF_PHASES * producerInstanceIndex + 2].EndVar() }, { 1, -1 }));

                                consumerProducerPairVariablesForConsumer.push_back(zi);

                                consumerProducerPairVariablesForConsumerGlobal.push_back(zi);


                                // Provjeri da li instance mogu komunicirati

                                long long int startOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod;
                                long long int endOfProducer = (currentInstanceOnProducersCore.getNumberOfInstance() - 1) * producerTaskPeriod + producerTaskPeriod;

                                if (canCommunicate(currentInstanceOnProducersCore, currentInstanceOnConsumersCore))
                                {
                                    long long int lowerBound = startOfConsumer - endOfProducer;

                                }

                            }


                        }

                    }

                    // Kreiraj dodatnu pomocnu varijablu jednaku -1 za laksi odabri

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


                        cpModelBuilder.AddEquality(helper, sat::LinearExpr::Sum({ consumerProducerPairVariablesForConsumer[consumerProducerPairIndex], helper2 })).OnlyEnforceIf(b);
                        cpModelBuilder.AddEquality(helper, 0).OnlyEnforceIf(Not(b));

                        helperVariables.push_back(helper);
                    }

                }

            }
        }

    }
    

    // Kreiraj funkciju cilja

    const Domain objVarDomain(0, consumerProducerPairVariablesForConsumerGlobal.size()* hyperPeriod);
    const sat::IntVar  objVar = cpModelBuilder.NewIntVar(objVarDomain);

    cpModelBuilder.AddEquality(objVar, sat::LinearExpr::Sum(helperVariables));

    cpModelBuilder.Minimize(objVar);

    // Rjesavanje
    sat::Model model;

    // Postavi parametre za pretragu
    sat::SatParameters parameters;
    parameters.set_num_search_workers(4);
    parameters.set_cp_model_use_sat_presolve(true);


    // Postavi vremensko ogranicenje
    parameters.set_max_time_in_seconds(timeLimit);

    model.Add(NewSatParameters(parameters));


    // Rjesi.
    std::cout << std::endl << "SOLVING..." << std::endl;

    // Mjeri vrijeme
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::chrono::steady_clock::time_point end;

    numberOfConstraints = cpModelBuilder.Build().constraints().size();

    sat::CpSolverResponse response = SolveCpModel(cpModelBuilder.Build(), &model);

    if (minimizeResponseTimes)
    {

        std::cout << "Solved, MINIMIZING RESPONSE TIMES!" << std::endl;
        // Dodaj ogranicenje da raspored ostane optimalan iz perspektive inter-core kasnjenja
        cpModelBuilder.AddEquality(objVar, response.objective_value());

        // Kreiraj novu funkciju cilja
        const Domain objVarResponseDomain(0, 1000000000000);
        const sat::IntVar  objVarResponse = cpModelBuilder.NewIntVar(objVarResponseDomain);
        cpModelBuilder.AddEquality(objVarResponse, sat::LinearExpr::Sum(responseTimeDecisionVariables));

        cpModelBuilder.Minimize(objVarResponse);

        // Rjesavanje.
        sat::Model model2;


        // Postavi parametre pretrage.
        sat::SatParameters parameters;
        parameters.set_num_search_workers(4);
        parameters.set_cp_model_use_sat_presolve(true);

        // Postavi vremensko ogranicenje
        parameters.set_max_time_in_seconds(timeLimit);

        model2.Add(NewSatParameters(parameters));

        response = SolveCpModel(cpModelBuilder.Build(), &model2);
    }

    LOG(INFO) << sat::CpSolverResponseStats(response);

    // mjeri vrijeme
    end = std::chrono::steady_clock::now();

    // Postavi polje status (validni, optimalni ili nije pronadjeno rjesenje)
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

        for (int core = 0; core < numberOfCores; core++)
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


    return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

}
