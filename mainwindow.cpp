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
}

MainWindow::~MainWindow()
{
    delete myN[0];
    std::cout<<"Destroying Main Window... ("<<this<<")"<<std::endl;
}
