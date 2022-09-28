#include <vector>

using namespace std;



class SmallBrain // uncouncious direct synapse trash
{
public: // faosjdvoöjanfboaebof FIKCFIXIFXIngaeojnboaeböoaenboöndgbisdgbianebosgboöjaoejgboönöojeanbos
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
        void fire();
    };

    vector<vector<Neuron>> layers;


    SmallBrain(int inputSize, int outputSize)
    : layers(2) 
    {
        layers[0] = vector<Neuron>(inputSize);
        layers[1] = vector<Neuron>(outputSize);
    };

    void fireNeuron(Neuron &neuron);
    
    void addSynapse(double weightAbs);
    void addNeuron(double weightAbs);

    // Neuron* getRandomNeuron();
    // int getLayerInd(Neuron *pointr);
    // int getNeuronInd(Neuron &pointr);
};