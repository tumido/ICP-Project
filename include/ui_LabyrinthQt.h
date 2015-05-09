#ifndef UI_LABYRINTHQT_H
#define UI_LABYRINTHQT_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QListWidget>
#include <QListWidgetItem>



QT_BEGIN_NAMESPACE

class Ui_LabyrinthQt
{
public:
    QAction *actionNew_game;
    QAction *actionLoad_map;
    QAction *actionSave_map;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsScene *graphicsScene;
    QGraphicsView *graphicsView;
    QLabel *WelcomeText;
    QMenuBar *menuBar;
    QMenu *menuGame;
    QStatusBar *statusBar;
    QListWidget * listWidget;

    void setupUi(QMainWindow *LabyrinthQt)
    {
        if (LabyrinthQt->objectName().isEmpty())
            LabyrinthQt->setObjectName(QString::fromUtf8("LabyrinthQt"));
        LabyrinthQt->resize(408, 320);
        actionNew_game = new QAction(LabyrinthQt);
        actionNew_game->setObjectName(QString::fromUtf8("actionNew_game"));
        actionLoad_map = new QAction(LabyrinthQt);
        actionLoad_map->setObjectName(QString::fromUtf8("actionLoad_map"));
        actionSave_map = new QAction(LabyrinthQt);
        actionSave_map->setObjectName(QString::fromUtf8("actionSave_map"));
        actionExit = new QAction(LabyrinthQt);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(LabyrinthQt);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        WelcomeText = new QLabel(centralWidget);
        WelcomeText->setObjectName(QString::fromUtf8("WelcomeText"));
        WelcomeText->setEnabled(true);
        WelcomeText->setFrameShape(QFrame::NoFrame);
        WelcomeText->setAlignment(Qt::AlignCenter);
        graphicsScene = new QGraphicsScene;
        graphicsView = new QGraphicsView;
        graphicsView->setScene(graphicsScene);

        gridLayout->addWidget(WelcomeText, 0, 1, 1, 1);

        LabyrinthQt->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LabyrinthQt);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 408, 24));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QString::fromUtf8("menuGame"));
        LabyrinthQt->setMenuBar(menuBar);
        statusBar = new QStatusBar(LabyrinthQt);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LabyrinthQt->setStatusBar(statusBar);

        menuBar->addAction(menuGame->menuAction());
        menuGame->addAction(actionNew_game);
        menuGame->addAction(actionLoad_map);
        menuGame->addAction(actionSave_map);
        menuGame->addSeparator();
        menuGame->addAction(actionExit);

        listWidget= new QListWidget;
        retranslateUi(LabyrinthQt);

        QMetaObject::connectSlotsByName(LabyrinthQt);
    } // setupUi

    void retranslateUi(QMainWindow *LabyrinthQt)
    {
        LabyrinthQt->setWindowTitle("Labyrinth 2015");
        actionNew_game->setText("New game");
        actionLoad_map->setText("Load map");
        actionSave_map->setText("Save map");
        actionExit->setText("Exit");
        WelcomeText->setText("Welcome to the Labyrinth game\nTo start a new game press \"Game\" -> \"New game\"");
        menuGame->setTitle("Game");
    } // retranslateUi

};

namespace Ui {
    class LabyrinthQt: public Ui_LabyrinthQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABYRINTHQT_H
