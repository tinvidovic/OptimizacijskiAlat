/*
A file containing all the helper functions used throught project
*/

#include <vector>
#include <set>
#include "TaskInstance.h"
#include "Task.h"
#include "iostream"
#include "math.h"
#include <algorithm>
#include<random>
#include <ctime>

#pragma once



unsigned long long int findGreatestCommonDivisor(unsigned long long int a, unsigned long long int b);

unsigned long long int findGreatestCommonDivisorOfVector(std::vector<unsigned long long int> inputs);

unsigned long long int findLeastCommonMultiple(std::vector<unsigned long long int> inputs);

// Funkcija koja odabire element iz vektora na principu roullete wheel algoritma
int roulleteWheelSelecetion(std::vector<double> probabilities);

/* Funkcija koa pronalazi index vrijednosti value u vektoru values, vraca -1 ukoliko se value ne nalazi u values */
int findIndex(std::vector<int> values, int value);

// Funkcija koja provjera da li su svi elementi u vektoru razliciti
bool allDifferent(std::vector<int> inputs);

// Pomocna funkcija za repliciranje matice
std::vector<std::vector<double> > repmat(std::vector<std::vector<double> > mat, int rows, int columns);

// Funkcija koja vraca n uniformno rasporedjenih brojava cija je suma jednaka u
std::vector<std::vector<double>> generateTaskUtilization(double n, double u);

// Funkcija koja provjerava da li se dva skupa presjecaju
bool setsIntersect(std::set<int> a, std::set<int> b);

// Funkcija koja vraca true ako se intervali [a1, a2] i [b1, b2] presjecaju
bool intervalsOverlap(long long int a1, long long int a2, long long int b1, long long int b2);

// Funkcija koja vraca true ako producer i consumer mogu komunicirati
bool canCommunicate(TaskInstance& producer, TaskInstance& consumer);




// A function that returns the left most digit of a 4 digit number (0 if non-enxistent)
int getFirstDigit(int number);

// A function that returns the second left most digit of a 4 digit number (0 if non-enxistent)
int getSecondDigit(int number);

// A function that returns the third left most digit of a 4 digit number
int getThirdDigit(int number);


// A function that returns the third left most digit of a 4 digit number
int getFourthDigit(int number);



// Check if instance b can communicate with instance a
bool follows(TaskInstance& a, TaskInstance& b);

// A function that prints vector of ints
void showVectorInt(std::vector<int> vec);

// A function that prints vector of doubles
void showVector(std::vector<double > vec);

// A function that prints matrix of doubles
void showMatrix(std::vector<std::vector<double> > vec);

// A function that replicates the matrix mat rows times horzontally and columns times vertically
std::vector<std::vector<double> > repmat(std::vector<std::vector<double> > mat, int rows, int columns);
