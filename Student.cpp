#include <iostream>
#include <cmath>

#include "Student.h"


using namespace std;


double Student::getFitness()
{
	vector<char> keyword = {'j', 'o', 'j'}; 
	double temp_fitness = 0;

	for(vector<char>::size_type i = 0; i < keyword.size(); i++) 
		temp_fitness += word[i] == keyword[i];

    temp_fitness = exp(temp_fitness);

	fitness = temp_fitness;
    return temp_fitness;
}

void Student::display()
{
	for(auto letter: word)
		cout << letter ;
	cout << " => " << getFitness();
}

void interpolate(const class Student &parent1, const class Student &parent2, class Student &child, double bias) // getting a student that is made up of two other students
{
	for(vector<char>::size_type i = 0; i < child.word.size(); i++)
		child.word[i] = ( rand()/(double)RAND_MAX < bias) ? parent1.word[i] : parent2.word[i];
}

void Student::mutate(double probability, double strength) // some kind of smoother probability to mutation strength prefered
{
	if(rand()/(double)RAND_MAX < probability)
	{
		for(int i = 0; i <= strength; i++)
			word[rand()%word.size()] = 'a' + rand()%('z' - 'a' + 1);
	}
}
