/*
* Klasa koja opisuje jedan zadatak u ugradbenoj aplikaciji
* Jedan zadatak je opisan sa nekoliko atributa i to:
* ID zadatka
* ime zadatka
* najgore vrijeme za izvršenje faza čitanja, egzekucije i pisanja za zadatak
* najgore ukupno vrijeme izvršavanja zadatka
* period zadatka
* relativni rok za izvršenje zadatka (kako se razmatraju samo periodični zadaci, smatra se da je relativni rok zadatka jednak njegovom periodu)
*/

#include <vector>
#include <iostream>
#include <string>

using std::string;

static int max_id = 1;

#pragma once
class Task
{
private:
	int id; // ID zadatka
	string name; // Ime zadatka
	long long int worst_case_read = 0; // Najgore vrijeme za izvršenje faze čitanja zadatka
	long long int worst_case_execute = 0; // Najgore vrijeme za izvršenje faze egzekucije zadatka
	long long int worst_case_write = 0; // Najgore vrijeme za izvršenje faze pisanja zadatka
	long long int period; // Period zadatka
	long long int deadline; // Relativni rok za izvršenje zadatka (period == deadline)


public:

	//Konstruktori

	Task(long long int t_worst_case_read, long long int t_worst_case_execute, long long int t_worst_case_write, long long int t_period);


	// Setteri

	void setId(int t_id);

	void setName();

	void setWorstCaseRead(long long int t_worst_case_read);

	void setWorstCaseExecute(long long int t_worst_case_execute);

	void setWorstCaseWrite(long long int worst_case_write);

	void setPeriod(long long int t_period);

	void setDeadline(long long int t_deadline);

	// Getteri

	long long int getId() const;

	string getName() const;

	long long int getWorstCaseRead() const;

	long long int getWorstCaseExecute() const;

	long long int getWorstCaseWrite() const;

	long long int getPeriod() const;

	long long int getDeadline() const;


	// Metode

	// Metoda koja vraća najgore ukupno vrijeme izvršavanja zadatka
	long long int getWorstCaseExecutionTime() const;

	// Operatori

	// Operator << za željeni ispisni stream
	friend std::ostream& operator<<(std::ostream& out, const Task& task);


};
