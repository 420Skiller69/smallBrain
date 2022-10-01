#include <iostream>
#include <vector>
#include <iterator>
#include <ctime>
#include <random>

#include "SmallBrain.h"

using namespace std;


int main()
{
	srand(time(NULL));
	SmallBrain brian(2,2);

	vector<double> input = {1,2};
	for(auto out: brian.fire(input))
		cout << out << endl;
	

	for(int i = 0; i < 1000; i++)
		brian.addNeuron(1);

	for(int i = 0; i < 1000; i++)
		brian.addSynapse(1);

	for(int i = 0; i < 1000; i++)
		brian.changeRandomBias(1);
	
	for(int i = 0; i < 1000; i++)
		brian.changeRandomSynapse(1);

	cout << endl;
	for(auto out: brian.fire(input))
		cout << out << endl;

	return 0;
}


