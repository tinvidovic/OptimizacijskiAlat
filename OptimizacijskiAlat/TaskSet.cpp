#include "TaskSet.h"

//Konstruktor

TaskSet::TaskSet(long long int t_core)
{
	setCore(t_core);

	setHyperperiod(HYPERPERIOD_OF_EMPTY_TASK_SET);
}

// Setteri

void TaskSet::setCore(long long int t_core)
{
	core = t_core;
	return;
}

void TaskSet::setHyperperiod(long long int t_hyperperiod)
{
	hyperperiod = t_hyperperiod;
}

void TaskSet::setInstances()
{

	instances.clear();

	for (long long int i = 0; i < tasks.size(); i++)
	{

		for (long long int j = 1; j <= this->getHyperperiod() / tasks.at(i).getPeriod(); j++)
		{
			//Kreiraj pokazivac na instancu

			TaskInstance taskInstance(tasks.at(i), j);

			// Dodaj ga u vektor instanci
			instances.push_back(taskInstance);
		}
	}
}

// Getteri

std::vector<Task> TaskSet::getTasks() { return tasks; };

long long int TaskSet::getCore() { return core; }

long long int TaskSet::getHyperperiod() { return hyperperiod; }

std::vector<TaskInstance> TaskSet::getInstances()
{
	return instances;
}

Task TaskSet::getTaskById(int id)
{
	for (int i = 0; i < tasks.size(); i++)
	{
		if (tasks.at(i).getId() == id) return tasks.at(i);
	}

	return Task(0, 0, 0, 0);
}

// Metode

void TaskSet::addTask(Task * t_task)
{


	if (!isInSet(*t_task, *this))
	{
		t_task->setCore(this->getCore());
		tasks.push_back(*t_task);
		

	}


	setHyperperiod(calculateHyperperiod()); // Nakon svakog novog dodavanja zadatka ponovo izracunaj i postavi hiperperiod
	setInstances();
}

void TaskSet::addTasks(std::vector<Task> t_tasks)
{

	//Dodaj zadatke
	for (long long int i = 0; i < t_tasks.size(); i++)
	{

		if (!isInSet(t_tasks.at(i), *this))
		{
			t_tasks.at(i).setCore(this->getCore());
			tasks.push_back(t_tasks.at(i));
			
		}
	}

	setHyperperiod(calculateHyperperiod()); // Nakon svakog novog dodavanja zadatka ponovo izracunaj i postavi hiperperiod
	setInstances();
}

// TODO: Izdvoji u jednu funkciju koja radi i sa lancima i sa setovima
long long int TaskSet::calculateHyperperiod()
{

	if (tasks.size() == 1) return tasks.at(0).getPeriod(); // Ako je samo jedan zadatak u setu

	std::vector<unsigned long long int> periods; // Vektor koji sadr�i periode svih zadataka u lancu (bez duplikata)

	for (long long int i = 0; i < tasks.size(); i++)
	{
		long long int period = tasks.at(i).getPeriod();
		bool isNewPeriodValue = true;

		for (long long int j = 0; j < periods.size(); j++)
		{
			// Ukloni duple periode radi brzeg racunanja
			if (periods.at(j) == period) isNewPeriodValue = false;
		}

		if (isNewPeriodValue || true) periods.push_back(period);
	}
	return findLeastCommonMultiple(periods);

}


std::ostream& operator<<(std::ostream& out, const TaskSet& taskSet)
{
	// Ispisi zadatke
	out << "Tasks: " << std::endl;
	for (int i = 0; i < taskSet.tasks.size(); i++)
	{
		out << (taskSet.tasks.at(i)) << std::endl;
	}

	// Ispisi hiperperiod
	out << "Hyperperiod: " << taskSet.hyperperiod;

	out << std::endl;

	// Ispisi jezgru
	out << "Core: " << taskSet.core;

	out << std::endl;

	// Ispisi instance unutar hiperperioda
	out << "Instances: " << std::endl;
	for (int i = 0; i < taskSet.instances.size(); i++)
	{


		// Kada predjemo na slijedeci zadatak ispisi novi red
		if (i > 0)
		{
			if (taskSet.instances.at(i - 1).getTask().getId() != taskSet.instances.at(i).getTask().getId())
			{
				out << std::endl;
			}
		}

		out << (taskSet.instances.at(i)) << std::endl;

	}

	return out;
}

long long int getTotalHyperperiod(std::vector<TaskSet>& taskSets)
{
	std::vector<unsigned long long int> hyperperiods;
	for (int i = 0; i < taskSets.size(); i++)
	{
		if (taskSets.at(i).getHyperperiod() != 0) hyperperiods.push_back(taskSets.at(i).getHyperperiod());
	}

	return findLeastCommonMultiple(hyperperiods);
}

bool isInSet(Task t_task, TaskSet& taskSet)
{
	if (t_task.getCore() == taskSet.getCore()) return true;

	return false;
}
