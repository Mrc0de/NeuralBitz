#ifndef NEURON_H
#define NEURON_H

#include <QObject>
#include <QWidget>
#include <QList>
#include <QRectF>


class neuron : public QWidget {
    Q_OBJECT
public:
    explicit neuron(int inputs,QWidget *parent = 0, int sequence=1);
    ~neuron();
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
    void setExampleWeights(int whichExampleNode=0);
    float sigmoid(float x);
    void paintEvent(QPaintEvent *);
    float getHiddenLayerSum();
private:
    QRectF *mRect;
    float dSigmoid(float x);
    QList<float> inputs;
    QList<float> weights;
    float output;
    float outputWeight;
    void say(QString sayThis);
    QWidget *mParent;
    float mHiddenLayerSum;
signals:

public slots:
};

#endif // NEURON_H
