QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = ../labyrint2015
QMAKE_CXXFLAGS += -std=c++11 -fPIC

DEPENDPATH += . ..
INCLUDEPATH += . ..
LIBS += ../build/core.a

SOURCES += ../src/gui/client_gui.cpp \
        ../src/gui/LabyrinthQt.cpp \
    ../src/core/GameManager.cpp

HEADERS += ../src/include/LabyrinthQt.h \
         ../src/include/ui_LabyrinthQt.h

RESOURCES += ../gui/res.qrc
