/**
 * @file client_gui.cpp
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Main function for Qt version of our program
 */
#include "../include/LabyrinthQt.h"
#include <QApplication>

/// @brief Main for CLI variant of the game
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LabyrinthQt w;
    w.show();

    return a.exec();
}
