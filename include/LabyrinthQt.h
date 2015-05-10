#ifndef LABYRINTHQT_H
#define LABYRINTHQT_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDebug>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QMouseEvent>

#include "MazeCard.h"
#include "GameManager.h"
#include "Player.h"
#include "CANGO.h"

#define MAX_PLAYERS 4
#define MIN_PLAYERS 2
#define BOARD_MIN 5
#define BOARD_MAX 11
#define BOARD_DEFAULT 7
#define SPACING 5

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
    void drawBoard();
    void updateBoard();
public slots:
    void onActionExit();
    void onActionNewGame();
    void onActionLoad();
    void onActionSave();

protected:
    void mousePressEvent(QMouseEvent* e);

private:
    Ui::LabyrinthQt *ui;
    GameManager * game;
    vector<QGraphicsItem*> horizontalButtons;
    vector<QGraphicsItem*> verticalButtons;
    vector<QGraphicsItem*> tiles;
    vector<QGraphicsItem*> treasures;
    vector<QGraphicsItem*> figures;
    bool turnState;
    void toggleArrows();
};

#endif // LABYRINTHQT_H
