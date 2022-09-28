#include "Student.h"

using namespace std;

class Classroom
{
    vector<class Student> population;
    vector<class Student> population_mirror;

    double totalFitness;

    public:
        Classroom(int size)
        {
            population          = vector<class Student>(size); // is this the correct way of initalizing vectors ???!
            population_mirror   = vector<class Student>(size);
        }

        int getRandomStudent();
        class Student& getBest();
        void generation();
        void displayAll();
};