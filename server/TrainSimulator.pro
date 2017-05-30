#-------------------------------------------------
#
# Project created by QtCreator 2016-04-15T06:45:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrabalhoTrem
TEMPLATE = app


SOURCES += \
    source/main.cpp \
    source/mainwindow.cpp \
    source/semaforo.cpp \
    source/system_train.cpp \
    source/trem.cpp \

HEADERS  += \
    header/mainwindow.h \
    header/semaforo.h \
    header/system_train.h \
    header/trem.h

FORMS    += \
    forms/mainwindow.ui

CONFIG  += c++11
QMAKE_CXXFLAGS += -std=c++11 -pthread
LIBS += -pthread
