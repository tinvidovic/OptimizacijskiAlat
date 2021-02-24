/*
* Klasa koja opisuje jedan set zadataka u ugradbenoj aplikaciji
* Jedan set zadataka je opisan sa nekoliko atributa i to:
* vektorom zadataka koji se nalaze u datom setu zadataka
* brojem jezgre na kojoj se set zadataka treba izvrsavati
* hiperperiod seta zadataka, koji se racuna NZS perioda zadataka koji pripadaju datom setu zadaataka
* vektorom svih instanci, cije absolutno vrijeme oslobadjanja pripada [0, HP]
* period zadatka
* relativni rok za izvršenje zadatka (kako se razmatraju samo periodični zadaci, smatra se da je relativni rok zadatka jednak njegovom periodu)
*/

#include <vector>
#include "Task.h"
#include "TaskInstance.h"
#include "Helper.h"
#include "Constants.h"
#include "iostream"

#pragma once
class TaskSet
{
private:
	std::vector<Task> tasks; // Vektor zadataka koji se nalaze u datom setu zadataka
	long long int core; // Broj jezgre na kojoj se set zadataka treba izvrsavati
	long long int hyperperiod; // Hiperperiod seta zadataka
	std::vector<TaskInstance> instances; // Vektor svih instanci, cije absolutno vrijeme oslobadjanja pripada[0, HP]


public:

	//Konstruktor

	TaskSet(long long int t_core);

	// Setteri

	void setCore(long long int t_core);
	void setHyperperiod(long long int t_hyperperiod);
	void setInstances();


	// Getteri
	std::vector<Task> getTasks();
	long long int getCore();
	long long int getHyperperiod();
	std::vector<TaskInstance> getInstances();
	Task getTaskById(int id);

	// Metode

	// Metoda koja dodaje jedan zadatak u set zadataka
	void addTask(Task * t_task);

	// Metoda koja dodaje vise zadataka u set zadataka
	void addTasks(std::vector<Task> t_tasks);

	// Metoda koja racuna vriejdnost hiperperioda seta zadataka, na osnovu zadataka koji mu pripadaju
	long long int calculateHyperperiod();

	// Operatori

	// Operator << za željeni ispisni stream
	friend std::ostream& operator<<(std::ostream& out, const TaskSet& taskSet);

};

long long int getTotalHyperperiod(std::vector<TaskSet>& taskSets);

bool isInSet(Task t_task, TaskSet& taskSet);