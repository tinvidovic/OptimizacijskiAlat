#include "TaskInstance.h"
#include "Task.h"


// Konstruktor

TaskInstance::TaskInstance(Task t_task, long long int t_number_of_instance)
{
	setTask(t_task);

	setNumberOfInstance(t_number_of_instance);

	setAbsoluteReleaseTime((t_number_of_instance - 1) * task.getPeriod());

	setAbsoluteDeadline(t_number_of_instance * task.getPeriod());

	setName();

	return;
}


// Setteri


void TaskInstance::setTask(Task t_task)
{
	task = t_task;

	return;
}


void TaskInstance::setAbsoluteReleaseTime(long long int t_absolute_release_time)
{
	if (t_absolute_release_time != (this->getNumberOfInstance() - 1) * this->getTask().getPeriod()) throw std::invalid_argument("Neispravno absolutno vrijeme oslobadjanja!");

	absolute_release_time = t_absolute_release_time;

	return;
}

void TaskInstance::setAbsoluteDeadline(long long int t_absolute_deadline)
{

	if (t_absolute_deadline != this->getNumberOfInstance() * this->getTask().getPeriod()) throw std::invalid_argument("Neispravan absolutni rok za izvr�enje instance!");

	absolute_deadline = t_absolute_deadline;

	return;
}

void TaskInstance::setNumberOfInstance(long long int t_number_of_instance)
{

	if (t_number_of_instance < 0) throw std::invalid_argument("Broj instance ne moze biti negativan!");
	number_of_instance = t_number_of_instance;

	return;
}

void TaskInstance::setName()
{
	name = task.getName() + "_" + std::to_string(this->getNumberOfInstance());

	return;
}

void TaskInstance::setStartOfRead(long long int t_start_of_read)
{
	//TODO: fix boundaries
	if (t_start_of_read < this->getAbsoluteReleaseTime() || t_start_of_read > this->getAbsoluteDeadline()) throw std::invalid_argument("Neispravan pocetak faze citanja!");

	start_of_read = t_start_of_read;

	return;
}

void TaskInstance::setEndOfRead(long long int t_end_of_read)
{
	if (t_end_of_read < this->getAbsoluteReleaseTime() || t_end_of_read > this->getAbsoluteDeadline()) throw std::invalid_argument("Neispravan kraj faze citanja!");

	end_of_read = t_end_of_read;

	return;
}

void TaskInstance::setStartOfExecute(long long int t_start_of_execute)
{
	if (t_start_of_execute < this->getAbsoluteReleaseTime() || t_start_of_execute > this->getAbsoluteDeadline()) throw std::invalid_argument("Neispravan pocetak faze egzekucije!");

	start_of_execute = t_start_of_execute;

	return;
}

void TaskInstance::setEndOfExecute(long long int t_end_of_execute)
{
	if (t_end_of_execute < this->getAbsoluteReleaseTime() || t_end_of_execute > this->getAbsoluteDeadline()) throw std::invalid_argument("Neispravan kraj faze egzekucije!");

	end_of_execute = t_end_of_execute;

	return;
}

void TaskInstance::setStartOfWrite(long long int t_start_of_write)
{
	if (t_start_of_write < this->getAbsoluteReleaseTime() || t_start_of_write > this->getAbsoluteDeadline()) throw std::invalid_argument("Neispravan pocetak faze pisanja!");

	start_of_write = t_start_of_write;

	return;
}

void TaskInstance::setEndOfWrite(long long int t_end_of_write)
{
	if (t_end_of_write < this->getAbsoluteReleaseTime() || t_end_of_write > this->getAbsoluteDeadline()) throw std::invalid_argument("Neispravan kraj faze pisanja!");

	end_of_write = t_end_of_write;

	return;
}

// Getteri

Task TaskInstance::getTask() const { return task; }

long long int TaskInstance::getAbsoluteReleaseTime() const { return absolute_release_time; }

long long int TaskInstance::getAbsoluteDeadline() const { return absolute_deadline; }

long long int TaskInstance::getNumberOfInstance() const { return number_of_instance; }

string TaskInstance::getName() const { return name; }

long long int TaskInstance::getStartOfRead() const
{
	return start_of_read;
}

long long int TaskInstance::getEndOfRead() const
{
	return end_of_read;
}

long long int TaskInstance::getStartOfExecute() const
{
	return start_of_execute;
}

long long int TaskInstance::getEndOfExecute() const
{
	return end_of_execute;
}

long long int TaskInstance::getStartOfWrite() const
{
	return start_of_write;
}

long long int TaskInstance::getEndOfWrite() const
{
	return end_of_write;
}

// Operatori

// Operator << za �eljeni ispisni stream
std::ostream& operator<<(std::ostream& out, const TaskInstance& task_instance)
{
	out << task_instance.getName() << "Read ( " << task_instance.getStartOfRead() << ", " << task_instance.getEndOfRead() << ")" << " Execute ( " << task_instance.getStartOfExecute() << ", "
		<< task_instance.getEndOfExecute() << ")" << " Write( " << task_instance.getStartOfWrite() << ", " << task_instance.getEndOfWrite() << ")" << std::endl;

	return out;
}