#include "SmallBrain.h"
#include <cmath>
#include <iterator>
#include <algorithm>
#include <iostream>




vector<double> SmallBrain::fire(vector<double> input)
{
    if(input.size() != layers[0].size())    // check valid input
        return vector<double>(layers[layers.size()-1].size(), 0);

    for(std::vector<double>::size_type i = 0; i < input.size(); i++)    // set input
        layers[0][i].value = input[i];
    
    for(std::vector<std::vector<SmallBrain::Neuron>>::size_type i = 1; i < layers.size(); i++)  //fire
        for(auto &neuron: layers[i])
            fireNeuron(neuron);
    
    vector<double> output(layers[layers.size()-1].size());  // get output
    for(std::vector<double>::size_type i = 0; i < input.size(); i++)
        output[i] = layers[layers.size()-1][i].value;
    
    return output;
}

void SmallBrain::fireNeuron(Neuron &neuron)
{
    neuron.value = 0;
    for(auto incoming: neuron.synapss)
        neuron.value += layers[incoming.layer][incoming.neuron].value * incoming.weight;
    
    neuron.value -= neuron.bias;
    if(neuron.value < 0) neuron.value = 0;
}

void SmallBrain::changeRandomSynapse(double value)
{
    if(layers.size() == 2)
    {
        bool isEmpty = true;
        for(auto neuron: layers[1])
            if(neuron.synapss.size() != 0) isEmpty = false;
        
        if(isEmpty) return;
    }
    // get random neuron
    int neuronN = 0, layerInd = 1;
    for(std::vector<std::vector<SmallBrain::Neuron>>::size_type i = 1; i < layers.size(); i++) neuronN += layers[i].size();
    std::vector<SmallBrain::Neuron>::size_type neuronInd = rand()%(neuronN);

    do{
        while(neuronInd >= layers[layerInd].size())
        {
            neuronInd -= layers[layerInd].size();
            layerInd++;
        }
    }while(layers[layerInd][neuronInd].synapss.size() == 0);

    layers[layerInd][neuronInd].synapss[rand()%layers[layerInd][neuronInd].synapss.size()].weight += value;
}

void SmallBrain::changeRandomBias(double value)
{
    int neuronN = 0, layerInd = 1;
    for(std::vector<std::vector<SmallBrain::Neuron>>::size_type i = 1; i < layers.size(); i++) neuronN += layers[i].size();
    std::vector<SmallBrain::Neuron>::size_type neuronInd = rand()%(neuronN);

    while(neuronInd >= layers[layerInd].size())
    {
        neuronInd -= layers[layerInd].size();
        layerInd++;
    };

    layers[layerInd][neuronInd].bias += value;
}

void SmallBrain::addNeuron(double weightAbs)
{

    int newNeuronLayer; // layer to add neuron to with 0 meaning fist possible one
    if(rand()/(double)RAND_MAX < 0.5 && layers.size() > 2) // add new layer or use exiistinng one ? 50/50
        newNeuronLayer = rand()%(layers.size() - 2); 
    else
    {
        int newLayer = rand()%(layers.size() - 1); 
        layers.insert(layers.begin() + newLayer + 1,vector<SmallBrain::Neuron>(0));
        newNeuronLayer = newLayer;

        for(std::vector<std::vector<SmallBrain::Neuron>>::size_type i = newNeuronLayer+2; i < layers.size(); i++) // correct outdated idexes due to isertion of layer
            for(std::vector<SmallBrain::Neuron>::size_type j = 0; j < layers[i].size(); j++)
                for(auto &synaps: layers[i][j].synapss)
                    if(synaps.layer > newNeuronLayer)
                        synaps.layer++;
    }
    
    Synapse syn; // need to make synapses for the new neuron
    syn.layer = newNeuronLayer;          
    syn.neuron = rand()%layers[newNeuronLayer].size(); // find random input neuron directly on the left layer to the new neurons layer
    syn.weight = 2*weightAbs * rand()/RAND_MAX - weightAbs;
    
    Neuron n;
    n.synapss.push_back(syn);   // add synapse to newNeuron

    do // find random inputNeuron on any of the left layers to the newNeuronLayer ----------------------------------------------------
    {
        syn.layer = 0;
        
        int neuronN = 0;        
        for(int i = 0; i < newNeuronLayer+1; i++) neuronN += layers[i].size();  // calculate neuronN

        std::vector<SmallBrain::Neuron>::size_type randInd = rand()%(neuronN);  // random Index that determines the Neuron we will use
        while(randInd >= layers[syn.layer].size()) // skip layers if randInd is bigger than them
        {
            randInd -= layers[syn.layer].size();
            syn.layer++;
        }
        syn.neuron = randInd;

    }while(syn.layer == n.synapss[0].layer && syn.neuron == n.synapss[0].neuron);  // redo if synaps already exists

    syn.weight = 2*weightAbs * rand()/RAND_MAX - weightAbs;
    n.synapss.push_back(syn);  // add synapse to newNeuron

    layers[newNeuronLayer+1].push_back(n);   // add neuron

    // find random output neuron--------------------------------------------------------------------------------------------
    int layerInd = newNeuronLayer+2, neuronInd;      
    int neuronN = 0;
    for(std::vector<std::vector<SmallBrain::Neuron>>::size_type i = newNeuronLayer+2; i < layers.size(); i++) neuronN += layers[i].size();
    std::vector<SmallBrain::Neuron>::size_type randInd = rand()%(neuronN);

    while(randInd >= layers[layerInd].size())
    {
        randInd -= layers[layerInd].size();
        layerInd++;
    }
    neuronInd = randInd;

    syn.layer = newNeuronLayer+1;        // synaps from new neuron to output neuron
    syn.neuron = layers[newNeuronLayer+1].size()-1;
    syn.weight = 2*weightAbs * rand()/RAND_MAX - weightAbs;
    layers[layerInd][neuronInd].synapss.push_back(syn);
}

void SmallBrain::addSynapse(double weightAbs)
{   
    int layerInd = 1, neuronInd;
    Synapse syn; syn.layer = 0;

    // get random output neuron
    int neuronN = 0;
    for(std::vector<std::vector<SmallBrain::Neuron>>::size_type i = 1; i < layers.size(); i++) neuronN += layers[i].size();
    std::vector<SmallBrain::Neuron>::size_type randInd = rand()%(neuronN);

    while(randInd >= layers[layerInd].size())
    {
        randInd -= layers[layerInd].size();
        layerInd++;
    }
    neuronInd = randInd;
    
    // get random input neuron
    neuronN = 0;
    for(std::vector<std::vector<SmallBrain::Neuron>>::size_type i = 0; i < layerInd; i++) neuronN += layers[i].size();
    randInd = rand()%(neuronN);

    while(randInd >= layers[syn.layer].size())
    {
        randInd -= layers[syn.layer].size();
        syn.layer++;
    }
    syn.neuron = randInd;

    // check for duplicate
    for(auto &synaps: layers[layerInd][neuronInd].synapss)
        if(synaps.layer == syn.layer && synaps.neuron == syn.neuron)
            return;

    // put in synaps
    syn.weight = 2*weightAbs * rand()/RAND_MAX - weightAbs;
    layers[layerInd][neuronInd].synapss.push_back(syn);
}


