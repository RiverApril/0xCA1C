#-------------------------------------------------
#
# Project created by QtCreator 2015-07-03T21:00:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 0xCA1C
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    mathinterpreter.cpp

HEADERS  += mainwindow.h \
    mathinterpreter.h \
    exceptions.h

FORMS    += mainwindow.ui
