#include "neuralbitznetwork.h"
#include "neuron.h"
#include <iostream>


neuralBitzNetwork::neuralBitzNetwork(int neurons, int inputs,QObject *parent) : QObject(parent) {
    myParent = parent;
    mNeuronNum = neurons;
    mInputNum = inputs;
    std::cout<<"Network "<<this<<" Created... ( Parent: "<<parent<<" )"<<std::endl;
    std::cout<<this<<"> Creating "<<mNeuronNum<<" Neurons with "<<mInputNum<<" Inputs each."<<std::endl;
    for(int n=0;n<neurons;n++) {
        mNeurons.append(new neuron(mInputNum,this));
    }
}

neuralBitzNetwork::~neuralBitzNetwork() {
    say("Destroying neuralBitzNetwork...");
    for(int d=0;d<mNeurons.size();d++){
        delete mNeurons[d];
    }
    say("Destroyed neuralBitzNetwork...");
}

void neuralBitzNetwork::say(QString sayThis) {
    std::cout<<this<<"> "<<sayThis.toStdString()<<std::endl;
}
