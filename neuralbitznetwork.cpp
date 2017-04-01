#include "neuralbitznetwork.h"
#include "neuron.h"
#include <iostream>

#define e 2.71828

neuralBitzNetwork::neuralBitzNetwork(int neurons, int inputs,QObject *parent) : QObject(parent) {
    myParent = parent;
    mNeuronNum = neurons;
    mInputNum = inputs;
    mInWeightPerNeuron = mInputNum;
    std::cout<<"Network "<<this<<" Created... ( Parent: "<<parent<<" )"<<std::endl;
    std::cout<<this<<"> Creating "<<mNeuronNum<<" Neurons with "<<mInputNum<<" Inputs each."<<std::endl;
    for(int n=0;n<neurons;n++) {
        mNeurons.append(new neuron(mInputNum,this));
    }
    say("Total Input Weights Needed: " + QString().setNum(neurons * inputs));
    say("Input Weights Per Neuron: " + QString().setNum(mInWeightPerNeuron));
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

bool neuralBitzNetwork::setup(QList<float> inputList,QList<float> weightList,QList<float> outputWeightList) {
    bool success = true;
    say("Setting up Network...");
    say("Set Neuron Inputs... " + QString().setNum(mNeuronNum) );
    for(int n=0;n<mNeuronNum;n++) {
        for (int z=0;z<mInputNum;z++) {
            mNeurons.at(n)->setInput(z,inputList.at(z));
            say("SET Neuron " + QString().setNum(n) + " INPUT " + QString().setNum(z) + " --> " + QString().setNum(inputList.at(z)));
        }
        //set outputWeights
        mNeurons.at(n)->setOutputWeight(outputWeightList.at(n));
        say("SET Neuron " + QString().setNum(n) + " Output Weight --> " + QString().setNum(outputWeightList.at(n)) );
    }
    //set inputWeights
    int n = 0;
    int cycle = 0;
    for(int o=0;o<(mNeuronNum * mInputNum);o++){
        say("Neuron --> " + QString().setNum(n + 1) + " InputWeight " + QString().setNum(o+1) + " --> " + QString().setNum(weightList.at(o)) );
        mNeurons.at(n)->setWeight(cycle,weightList.at(o));
        n++;
        (n >= mNeuronNum ) ? cycle++ : cycle=cycle ;
        (n >= mNeuronNum ) ?   n=0 : n=n ;
    }
    say( (success) ? "[Successful]" : "[Failed]" );
    return success;
}

float neuralBitzNetwork::findNetworkOutput() {
    QList<float> outs;
    say("Finding Network Answer...");
    for(int n=0;n<mNeuronNum;n++) {
        say("Activate Neuron " + QString().setNum(n) );
        float out = mNeurons.at(n)->findOutput();
        outs.append((mNeurons.at(n)->getOutput() * mNeurons.at(n)->getOutputWeight()));
        say("Final Weighted Neuron Output --> " + QString().setNum(outs.at(n)) );
    }
    float mNetworkOutput = 0;
    for(int n=0;n<mNeuronNum;n++) {
        mNetworkOutput += outs.at(n);
    }
    say("Final Network Answer: " + QString().setNum(sigmoid(mNetworkOutput)) );
    return mNetworkOutput;
}

float neuralBitzNetwork::sigmoid(float x) {
    return float(1/(1+std::pow(e,-x)));
}

float neuralBitzNetwork::dSigmoid(float x) {
    return (sigmoid(x) * (1-sigmoid(x)));
}
