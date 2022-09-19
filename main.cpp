#include <iostream>
#include <vector>
#include <iterator>
#include <random>
#include <ctime>

#include "Classroom.h"

using namespace std;


int main(int argc, char* args[])
{
	srand(time(NULL));

	class Classroom cl(10); // create the population of students which will be trained

	for(int generation = 0; generation < 1000; generation++)
	{
		cl.generation(); // evaluate fitnesses, pair, reproduce and mutate population
		
		cout << endl << generation << "--------------------------" << endl; 
		cl.displayAll();	
	}


	return 0;
}


