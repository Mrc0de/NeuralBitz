#include "mainwindow.h"
#include "neuron.h"
#include "neuralbitznetwork.h"
#include <iostream>
#include <QApplication>
#include <QTimer>

MainWindow::MainWindow(QApplication *app, QWidget *parent) : QMainWindow(parent) {
    myApp = app;
    std::cout<<"Parent Application: ("<<myApp<<")"<<std::endl;
    std::cout<<"Created Main Window...("<<this<<")"<<std::endl;
    setGeometry(128, 128, 256,256);
    myNet = new neuralBitzNetwork(3,2,this);

    //Example usage below
    QList<float> inputs;
    //Example inputs (replace em)
    inputs.append(1);
    inputs.append(1);
    QList<float> weights;
    //Example weights (replace with random number 0-1)
    weights.append(0.8);weights.append(0.4);weights.append(0.3);
    weights.append(0.2);weights.append(0.9);weights.append(0.5);
    QList<float> outWeights;
    //Example Output weights (replace random number 0-1)
    outWeights.append(0.3);outWeights.append(0.5);outWeights.append(0.9);

    //The above example trains to become an XOR gate by seeking output of 0 (from 2 inputs of 1).
    //Example values from some dudes website about AI (TODO: add url)
    myNet->mExpectedOutput = 0;
    if ( ! myNet->setup(inputs,weights,outWeights) ) { QApplication::exit(1); }
    float answer = myNet->findNetworkOutput();
    if (!myNet->mDelayedExpectedOutput){
        //If expected value is already known
        QTimer::singleShot(1000, myNet, SLOT(selfC()));
    } else {
        //If comparison value is unknown until a later time
        myNet->mExpectedOutput = NULL;
    }
    //Todo: Adjust Weights and Continue Training Network
    //Todo: Create Functions to produce the above
}

MainWindow::~MainWindow()
{
    delete myNet;
    std::cout<<"Destroying Main Window... ("<<this<<")"<<std::endl;
}
