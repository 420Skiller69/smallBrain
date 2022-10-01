#include <vector>

using namespace std;



class SmallBrain // uncouncious direct synapse trash
{
    struct Neuron;

    struct Synapse
    {
        int layer, neuron;
        double weight;
    };

    struct Neuron
    {
        vector<Synapse> synapss;
        double bias;
        double value;

        Neuron() : synapss(0) {};
    };

    vector<vector<Neuron>> layers;

    void fireNeuron(Neuron &neuron);
    
public: 
    SmallBrain(int inputSize, int outputSize)
    : layers(2) 
    {
        layers[0] = vector<Neuron>(inputSize);
        layers[1] = vector<Neuron>(outputSize);
    };

    vector<double> fire(vector<double> input);
    void addSynapse(double weightAbs);
    void addNeuron(double weightAbs);
    void changeRandomSynapse(double value);
    void changeRandomBias(double value);

};