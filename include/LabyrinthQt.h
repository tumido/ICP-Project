#ifndef LABYRINTHQT_H
#define LABYRINTHQT_H

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QDebug>
#include <QPixmap>

#include "../include/GameManager.h"
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
