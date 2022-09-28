#include "SmallBrain.h"
#include <cmath>
#include <iterator>
#include <algorithm>
#include <iostream>
















void SmallBrain::fireNeuron(Neuron &neuron)
{
    neuron.value = 0;
    for(auto incoming: neuron.synapss)
        neuron.value += layers[incoming.layer][incoming.neuron].value * incoming.weight;
    
    neuron.value += neuron.bias;
    neuron.value = neuron.value / (1 + (std::abs(neuron.value)));
}

void SmallBrain::addNeuron(double weightAbs)
{
    int layer;
    Synapse syn; syn.weight = 0; // ihbfivbihfbiuaehbuilhaouhboaehgbuahiugvhsildghbihiuldfhbfbgdndmjzfkmgdfgbdfnfhmjnhfgghnfnfdcs
    if(rand()/(double)RAND_MAX < 0.5 && layers.size() > 2) // add new layer or use exiistinng one ? 50/50
        layer = rand()%(layers.size() - 2); // use existin layer
    else
    {
        int newLayer = rand()%(layers.size() - 1); // add new layer
        layers.insert(layers.begin() + newLayer + 1,vector<SmallBrain::Neuron>(0));
        layer = newLayer;

        for(int i = layer+2 ; i < layers.size(); i++) // correct outdated idexes due to isertion of layer
            for(int j = 0; j < layers[i].size(); j++)
                for(auto &synaps: layers[i][j].synapss)
                    if(synaps.layer > layer+1)
                    {
                        synaps.layer++;
                        synaps.weight += 10;
                    }
    }
    
     syn.layer = 0; // need to make synapses for the new neuron
    Neuron n;

    syn.layer = layer;          // find random input neuron directly on the left layer to the new neurons layer
    syn.neuron = rand()%layers[layer].size();
    syn.weight += 1; //2*weightAbs * rand()/RAND_MAX - weightAbs;
    n.synapss.push_back(syn);
    syn.weight -= 1;

    do
    {
        syn.layer = 0;
        int neuronN = 0;        // find random inputNeuron on any of the left layers to the new neuron 
        for(int i = 0; i < layer+1; i++) neuronN += layers[i].size();
        int randInd = rand()%(neuronN);

        while(randInd >= layers[syn.layer].size())
        {
            randInd -= layers[syn.layer].size();
            syn.layer++;
        }
        syn.neuron = randInd;

    }while(syn.layer == n.synapss[0].layer && syn.neuron == n.synapss[0].neuron);
    syn.weight += 2; //2*weightAbs * rand()/RAND_MAX - weightAbs;
    n.synapss.push_back(syn);
    syn.weight -= 2; //2*weightAbs * rand()/RAND_MAX - weightAbs;


    layers[layer+1].push_back(n);   // add neuron


    int layerInd = layer+2, neuronInd;      // find random output neuron
    int neuronN = 0;
    for(int i = layer+2; i < layers.size(); i++) neuronN += layers[i].size();
    int randInd = rand()%(neuronN);

    while(randInd >= layers[layerInd].size())
    {
        randInd -= layers[layerInd].size();
        layerInd++;
    }
    neuronInd = randInd;

    syn.layer = layer+1;        // synaps from new neuron to output neuron
    syn.neuron = layers[layer+1].size()-1;
    syn.weight += 3;//2*weightAbs * rand()/RAND_MAX - weightAbs;
    layers[layerInd][neuronInd].synapss.push_back(syn);
    syn.weight -= 3;//2*weightAbs * rand()/RAND_MAX - weightAbs;
}

void SmallBrain::addSynapse(double weightAbs)
{   
    int layerInd = 1, neuronInd;
    Synapse syn; syn.layer = 0;

    // get random output neuron
    int neuronN = 0;
    for(int i = 1; i < layers.size(); i++) neuronN += layers[i].size();
    int randInd = rand()%(neuronN);

    while(randInd >= layers[layerInd].size())
    {
        randInd -= layers[layerInd].size();
        layerInd++;
    }
    neuronInd = randInd;
    
    // get random input neuron
    neuronN = 0;
    for(int i = 0; i < layerInd; i++) neuronN += layers[i].size();
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


