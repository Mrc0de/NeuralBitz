#ifndef NEURON_H
#define NEURON_H

#include <QObject>
#include <QList>


class neuron : public QObject {
    Q_OBJECT
public:
    explicit neuron(int inputs,QObject *parent = 0);
    void setInput(int which,float data);
    float getInput(int which);
    void setWeight(int which,float data);
    void setRandomWeight(int which);
    float getWeight(int which);
    float findOutput();
    float getOutput();
    float getOutputWeight();
    void setOutputWeight(float w);
    void setExampleInputs();
    void setExampleWeights();

private:
    float sigmoid(float x);
    float dSigmoid(float x);
    QList<float> inputs;
    QList<float> weights;
    float output;
    float outputWeight;
    void say(QString sayThis);

signals:

public slots:
};

#endif // NEURON_H
