#include "../include/LabyrinthQt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LabyrinthQt w;
    w.show();

    return a.exec();
}
