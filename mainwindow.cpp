#include "mainwindow.h"
#include "neuron.h"
#include "neuralbitznetwork.h"
#include <iostream>
#include <QApplication>

MainWindow::MainWindow(QApplication *app, QWidget *parent) : QMainWindow(parent) {
    myApp = app;
    std::cout<<"Parent Application: ("<<myApp<<")"<<std::endl;
    std::cout<<"Created Main Window...("<<this<<")"<<std::endl;
    myNet = new neuralBitzNetwork(3,2,this);

    //Example usage below
    QList<float> inputs;
    //Example inputs (replace em)
    inputs.append(1);
    inputs.append(1);
    QList<float> weights;
    //Example weights (replace em)
    weights.append(0.8);weights.append(0.4);weights.append(0.3);
    weights.append(0.2);weights.append(0.9);weights.append(0.5);
    QList<float> outWeights;
    //Example Output weights (replace em)
    outWeights.append(0.3);outWeights.append(0.5);outWeights.append(0.9);

    //The above example trains to become an AND gate by seeking output of 0.
    //Example values from some dudes website about AI (TODO: add url)
    myNet->mExpectedOutput = 0;
    if ( ! myNet->setup(inputs,weights,outWeights) ) { QApplication::exit(1); }
    float answer = myNet->findNetworkOutput();

    //Todo: Adjust Weights and Continue Training Network
    //Todo: Create Functions to produce the above
}

MainWindow::~MainWindow()
{
    delete myNet;
    std::cout<<"Destroying Main Window... ("<<this<<")"<<std::endl;
}
