// Implemenatacija klase Task

#include "Task.h"

// Konstruktor

Task::Task(long long int t_worst_case_read, long long int t_worst_case_execute, long long int t_worst_case_write, long long int t_period)
{
	// postavi atribute koristeći settere sa provjerom argumenata

	setId(max_id);

	setName();

	setPeriod(t_period);

	setDeadline(t_period);

	setWorstCaseRead(t_worst_case_read);

	setWorstCaseExecute(t_worst_case_execute);

	setWorstCaseWrite(t_worst_case_write);

	return;
}

// Setteri

void Task::setId(int t_id)
{
	id = t_id;

	// povecaj maksimalni id za slijedeci zadatak

	max_id++;

	return;
}

void Task::setName()
{
	name = "Tau_" + std::to_string(this->getId());

	return;
}

void Task::setWorstCaseRead(long long int t_worst_case_read)
{
	if ( t_worst_case_read < 0 ) throw std::invalid_argument("Najgore vrijeme za izvrsenje faze citanja zadatka mora biti > 0!");

	worst_case_read = t_worst_case_read;

	// da li je zadatak izvršiv u relativnom roku za izvršavanje?
	if (this->getWorstCaseExecutionTime() > this->getDeadline()) throw std::invalid_argument("Zadatak " + this->getName() + " nije izvrsiv u zadanom relativnom roku");

	return;
}

void Task::setWorstCaseExecute(long long int t_worst_case_execute)
{
	if ( t_worst_case_execute < 0 ) throw std::invalid_argument("Najgore vrijeme za izvrsenje faze egzekucije zadatka mora biti > 0!");

	worst_case_execute = t_worst_case_execute;

	// da li je zadatak izvršiv u relativnom roku za izvršavanje?
	if (this->getWorstCaseExecutionTime() > this->getDeadline()) throw std::invalid_argument("Zadatak " + this->getName() + " nije izvrsiv u zadanom relativnom roku");

	return;
}

void Task::setWorstCaseWrite(long long int t_worst_case_write)
{

	if ( t_worst_case_write < 0 ) throw std::invalid_argument("Najgore vrijeme za izvrsenje faze pisanja zadatka mora biti > 0!");

	worst_case_write = t_worst_case_write;

	// da li je zadatak izvršiv u relativnom roku za izvršavanje?

	if (this->getWorstCaseExecutionTime() > this->getDeadline()) throw std::invalid_argument("Zadatak " + this->getName() + " nije izvrsiv u zadanom relativnom roku");

	return;
}

void Task::setPeriod(long long int t_period)
{

	if ( t_period <= 0 ) throw std::invalid_argument("Period zadatka mora biti > 0!");

	period = t_period;

	return;
}

void Task::setDeadline(long long int t_deadline)
{

	if ( t_deadline != period ) throw std::invalid_argument("Relativni rok za izvrsenje zadatka mora biti jednak periodu zadatka!");

	deadline = t_deadline;

	return;
}

// Getteri

long long int Task::getId() const { return id; }

string Task::getName() const { return name; }

long long int Task::getWorstCaseRead() const { return worst_case_read; }

long long int Task::getWorstCaseExecute() const { return worst_case_execute; }

long long int Task::getWorstCaseWrite() const { return worst_case_write; }

long long int Task::getPeriod() const { return period; }

long long int Task::getDeadline() const { return deadline; }

// Metode

long long int Task::getWorstCaseExecutionTime() const
{
	// WCET je zbir najgorih vremena za izvršavanje svake od faza
	return getWorstCaseRead() + getWorstCaseExecute() + getWorstCaseWrite();
}


// OPERATORS
std::ostream& operator<<(std::ostream& out, const Task& task)
{
	out << task.getName().c_str() << ", WC Read: " << task.getWorstCaseRead() << ", WC Execute: " << task.getWorstCaseExecute() << ", WC Write: " << task.getWorstCaseWrite() << ", Period: " 
		<< task.getPeriod()  << ", Utilization: " << (double)(task.getWorstCaseExecutionTime()) / task.getPeriod() << std::endl;

	return out;
}