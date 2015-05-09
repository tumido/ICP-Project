#ifndef UI_LABYRINTHQT_H
#define UI_LABYRINTHQT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>



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
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

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
        mainToolBar = new QToolBar(LabyrinthQt);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        LabyrinthQt->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LabyrinthQt);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LabyrinthQt->setStatusBar(statusBar);

        menuBar->addAction(menuGame->menuAction());
        menuGame->addAction(actionNew_game);
        menuGame->addAction(actionLoad_map);
        menuGame->addAction(actionSave_map);
        menuGame->addSeparator();
        menuGame->addAction(actionExit);

        retranslateUi(LabyrinthQt);

        QMetaObject::connectSlotsByName(LabyrinthQt);
    } // setupUi

    void retranslateUi(QMainWindow *LabyrinthQt)
    {
        LabyrinthQt->setWindowTitle(QApplication::translate("LabyrinthQt", "Labyrinth 2015", 0, QApplication::UnicodeUTF8));
        actionNew_game->setText(QApplication::translate("LabyrinthQt", "New game", 0, QApplication::UnicodeUTF8));
        actionLoad_map->setText(QApplication::translate("LabyrinthQt", "Load map", 0, QApplication::UnicodeUTF8));
        actionSave_map->setText(QApplication::translate("LabyrinthQt", "Save map", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("LabyrinthQt", "Exit", 0, QApplication::UnicodeUTF8));
        WelcomeText->setText(QApplication::translate("LabyrinthQt", "Welcome to the Labyrinth game\n"
"To start a new game press \"Game\" -> \"New game\"", 0, QApplication::UnicodeUTF8));
        menuGame->setTitle(QApplication::translate("LabyrinthQt", "Game", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LabyrinthQt: public Ui_LabyrinthQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABYRINTHQT_H
