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
    bool setup(QList<float> inputList,QList<float> weightList,QList<float> outputWeightList);
    float mExpectedOutput;
    bool mDelayedExpectedOutput;
    bool checkForExpectedOutput();
    float fetchExpectedOutput();
    void setTraining(bool train);
    bool getTraining(bool train);
    float findNetworkOutput();
    float getLastOutput();
private:
    float sigmoid(float x);
    float dSigmoid(float x);
    void say(QString sayThis);
    void setNeuronInputs(QList<float> i);
    void setNeuronWeights(QList<float> w);
    QList<float> mInputs;
    QList<float> mWeights;
    QList<neuron*> mNeurons;
    int mNeuronNum;
    int mInputNum;
    int mWeightNum;
    int mInWeightPerNeuron;
    QObject *myParent;
    bool training;
    float mNetworkOutput;
signals:

public slots:
};

#endif // NEURALBITZNETWORK_H
