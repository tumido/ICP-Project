#ifndef LABYRINTHQT_H
#define LABYRINTHQT_H

#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QFormLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>
#include <QtCore/QDebug>
#include <QtGui/QPixmap>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsPixmapItem>

//#include "GameManager.h"
#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define BOARD_MIN 5
#define BOARD_MAX 11
#define BOARD_DEFAULT 7

namespace Ui {
class LabyrinthQt;
}

class LabyrinthQt : public QMainWindow
{
    Q_OBJECT

public:
    explicit LabyrinthQt(QWidget *parent = 0);
    ~LabyrinthQt();
    void startGame();
    bool prepareGame();
public slots:
    void onActionExit();
    void onActionNewGame();
    void onActionLoad();
    void onActionSave();

protected:


private:
    Ui::LabyrinthQt *ui;
    //GameManager game;

};

#endif // LABYRINTHQT_H
