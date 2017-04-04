#include "neuron.h"
#include "neuralbitznetwork.h"
#include <iostream>
#include <cmath>
#include <QTime>
#include <QPainter>

#define e 2.71828

neuron::neuron(int inputs, QWidget *parent, int sequence) : QWidget(parent) {
    //QTime::currentTime()
    mParent = parent;
    mHiddenLayerSum = NULL;
    std::cout<<"I am Neuron: "<<this<<" (Parent: "<<parent<<")"<<std::endl;
    std::cout<<"Inputs: "<<inputs<<std::endl;
//    std::cout<<this<<"> S_Test: Sigmoid Of 1 is "<<sigmoid(1)<<std::endl;
//    std::cout<<this<<"> D_Test: Derivative of Sigmoid(1.235) is "<<dSigmoid(1.235)<<std::endl;
    setGeometry(0,0,32,32);
    mRect = new QRectF(this->x() + mParent->x(),this->y() + mParent->y(),this->width()-1,this->height()-1);
}

neuron::~neuron(){
    say("Destroying neuron...");
    delete mRect;
}

void neuron::say(QString sayThis) {
    std::cout<<this<<"> "<<sayThis.toStdString()<<std::endl;
}

void neuron::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setPen(Qt::SolidLine);
    painter.setBrush(Qt::red);
    painter.drawRect(*mRect);
}

float neuron::findOutput() {
    float retVal = 0;
    QList<float> hiddenLayers;
    for(int f=0; f<inputs.size(); f++){
        say("Input " + QString().setNum(f + 1) + " = " + QString().setNum(inputs.at(f)));
        float value = (inputs.at(f) * weights.at(f));
        hiddenLayers.append(value);
        say(QString().setNum(inputs.at(f)) +" * " + QString().setNum(weights.at(f)) +" = "+QString().setNum(hiddenLayers.at(f)));
    }
    //Sum Hidden Layer Results
    float hLayerSum = 0;
    for (int f=0;f<hiddenLayers.size();f++){
        hLayerSum += hiddenLayers.at(f);
    }
    //Activate with sigmoid of hLayerSum
    say("Activating with Hidden Layer Sum Of " + QString().setNum(hLayerSum) );
    output = sigmoid(hLayerSum);
    retVal = output;
    say("Output: " + QString().setNum(getOutput()) );
    return retVal;
}

float neuron::getHiddenLayerSum() {
    return mHiddenLayerSum;
}

void neuron::setExampleInputs() {
    setInput(0,1);
    setInput(1,1);
}

void neuron::setExampleWeights(int whichExampleNode) {
    switch(whichExampleNode) {
        case 0: {
            setWeight(0,0.8);
            setWeight(1,0.2);
            setOutputWeight(0.3);
            break;
        }
        case 1: {
            setWeight(0,0.4);
            setWeight(1,0.9);
            setOutputWeight(0.5);
            break;
        }
        case 2: {
            setWeight(0,0.3);
            setWeight(1,0.5);
            setOutputWeight(0.9);
            break;
        }
    }


}

float neuron::sigmoid(float x) {
    return float(1/(1+std::pow(e,-x)));
}

float neuron::dSigmoid(float x) {
    return (sigmoid(x) * (1-sigmoid(x)));
}

void neuron::setInput(int which,float data) {
//    say("setInput");
    if ( inputs.size() <= which ) {
        inputs.append(data);
    } else {
        inputs[which] = data;
    }
}

float neuron::getInput(int which) {
    return inputs.at(which);
}

void neuron::setRandomWeight(int which) {
    qsrand(QTime::currentTime().msec());
    weights[which] = qrand();
    //A random Number Generator and a Neural Network Having an argument in a bar
    //The Random Number Gen keeps picking random numbers
    //The Neural network keeps trying to guess the next one
    //Made me chuckle.
}

void neuron::setWeight(int which,float data) {
//    say("setWeight");
    if ( weights.size() <= which ) {
        weights.append(data);
    } else {
        weights[which] = data;
    }
}

float neuron::getWeight(int which) {
    return weights.at(which);
}

float neuron::getOutput() {
    return output;
}

void neuron::setOutputWeight(float w) {
    outputWeight = w;
}

float neuron::getOutputWeight() {
    return outputWeight;
}
