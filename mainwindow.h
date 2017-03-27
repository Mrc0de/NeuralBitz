#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "neuron.h"
#include "neuralbitznetwork.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QApplication *app, QWidget *parent = 0 );
    ~MainWindow();
private:
    QApplication *myApp;
    neuralBitzNetwork *myNet;
};

#endif // MAINWINDOW_H
