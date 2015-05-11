/**
 * @file Ui_LabyrinthQt.h
 * @author Albert Uchytil (xuchyt03), Tomas Coufal (xcoufa09)
 * @brief Definition of layout of Qt's main window
 */
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
#include <QGroupBox>



QT_BEGIN_NAMESPACE

/// @brief Class defining the layout of Qt's front-end main window
class Ui_LabyrinthQt
{
public:
    QAction *actionNew_game;
    QAction *actionLoad_map;
    QAction *actionSave_map;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionStats;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGraphicsView *mainView;
    QGraphicsView *cardView;
    QGraphicsScene *cardScene;
    QLabel *WelcomeText;
    QLabel *Hint;
    QMenuBar *menuBar;
    QMenu *menuGame;
    QMenu *menuEdit;
    QStatusBar *statusBar;
    QListWidget * listWidget;
    QGraphicsPixmapItem *rotateButton;
    QGroupBox * rightPanelPlayers;
    QGroupBox * rightPanelCurrentTurn;
    QGraphicsView *treasureView;
    QGraphicsScene *treasureScene;

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
        actionUndo = new QAction(LabyrinthQt);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionStats = new QAction(LabyrinthQt);
        actionStats->setObjectName(QString::fromUtf8("actionStats"));
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
        mainView = new QGraphicsView;
        mainView->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
        rightPanelPlayers = new QGroupBox;
        QGridLayout * lp = new QGridLayout(rightPanelPlayers);
        rightPanelCurrentTurn = new QGroupBox;
        QGridLayout * lt = new QGridLayout(rightPanelCurrentTurn);
        cardView = new QGraphicsView;
        cardView->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
        cardScene = new QGraphicsScene;
        cardView->setScene(cardScene);
        QPixmap rotate = QPixmap(":/res/rotate");
        rotateButton = cardScene->addPixmap(rotate);
        rotateButton->setOffset(-rotate.width()/2, -rotate.height()/2);
        treasureView = new QGraphicsView;
        treasureView->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
        treasureScene = new QGraphicsScene;
        treasureView->setScene(treasureScene);

        gridLayout->addWidget(WelcomeText, 0, 1, 1, 1);

        LabyrinthQt->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LabyrinthQt);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 408, 24));
        menuGame = new QMenu(menuBar);
        menuGame->setObjectName(QString::fromUtf8("menuGame"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        LabyrinthQt->setMenuBar(menuBar);
        statusBar = new QStatusBar(LabyrinthQt);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LabyrinthQt->setStatusBar(statusBar);

        menuBar->addAction(menuGame->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuGame->addAction(actionNew_game);
        menuGame->addAction(actionLoad_map);
        menuGame->addAction(actionSave_map);
        menuGame->addSeparator();
        menuGame->addAction(actionExit);

        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionStats);

        listWidget= new QListWidget(rightPanelPlayers);

        Hint = new QLabel("Game began!", rightPanelCurrentTurn);
        Hint->setAlignment(Qt::AlignCenter);
        Hint->setTextFormat(Qt::RichText);
        Hint->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred );
        QLabel * target = new QLabel("You are looking for: ", rightPanelCurrentTurn);
        target->setAlignment(Qt::AlignCenter);
        target->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        rightPanelPlayers->setTitle("List of players");
        lp->addWidget(listWidget);
        rightPanelPlayers->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred );

        rightPanelCurrentTurn->setTitle("Current turn");
        lt->addWidget(Hint, 0, 0, 1, 0);
        lt->addWidget(target, 1, 0);
        lt->addWidget(treasureView, 1, 1);

        rightPanelCurrentTurn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred );

        actionStats->setDisabled(true);
        actionUndo->setDisabled(true);
        actionSave_map->setDisabled(true);

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
        actionUndo->setText("Undo");
        actionStats->setText("Statistics pop-up");
        WelcomeText->setText("Welcome to the Labyrinth game\nTo start a new game press \"Game\" -> \"New game\"");
        menuGame->setTitle("Game");
        menuEdit->setTitle("Edit");
    } // retranslateUi

};

/// @brief Namespace for Qt GUI
namespace Ui {
    class LabyrinthQt: public Ui_LabyrinthQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABYRINTHQT_H
