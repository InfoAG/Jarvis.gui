QT       += core gui network
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

INCLUDEPATH += ../../Frontend
LIBS += -L../../Frontend/debug/ -lJarvis-Frontend


SOURCES += main.cpp\
        mainwindow.cpp \
    ServerObject.cpp

HEADERS  += mainwindow.h \
    ServerObject.h

FORMS    += mainwindow.ui
