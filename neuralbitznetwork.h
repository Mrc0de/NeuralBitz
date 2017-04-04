#ifndef NEURALBITZNETWORK_H
#define NEURALBITZNETWORK_H

#include <QObject>
#include <QList>
#include <QMainWindow>
#include "neuron.h"

class neuralBitzNetwork : public QWidget
{
    Q_OBJECT
public:
    explicit neuralBitzNetwork(int neurons, int inputs,QMainWindow *parent = 0);
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
    void paintEvent(QPaintEvent *);
    float getLastAnswer();
    int mNeuronNum;
    void selfCorrect();
    bool killMe;
private:
    float sigmoid(float x);
    float dSigmoid(float x);
    void say(QString sayThis);
    void setNeuronInputs(QList<float> i);
    void setNeuronWeights(QList<float> w);
    QList<float> mInputs;
    QList<float> mWeights;
    QList<neuron*> mNeurons;
    long mEpoch;
    int mInputNum;
    int mWeightNum;
    int mInWeightPerNeuron;
    bool mTraining;
    float mNetworkOutput;
    QRectF *mNetRect;
    QMainWindow *myParent;
    float mLastAnswer;
    float mMarginOfError;
    float mDeltaOutputSum;
signals:

public slots:
    void selfC();
    void findOut();
};

#endif // NEURALBITZNETWORK_H
