#-------------------------------------------------
#
# Project created by QtCreator 2012-12-05T17:05:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = abicountdown
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    Pixmap.h

RESOURCES = animatedtiles.qrc
