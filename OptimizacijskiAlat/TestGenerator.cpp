#include "TestGenerator.h"

bool chainsValid(std::vector<TaskChain> taskChains)
{
	int chainIndex = 0;
	int taskIndex = 0;

	for (int i = 0; i < taskChains.size(); i++)
	{
		chainIndex = i;
		for (int j = 0; j < taskChains.at(i).getTasks().size(); j++)
		{
			taskIndex = j;
			int taskId = taskChains.at(i).getTasks().at(taskIndex).getId();
			std::set<int> taskPredecessors;
			std::set<int> taskSuccessors;

			for (int k = 0; k < taskChains.size(); k++)
			{
				for (int l = 0; l < taskChains.at(k).getTasks().size(); l++)
				{
					if (taskChains.at(k).getTasks().at(l).getId() == taskId)
					{
						//dodaj sve proizvodjace u skup
						for (int predecessors = 0; predecessors < l; predecessors++)
						{
							taskPredecessors.insert(taskChains.at(k).getTasks().at(predecessors).getId());
						}
						//dodaj sve potrosace u skup
						for (int successors = l + 1; successors < taskChains.at(k).getTasks().size(); successors++)
						{
							taskSuccessors.insert(taskChains.at(k).getTasks().at(successors).getId());
						}
					}
				}
			}

			// ako skup poroizvodjaca i potrosaca ima zajednickih elemanata, vrati false
			if (setsIntersect(taskPredecessors, taskSuccessors))
			{
				return false;
			}
		}
	}
	return true;
}


bool correctAmountOfCommunicatingInstances(std::vector<TaskSet> taskSets, std::vector<TaskChain> taskChains, int n)
{

	if (n < 0) return true;


	int numberOfInstances = 0;

	std::vector<std::vector<TaskInstance>> instancesOnCore;


	// Treba razmatrati zajednicki hiperperiod
	long long int hyperPeriod = getTotalHyperperiod(taskSets);

	for (int i = 0; i < taskSets.size(); i++)
	{
		instancesOnCore.push_back(std::vector<TaskInstance>());
		instancesOnCore.at(i) = taskSets.at(i).getInstances();
	}

	// Loop through all the chains

	for (int chain = 0; chain < taskChains.size(); chain++)
	{
		// loop through all of the consumers in the chain
		for (int consumerIndex = 1; consumerIndex < taskChains.at(chain).getTasks().size(); consumerIndex++)
		{
			long long int consumerTaskId = taskChains.at(chain).getTasks().at(consumerIndex).getId();
			long long int consumerCoreAssignedTo = taskChains.at(chain).getTasks().at(consumerIndex).getCore();

			long long int producerIndex = consumerIndex - 1;
			long long int producerTaskId = taskChains.at(chain).getTasks().at(producerIndex).getId();
			long long int producerCoreAssignedTo = taskChains.at(chain).getTasks().at(producerIndex).getCore();

			//loop through all instances on consumers core
			for (int consumerInstanceIndex = 0; consumerInstanceIndex < instancesOnCore.at(consumerCoreAssignedTo).size(); consumerInstanceIndex++)
			{
				bool firstTime = true;
				TaskInstance currentConsumerInstance = instancesOnCore.at(consumerCoreAssignedTo).at(consumerInstanceIndex);

				// if it is an instance of the correct consumer
				if (currentConsumerInstance.getTask().getId() == consumerTaskId)
				{
					//loop through all instances on producers core
					for (int producerInstanceIndex = 0; producerInstanceIndex < instancesOnCore.at(producerCoreAssignedTo).size(); producerInstanceIndex++)
					{
						TaskInstance currentProducerInstance = instancesOnCore.at(producerCoreAssignedTo).at(producerInstanceIndex);

						// if it is an instance of the correct producer

						if (currentProducerInstance.getTask().getId() == producerTaskId)
						{
							//if the two instances can communicate increase count
							if (canCommunicate(currentConsumerInstance, currentProducerInstance) && producerCoreAssignedTo != consumerCoreAssignedTo)
							{
								numberOfInstances++;
							}

							if (intervalsOverlap(0, currentProducerInstance.getTask().getPeriod() - currentProducerInstance.getTask().getWorstCaseExecutionTime(), currentConsumerInstance.getAbsoluteReleaseTime() + currentConsumerInstance.getTask().getWorstCaseExecutionTime(), currentConsumerInstance.getAbsoluteDeadline()) && producerCoreAssignedTo != consumerCoreAssignedTo && firstTime)
							{
								firstTime = false;

								numberOfInstances++;

							}
						}
					}

				}
			}

		}
	}

	//std::cout << "Target Communicating Instances: " << n << " Generated communicating instances: " << numberOfInstances << std::endl;

	return numberOfInstances == n;
}


void generateTestCase(std::vector<TaskSet>& taskSets, std::vector<TaskChain>& taskChains, int numberOfTasks, int numberOfChains, std::vector<double> coreUtilizations, int numberOfCommunicatingProducerConsumerInstances)
{

	std::vector<Task> tasks;

	std::cout << "Generating a test case with " << numberOfTasks << " tasks and " << numberOfChains << " chains, with the following core utilizations: ";

	for (int core = 0; core < coreUtilizations.size(); core++)
	{
		std::cout << "Core " << core << " " << coreUtilizations.at(core) << "% ";
	}

	std::cout << std::endl;

	// Reset taskId counter
	max_id = 1;

	do
	{
		// Reset taskId counter
		max_id = 1;


		int numberOfTasksInChains;

		// Vektor koji cuva broj zadataka po aktivacijskom uzorku za svaki od lanaca
		std::vector<std::vector<int>> numberOfTasksPerActivationPatternPerChain;

		// Vektor koji cuva periode aktivacijskih uzoraka za svaki lanac
		std::vector<std::vector<int>> periodsOfTasksPerActivationPatternPerChain;


		// Vektor koji cuva periode svih zadataka (nezavisni + zadaci u lancima)
		std::vector<int> periodsOfTasks;

		do
		{

			// Reset taskId counter
			max_id = 1;

			taskSets.clear();
			numberOfTasksPerActivationPatternPerChain.clear();
			periodsOfTasksPerActivationPatternPerChain.clear();
			periodsOfTasks.clear();

			for (int chain = 0; chain < numberOfChains; chain++)
			{

				// Odaberi aktivacijski uzorak
				int indexOfActivationPattern = roulleteWheelSelecetion(activationPatternsProbabilities);

				std::vector<int> numbersOfTasksForCurrentChain;
				numberOfTasksPerActivationPatternPerChain.push_back(numbersOfTasksForCurrentChain);

				std::vector<int> periodsOfTasksForCurrentChain;
				periodsOfTasksPerActivationPatternPerChain.push_back(periodsOfTasksForCurrentChain);

				// Za svaki od aktivacijskih uzoraka generisi random broj zadataka koristeci distribucije vjerovatnoce
				for (int activationPattern = 0; activationPattern < activationPatterns[indexOfActivationPattern]; activationPattern++)
				{

					numberOfTasksPerActivationPatternPerChain.at(chain).push_back(numberOfTasksPerActivationPattern.at(roulleteWheelSelecetion(numberOfTasksPerActivationPatternProbabilites)));

					// Prvi aktivacijski uzorak moze biti bilo koji
					// svi ostali moraju postovati matricu dozvoljenih komunikacija

					if (activationPatterns[indexOfActivationPattern] == 1 || activationPattern == 0)
					{
						periodsOfTasksPerActivationPatternPerChain.at(chain).push_back(tasksPeriods.at(roulleteWheelSelecetion(tasksPeriodsProbabilities)));
					}

					else
					{
						// Period proizvodjaca
						int periodOfProducingActivationPattern = periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern - 1);

						// Nadji index perioda proizvodjaca
						int indexOfPeriodOfProducingActivationPattern = findIndex(tasksPeriods, periodOfProducingActivationPattern);

						int periodOfConsumingActivationPatternPeriod;

						int indexOfPeriodOfConsumingActivationPattern;

						// Generisi periode za potrosaca dok se ne dobije dozvoljena vrijednost
						do
						{
							// Reset taskId counter
							max_id = 1;

							periodOfConsumingActivationPatternPeriod = tasksPeriods.at(roulleteWheelSelecetion(tasksPeriodsProbabilities));

							indexOfPeriodOfConsumingActivationPattern = findIndex(tasksPeriods, periodOfConsumingActivationPatternPeriod);

						} while (isPeriodOfConsumingActivationPatternAllowed[indexOfPeriodOfProducingActivationPattern][indexOfPeriodOfConsumingActivationPattern] == false);

						periodsOfTasksPerActivationPatternPerChain.at(chain).push_back(tasksPeriods.at(indexOfPeriodOfConsumingActivationPattern));
					}
				}
			}

			for (int chain = 0; chain < numberOfChains; chain++)
			{
				for (int activationPattern = 0; activationPattern < numberOfTasksPerActivationPatternPerChain.at(chain).size(); activationPattern++)
				{
					for (int task = 0; task < numberOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern); task++)
					{
						periodsOfTasks.push_back(periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern));
					}
				}
			}

			numberOfTasksInChains = 0;

			// Izracunaj ukupni broj zadataka u lancima
			for (int chain = 0; chain < numberOfChains; chain++)
			{
				for (int activationPattern = 0; activationPattern < numberOfTasksPerActivationPatternPerChain.at(chain).size(); activationPattern++)
				{
					numberOfTasksInChains += numberOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern);
				}
			}

		} while (numberOfTasksInChains > numberOfTasks); // broj zadataka u lancima mora biti manji od ukupnog bbroja zadataka


		// Broj nezavisnih zadataka
		int numberOfIndependentTasks = numberOfTasks - numberOfTasksInChains;


		// Generisi periode za nezavisne zadatke

		for (int independentTask = 0; independentTask < numberOfIndependentTasks; independentTask++)
		{
			periodsOfTasks.push_back(tasksPeriods.at(roulleteWheelSelecetion(tasksPeriodsProbabilities)));
		}


		std::vector<int> allTasksIDs;

		for (int taskID = 0; taskID < numberOfTasks; taskID++)
		{
			allTasksIDs.push_back(taskID + 1);
		}

		// Promjesaj vektor ID-eva zadataka
		std::random_shuffle(allTasksIDs.begin(), allTasksIDs.end());


		// Generisi tacke razdvajanja za vektor zadataka
		std::uniform_int_distribution<> distributionForSplitUpOfTasks(1, numberOfTasks - 1);

		std::random_device rd;

		std::mt19937 gen(rd());

		std::vector<int> splitUpPoints;

		do
		{
			splitUpPoints.clear();
			for (int points = 0; points < coreUtilizations.size() - 1; points++)
			{
				splitUpPoints.push_back(distributionForSplitUpOfTasks(gen));
			}

		} while (!allDifferent(splitUpPoints));



		// Dodaj 0 i brojZadataka radi lakse manipulacije u ostatku algoritma
		splitUpPoints.push_back(0);
		splitUpPoints.push_back(numberOfTasks);

		std::sort(splitUpPoints.begin(), splitUpPoints.end());

		// Vektor koji cuva informacije o tome koji zadatak je dodijljen kojoj jezgri
		std::vector<int> coreAssignedTo;



		for (int taskID = 0; taskID < numberOfTasks; taskID++)
		{
			int core = 0;

			for (int point = 1; point < splitUpPoints.size() - 1; point++)
			{
				if (taskID >= splitUpPoints.at(point)) core = point;
			}

			coreAssignedTo.push_back(core);
		}



		// Sortiraj IDeve zadataka i coreAssignedTo zajedno sa njim

		for (int taskID = 0; taskID < allTasksIDs.size() - 1; taskID++)
		{
			for (int taskIDHelp = 0; taskIDHelp < allTasksIDs.size() - taskID - 1; taskIDHelp++)
			{
				if (allTasksIDs[taskIDHelp] > allTasksIDs[taskIDHelp + 1])
				{
					int tempID = allTasksIDs[taskIDHelp];
					int tempCore = coreAssignedTo[taskIDHelp];

					allTasksIDs[taskIDHelp] = allTasksIDs[taskIDHelp + 1];
					coreAssignedTo[taskIDHelp] = coreAssignedTo[taskIDHelp + 1];

					allTasksIDs[taskIDHelp + 1] = tempID;
					coreAssignedTo[taskIDHelp + 1] = tempCore;

				}
			}
		}



		// Generisi utilizacije za svaki zadatak svak e od jezgri i stavi ih u u odgovarajuci vektor

		std::vector<std::vector<std::vector<double>>> utilizationsForCores;

		for (int core = 0; core < coreUtilizations.size(); core++)
		{
			utilizationsForCores.push_back(generateTaskUtilization(double(splitUpPoints.at(core + 1) - splitUpPoints.at(core)), coreUtilizations.at(core)));
		}

		std::vector<double> utilizationsOfTasks(numberOfTasks, 0.0);

		std::vector<int> utilizationCounters(coreUtilizations.size(), 0);

		for (int task = 0; task < numberOfTasks; task++)
		{

			utilizationsOfTasks.at(task) = utilizationsForCores.at(coreAssignedTo.at(task)).at(0).at(utilizationCounters.at(coreAssignedTo.at(task)));

			utilizationCounters.at(coreAssignedTo.at(task))++;

		}



		// Izracunaj WCET za svaki od zadataka prema formuli WCET = T/U;

		std::vector<long long int> worstCaseExecutionTime;


		for (int task = 0; task < numberOfTasks; task++)
		{
			// Pretvori u pikosekunde
			worstCaseExecutionTime.push_back(1000000000 * (double)periodsOfTasks.at(task) * utilizationsOfTasks.at(task));
		}


		std::vector<long long int> worstCaseRead;

		for (int task = 0; task < numberOfTasks; task++)
		{
			// Pretvori u pikosekunde
			int generatedIndex = roulleteWheelSelecetion(labelSizesProbabilities);
			std::uniform_int_distribution<> labelDistribution(0, labelSizes.at(generatedIndex).size() - 1);

			int whichLabel = labelDistribution(gen);
			worstCaseRead.push_back(1000000000000 * READ_PERCENTAGE * (double)(labelSizes.at(generatedIndex).at(whichLabel)) / (double)(CLOCK_FREQUENCY * NUMBER_OF_BYTES_PER_ONE_CLOCK_CYCLE));
		}


		std::vector<long long int> worstCaseWrite;

		for (int task = 0; task < numberOfTasks; task++)
		{
			// Pretvori u pikosekunde
			int generatedIndex = roulleteWheelSelecetion(labelSizesProbabilities);
			std::uniform_int_distribution<> labelDistribution(0, labelSizes.at(generatedIndex).size() - 1);

			int whichLabel = labelDistribution(gen);
			worstCaseWrite.push_back(1000000000000 * WRITE_PERCENTAGE * (double)(labelSizes.at(generatedIndex).at(whichLabel)) / (double)(CLOCK_FREQUENCY * NUMBER_OF_BYTES_PER_ONE_CLOCK_CYCLE));
		}


		std::vector<long long int> worstCaseExecute;

		for (int task = 0; task < numberOfTasks; task++)
		{
			// worstCaseExecutionTime - worstCaseRead - worstCaseWrite
			if (worstCaseExecutionTime.at(task) - worstCaseRead.at(task) - worstCaseWrite.at(task) < 0)
			{
				worstCaseExecute.push_back(0);
			}
			else
			{
				worstCaseExecute.push_back(worstCaseExecutionTime.at(task) - worstCaseRead.at(task) - worstCaseWrite.at(task));
			}
		}


		// Kreiraj skupove zadataka

		for (int core = 0; core < coreUtilizations.size(); core++)
		{
			taskSets.push_back(TaskSet(core));
		}

		// Kreiraj zadatke i popuni skupove zadataka

		tasks.clear();

		for (int task = 0; task < numberOfTasks; task++)
		{
			Task newTask(worstCaseRead[task], worstCaseExecute[task], worstCaseWrite[task], (long long int) periodsOfTasks[task] * 1000000000);

			tasks.push_back(newTask);

			taskSets.at(coreAssignedTo.at(task)).addTask(&newTask);


		}

		// Fix task cores

		tasks.clear();

		for (int i = 0; i < taskSets.size(); i++)
		{
			for (int j = 0; j < taskSets.at(i).getTasks().size(); j++)
			{
				tasks.push_back(taskSets.at(i).getTasks().at(j));
			}
		}


		// Popuni lance zadataka
		do {


			taskChains.clear();

			for (int chain = 0; chain < numberOfChains; chain++)
			{
				TaskChain newChain;

				for (int activationPattern = 0; activationPattern < numberOfTasksPerActivationPatternPerChain.at(chain).size(); activationPattern++)
				{
					for (int taskNumber = 0; taskNumber < numberOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern); taskNumber++)
					{
						int randomTaskID = 0;

						do
						{



							std::uniform_int_distribution<> distribution(0, numberOfTasks - 1);

							randomTaskID = distribution(gen);

						} while (tasks.at(randomTaskID).getPeriod() != (long long int) periodsOfTasksPerActivationPatternPerChain.at(chain).at(activationPattern) * 1000000000 || newChain.isInChain(&tasks.at(randomTaskID)));

						newChain.addTask(tasks.at(randomTaskID));
					}
				}

				taskChains.push_back(newChain);
			}
		} while (!chainsValid(taskChains)); // provjeri da li su kreirani lanci zadataka neciklicni


	} while (!correctAmountOfCommunicatingInstances(taskSets, taskChains, numberOfCommunicatingProducerConsumerInstances)); // check if the number of instances and communicating instances is correct

	std::cout << "SUCCESS!" << std::endl << "Generated test case: ";

	for (int i = 0; i < taskSets.size(); i++)
	{
		std::cout << taskSets.at(i) << std::endl;
	}

	std::cout << "TASK CHAINS: " << std::endl;

	for (int i = 0; i < taskChains.size(); i++)
	{
		std::cout << taskChains.at(i) << std::endl;
	}


}