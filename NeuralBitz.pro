#-------------------------------------------------
#
# Project created by QtCreator 2017-03-25T22:37:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeuralBitz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    neuron.cpp \
    neuralbitznetwork.cpp

HEADERS  += mainwindow.h \
    neuron.h \
    neuralbitznetwork.h

FORMS += \
    mainwindow.ui
