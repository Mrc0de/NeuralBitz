#ifndef NEURALBITZNETWORK_H
#define NEURALBITZNETWORK_H

#include <QObject>
#include <QList>
#include "neuron.h"

class neuralBitzNetwork : public QObject
{
    Q_OBJECT
public:
    explicit neuralBitzNetwork(int neurons, int inputs,QObject *parent = 0);
    ~neuralBitzNetwork();
    void setInputs(QList<float>);
    void setWeights(QList<float>);
private:
    void say(QString sayThis);
    void setNeuronInputs(QList<float> i);
    void setNeuronWeights(QList<float> w);
    QList<float> mInputs;
    QList<float> mWeights;
    QList<neuron*> mNeurons;
    int mNeuronNum;
    int mInputNum;
    QObject *myParent;
signals:

public slots:
};

#endif // NEURALBITZNETWORK_H
