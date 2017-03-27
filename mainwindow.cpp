#include "mainwindow.h"
#include "neuron.h"
#include "neuralbitznetwork.h"
#include <iostream>

MainWindow::MainWindow(QApplication *app, QWidget *parent) : QMainWindow(parent) {
    myApp = app;
    std::cout<<"Parent Application: ("<<myApp<<")"<<std::endl;
    std::cout<<"Created Main Window...("<<this<<")"<<std::endl;
    myNet = new neuralBitzNetwork(3,2,this);
}

MainWindow::~MainWindow()
{
    delete myNet;
    std::cout<<"Destroying Main Window... ("<<this<<")"<<std::endl;
}
