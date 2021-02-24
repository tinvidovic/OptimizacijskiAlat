/*
* Klasa koja opisuje jedan lanac zadataka u ugradbenoj aplikaciji
* Jedan lanac zadataka je opisan sa nekoliko atributa i to:
* vektorom zadataka koji se nalaze u lancu
* hiperperiodom lanca zadataka koji se racuna kao NZS od perioda svih zadataka koji se nalaze u lancu zadataka
*/

#include "Task.h"
#include "Helper.h"
#include "Constants.h"
#include <iostream>
#include <vector>


#pragma once
class TaskChain
{
private:
	std::vector<Task> tasks; // Vektor zadataka koji se nalaze u lancu
	long long int hyperperiod; // Hiperperiod lanca zadataka

	// Privatna metoda koja postavlja vrijednost atributa hyperperiod na zeljenu vrijednost (poziva se samo iz klase TaskChain)
	void setHyperperiod(long long int t_hyperperiod);

	// Pomocna metoda koja se koristi za izracunavanje hiperperioda
	long long int calculateHyperperiod();

public:

	// Konstruktor
	TaskChain();

	// Getteri
	std::vector<Task> getTasks();

	long long int getHyperperiod();

	// Metode

	// Metoda kojom se proslijeđeni vektor zadataka dodaje u niz taskova
	void addTasks(std::vector<Task> t_tasks);

	// Metoda kojom se proslijeđeni zadatak dodaje u niz taskova
	void addTask(Task t_task);


	// Metoda koja vraca true ako se proslijeđeni task nalazi u datom lancu zadataka
	bool isInChain(Task * t_task);

	// Metoda koja vraca true ako se proslijeđeni task nalazi u datom lancu zadataka
	bool isInChain(int taskID);

	// Operatori

	// Operator << za željeni ispisni stream
	friend std::ostream& operator<<(std::ostream& out, const TaskChain& taskChain);

};