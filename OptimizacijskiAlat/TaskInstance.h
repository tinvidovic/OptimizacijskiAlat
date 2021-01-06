/*
* Klasa koja opisuje jednu instancu zadatka u ugradbenoj aplikaciji
* Jedna instanca je opisana sa nekoliko atributa i to:
* Tip zadatka kojem instanca pripada
* absolutno vrijeme oslobađanja instance
* absolutni rok za izvršavanje instance
* broj instance (u jednom hiperperiodu)
* ime instance
* pocetak izvrsavanja svih faza instance u kreiranom rasporedu
* kraj izvrsavanja svih faza instance u kreiranom rasporedu
*/

#include "Task.h"

#include <string>
#include <iostream>

using std::string;

#pragma once
class TaskInstance
{
private:
	Task* task; // Tip zadatka kojem instanca pripada
	long long int absolute_release_time; // Absolutno vrijeme oslobađanja instance
	long long int absolute_deadline; // Absolutni rok za izvršavanje instance
	long long int number_of_instance; // Broj instance (u jednom hiperperiodu)
	string name; // Ime instance
	long long int start_of_read = -1; // Pocetak izvrsavanja faze citanja instance u kreiranom rasporedu, postavljeno na -1 do kreiranja rasporeda
	long long int end_of_read = -1; // Kraj izvrsavanja faze citanja instance u kreiranom rasporedu, postavljeno na -1 do kreiranja rasporeda
	long long int start_of_execute = -1; // Pocetak izvrsavanja faze egzekucije instance u kreiranom rasporedu, postavljeno na -1 do kreiranja rasporeda
	long long int end_of_execute = -1; // Kraj izvrsavanja faze egzekucije instance u kreiranom rasporedu, postavljeno na -1 do kreiranja rasporeda
	long long int start_of_write = -1; // Pocetak izvrsavanja faze pisanja instance u kreiranom rasporedu, postavljeno na -1 do kreiranja rasporeda
	long long int end_of_write = -1; // Kraj izvrsavanja faze pisanja instance u kreiranom rasporedu, postavljeno na -1 do kreiranja rasporeda

public:

	// Konstruktor

	TaskInstance(Task* t_task, long long int t_number_of_instance);


	// Setteri

	void setTask(Task* t_task);

	void setAbsoluteReleaseTime(long long int t_absolute_release_time);

	void setAbsoluteDeadline(long long int t_absolute_deadline);

	void setNumberOfInstance(long long int t_number_of_instance);

	void setName();

	void setStartOfRead(long long int t_start_of_read);

	void setEndOfRead(long long int t_end_of_read);

	void setStartOfExecute(long long int t_start_of_execute);

	void setEndOfExecute(long long int t_end_of_execute);

	void setStartOfWrite(long long int t_start_of_write);

	void setEndOfWrite(long long int t_end_of_write);


	// Getteri

	Task* getTask() const;

	long long int getAbsoluteReleaseTime() const;

	long long int getAbsoluteDeadline() const;

	long long int getNumberOfInstance() const;

	string getName() const;

	long long int getStartOfRead() const;

	long long int getEndOfRead() const;

	long long int getStartOfExecute() const;

	long long int getEndOfExecute() const;

	long long int getStartOfWrite() const;

	long long int getEndOfWrite() const;


	// Operatori

	friend std::ostream& operator<<(std::ostream& out, const TaskInstance& task_instance);
};
