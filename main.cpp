#include <iostream>
#include <vector>
#include <iterator>
#include <ctime>
#include <random>

#include "SmallBrain.h"

using namespace std;


int main(int argc, char* args[])
{
	srand(time(NULL));
	SmallBrain brian(2,2);


	for(int i = 0; i < 10; i++)
		brian.addNeuron(1);

	for(auto &layer: brian.layers)
		for(auto &neuron: layer)
			neuron.value = rand()%1000;

	for(int i = 0; i < 10; i++)
		brian.addSynapse(1);

	

	return 0;
}


