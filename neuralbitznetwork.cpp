#include "neuralbitznetwork.h"
#include "neuron.h"
#include <iostream>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QPainter>
#include <QWidget>
#include <QTimer>

#define e 2.71828

neuralBitzNetwork::neuralBitzNetwork(int neurons, int inputs,QMainWindow *parent) : QWidget(parent) {
    myParent = parent;
    mNeuronNum = neurons;
    mInputNum = inputs;
    mInWeightPerNeuron = mInputNum;
    mEpoch = 0;
    mTraining = true;
    mMarginOfError = NULL;
    setGeometry(0,0,256,256);
    std::cout<<"Network "<<this<<" Created... ( Parent: "<<parent<<" )"<<std::endl;
    std::cout<<this<<"> Creating "<<mNeuronNum<<" Neurons with "<<mInputNum<<" Inputs each."<<std::endl;
    for(int n=0;n<neurons;n++) {
        mNeurons.append(new neuron(mInputNum,this,n));
        mNeurons.at(n)->move((12+(n)*77),20);
    }
    say("Total Input Weights Needed: " + QString().setNum(neurons * inputs));
    say("Input Weights Per Neuron: " + QString().setNum(mInWeightPerNeuron));
    mNetRect = new QRectF(0,0,255,255);
}

void neuralBitzNetwork::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::SolidLine);
    painter.setBrush(Qt::green);
    painter.drawRect(*mNetRect);
    painter.drawText(5,12,"Epoch " + QString().setNum(mEpoch) );
    QString t;
    (mTraining) ? t = "Yes" : t = "No";
    painter.drawText(96,12,"Training: " +  t );
    painter.drawText(5,104,"Raw Network Output: " + QString().setNum(getLastOutput()) );
    painter.drawText(5,116,"Network Answer: " + QString().setNum(getLastAnswer()) );
    painter.drawText(5,128,"Expected Answer: " + QString().setNum(mExpectedOutput) );
    painter.drawText(5,140,"Margin of Error: " + QString().setNum(mMarginOfError) );
    painter.drawText(5,152,"DeltaSum: " + QString().setNum(mDeltaOutputSum) );
}

neuralBitzNetwork::~neuralBitzNetwork() {
    say("Destroying neuralBitzNetwork...");
    for(int d=0;d<mNeurons.size();d++){
        delete mNeurons[d];
    }
    delete mNetRect;
    say("Destroyed neuralBitzNetwork...");
}

void neuralBitzNetwork::say(QString sayThis) {
    std::cout<<this<<"> "<<sayThis.toStdString()<<std::endl;
}

bool neuralBitzNetwork::setup(QList<float> inputList,QList<float> weightList,QList<float> outputWeightList) {
    mWeights = weightList;
    mInputs = inputList;
    killMe = false;
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
    mNetworkOutput = 0;
    for(int n=0;n<mNeuronNum;n++) {
        mNetworkOutput += outs.at(n);
    }
    say("Final Network Answer: " + QString().setNum(sigmoid(mNetworkOutput)) );
    mLastAnswer = sigmoid(mNetworkOutput);
    mEpoch++;
    return mNetworkOutput;
}

float neuralBitzNetwork::getLastOutput() {
    return mNetworkOutput;
}

void neuralBitzNetwork::selfCorrect() {
    mMarginOfError = mExpectedOutput - mLastAnswer;
    mDeltaOutputSum = mMarginOfError * dSigmoid(mNetworkOutput);
    QList<float> deltaOutputWeights;
    for(int n=0;n<mNeuronNum;n++){
        deltaOutputWeights.append( mDeltaOutputSum * mNeurons.at(n)->getOutput() );
        say("Delta Output Weights: " + QString().setNum(deltaOutputWeights.at(n)));
    }
    QList<float> deltaHiddenSums;
    for(int n=0;n<mNeuronNum;n++){
        deltaHiddenSums.append( mDeltaOutputSum * mNeurons.at(n)->getOutputWeight() * dSigmoid( mNeurons.at(n)->getHiddenLayerSum() ) );
        say("Delta Hidden Sum: " + QString().setNum(deltaHiddenSums.at(n)));
    }
    QList<float> deltaInputWeights;
    for(int i=0;i<mInputNum;i++){
        for(int n=0;n<mNeuronNum;n++) {
            deltaInputWeights.append( deltaHiddenSums.at(n) * mNeurons.at(n)->getInput(i) );
            say("Delta Input Weight: " + QString().setNum(deltaInputWeights.at(n)));
        }
    }

    //Change Input Weights
    for(int i=0;i<mInputNum;i++){
        for(int n=0;n<mNeuronNum;n++){
            float nW = (mNeurons.at(n)->getWeight(i) + deltaInputWeights.at(n));
            mNeurons.at(n)->setWeight(i,nW);
            say("New Neuron " + QString().setNum(n) + " Weight " + QString().setNum(i) + " = " + QString().setNum(mNeurons.at(n)->getWeight(i)) );
        }
    }
    //Change Output Weights
    for(int n=0;n<mNeuronNum;n++){
        mNeurons.at(n)->setOutputWeight( (mNeurons.at(n)->getOutputWeight() + deltaOutputWeights.at(n)) );
        say("New Output Weight " + QString().setNum(n) + " = " + QString().setNum(mNeurons.at(n)->getOutputWeight()) );
    }

    //Dont change any until the end we need the values
    //        say("Old Output Weight: " + QString().setNum(mNeurons.at(n)->getOutputWeight()) );
    //
    //        say("New Output Weight: " + QString().setNum(mNeurons.at(n)->getOutputWeight()) );

}


float neuralBitzNetwork::getLastAnswer() {
    return mLastAnswer;
}

float neuralBitzNetwork::sigmoid(float x) {
    return float(1/(1+std::pow(e,-x)));
}

float neuralBitzNetwork::dSigmoid(float x) {
    return (sigmoid(x) * (1-sigmoid(x)));
}

void neuralBitzNetwork::selfC() {
    selfCorrect();
    QTimer::singleShot(50, this, SLOT(findOut()));
    update();
}

void neuralBitzNetwork::findOut() {
    this->findNetworkOutput();
    update();
    if ( !killMe && !mDelayedExpectedOutput ) {
        QTimer::singleShot(50, this, SLOT(selfC()));
    }
}
