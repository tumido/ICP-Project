QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = labyrinth2015_gui

DEPENDPATH += . ..
INCLUDEPATH += . ..
LIB += ../build/core.so

SOURCES += ../src/gui/client_gui.cpp \
        ../src/gui/LabyrinthQt.cpp

HEADERS += ../include/LabyrinthQt.h \
         ../include/ui_LabyrinthQt.h

RESOURCES += ../gui/res.qrc
