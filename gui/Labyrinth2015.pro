QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = labyrinth2015_gui
QMAKE_CXXFLAGS += -std=c++11 -fPIC

DEPENDPATH += . ..
INCLUDEPATH += . ..


SOURCES += ../src/gui/client_gui.cpp \
        ../src/gui/LabyrinthQt.cpp \
    ../src/core/GameManager.cpp \
    ../src/core/Action.cpp \
    ../src/core/GameGenerator.cpp \
    ../src/core/MazeBoard.cpp \
    ../src/core/MazeCard.cpp \
    ../src/core/MazeField.cpp \
    ../src/core/PathFinder.cpp \
    ../src/core/Player.cpp

HEADERS += ../include/LabyrinthQt.h \
         ../include/ui_LabyrinthQt.h \
    ../include/Action.h \
    ../include/CANGO.h \
    ../include/GameGenerator.h \
    ../include/GameManager.h \
    ../include/MazeBoard.h \
    ../include/MazeCard.h \
    ../include/MazeField.h \
    ../include/PathFinder.h \
    ../include/Player.h \
    ../include/Point.h

RESOURCES += ../gui/res.qrc
