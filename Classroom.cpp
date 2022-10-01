#include <iostream>

#include "Classroom.h"


void Classroom::generation()
{
    // calc fitnesses and totalfitness ------------------------------------------------------
    totalFitness = 0;
    for(auto &s: population)
        totalFitness += s.getFitness();

    // generate childs in population_mirror -------------------------------------------------
    for(auto &child: population_mirror) 
    {
        int parentInd1 = getRandomStudent(), parentInd2 = getRandomStudent();
        // swap them so the first one is always the fittest
        if( population[parentInd1].fitness < population[parentInd2].fitness)    std::swap(parentInd1, parentInd2);
        
        // getting bias so that the fitter one gets more genes put into child
        double bias = population[parentInd1].fitness / ( population[parentInd1].fitness + population[parentInd2].fitness );
        interpolate(population[parentInd1], population[parentInd2], child, bias);
        
        
        child.mutate(0.2, 1);
    }
    swap(population, population_mirror);
}

int Classroom::getRandomStudent()
{
    std::vector<Student>::size_type ind = 0;

    if(totalFitness == 0)
        return rand()%population.size();
    else
    {
        double randVal = totalFitness * rand()/(double)RAND_MAX;
        do
        {
            randVal -= population[ind].fitness;
            ind++;
        }while(randVal > 0 && ind < population.size());
        ind--;
    }
    return ind;
}

class Student& Classroom::getBest()
{
    std::vector<class Student>::size_type ind = 0;
    for(std::vector<class Student>::size_type i = 0; i < population.size(); i++)
        if(population[i].fitness > population[ind].fitness)
            ind = i;
    
    return population[ind];
}

void Classroom::displayAll()
{
    for(auto s: population)
    {
        s.display();
        cout << endl;
    }
}