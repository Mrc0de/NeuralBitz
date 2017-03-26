#include "mainwindow.h"
#include "neuron.h"
#include <iostream>

MainWindow::MainWindow(QApplication *app, QWidget *parent) : QMainWindow(parent) {
    myApp = app;
    std::cout<<"Parent Application: ("<<myApp<<")"<<std::endl;
    std::cout<<"Created Main Window...("<<this<<")"<<std::endl;
    myN[0] = new neuron(2,this);
    myN[0]->setExampleInputs();
    myN[0]->setExampleWeights();
    float r1 = myN[0]->findOutput();
    float r1Final = (myN[0]->getOutputWeight() * r1);
    std::cout<<"Final Output Of "<<myN[0]<<" = "<<QString().setNum(r1Final).toStdString()<<std::endl;

    myN[1] = new neuron(2,this);
    myN[1]->setExampleInputs();
    myN[1]->setExampleWeights(1);
    float r2 = myN[1]->findOutput();
    float r2Final = (myN[1]->getOutputWeight() * r1);
    std::cout<<"Final Output Of "<<myN[1]<<" = "<<QString().setNum(r1Final).toStdString()<<std::endl;

    myN[2] = new neuron(2,this);
    myN[2]->setExampleInputs();
    myN[2]->setExampleWeights(2);
    float r3 = myN[2]->findOutput();
    float r3Final = (myN[2]->getOutputWeight() * r1);
    std::cout<<"Final Output Of "<<myN[2]<<" = "<<QString().setNum(r1Final).toStdString()<<std::endl;
    float netAnswer = myN[0]->sigmoid(r1Final + r2Final + r3Final);
    std::cout<<"Network Answer (1 Epoch) is "<<QString().setNum(netAnswer).toStdString()<<std::endl;
}

MainWindow::~MainWindow()
{
    delete myN[0];
    std::cout<<"Destroying Main Window... ("<<this<<")"<<std::endl;
}
