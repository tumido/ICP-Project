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
#include <QTableWidget>
#include <QTableWidgetItem>

#include "MazeCard.h"
#include "GameManager.h"
#include "Player.h"
#include "CANGO.h"
#include "DEFAULT_VALUES.h"

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
    void finishedGame();
    void drawBoard();
    void updateBoard();
    void placeCard(QPointF &coord);
    void movePlayer(QPointF &coord);
public slots:
    void onActionExit();
    void onActionNewGame();
    void onActionLoad();
    void onActionSave();
    void onActionUndo();
    void onActionStats();

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
    void prepareUI();
    void clearVector(vector<QGraphicsItem*> &vect, QGraphicsScene *&scene);
};

#endif // LABYRINTHQT_H
