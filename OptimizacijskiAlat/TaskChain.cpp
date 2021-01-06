#include "TaskChain.h"

// Konstruktor
TaskChain::TaskChain()
{
	tasks.clear();
	hyperperiod = HYPERPERIOD_OF_EMPTY_TASK_CHAIN;
}


void TaskChain::setHyperperiod(long long int t_hyperperiod) { hyperperiod = t_hyperperiod; }

long long int TaskChain::calculateHyperperiod()
{
	if (tasks.size() == 1) return tasks.at(0)->getPeriod(); // Ako je samo jedan zadatak u lancu

	std::vector<unsigned long long int> periods; // vector koji sadrži periode svih zadataka u lancu (bez duplikata)

	for (unsigned long long int i = 0; i < tasks.size(); i++)
	{
		unsigned long long int period = tasks.at(i)->getPeriod();
		bool isNewPeriodValue = true;

		for (unsigned long long int j = 0; j < periods.size(); j++)
		{
			//Ukloni duple periode radi brzeg racunanja
			if (periods.at(j) == period) isNewPeriodValue = false;
		}
		// Ukoliko je nova vrijednost dodaj je
		if (isNewPeriodValue) periods.push_back(period);
	}

	// Pronadji i vrati NZS za sve periode
	return findLeastCommonMultiple(periods);
}

// Getteri
std::vector<Task*> TaskChain::getTasks() { return tasks; }

long long int TaskChain::getHyperperiod() { return hyperperiod; }


// Metode

void TaskChain::addTasks(std::vector<Task*> t_tasks)
{
	for (unsigned int i = 0; i < t_tasks.size(); i++)
	{
		tasks.push_back(t_tasks.at(i));
	}

	setHyperperiod(calculateHyperperiod()); // Nakon svakog novog dodavanja zadatka ponovo izracunaj i postavi hiperperiod
}

void TaskChain::addTask(Task* t_task)
{
	tasks.push_back(t_task);
	setHyperperiod(calculateHyperperiod()); // Nakon svakog novog dodavanja zadatka ponovo izracunaj i postavi hiperperiod
}

bool TaskChain::isInChain(long long int taskID)
{

	for (long long int task = 0; task < this->getTasks().size(); task++)
	{
		if (tasks.at(task)->getId() == taskID)
		{
			return true;
		}
	}

	return false;
}

std::ostream& operator<<(std::ostream& out, const TaskChain& taskChain)
{
	out << "Task Chain: " << std::endl;

	for (long long int task = 0; task < taskChain.tasks.size() - 1; task++)
	{
		out << (*taskChain.tasks.at(task)) << "\t|" << std::endl << "\tV" << std::endl;
	}

	return out << (*taskChain.tasks.at(taskChain.tasks.size() - 1)) << std::endl;

}