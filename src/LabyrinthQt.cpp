#include "../include/LabyrinthQt.h"
#include "ui_LabyrinthQt.h"


LabyrinthQt::LabyrinthQt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LabyrinthQt)
{
    ui->setupUi(this);

    connect(ui->actionNew_game, SIGNAL(triggered()), this, SLOT(onActionNewGame()));
    connect(ui->actionLoad_map, SIGNAL(triggered()), this, SLOT(onActionLoad()));
    connect(ui->actionSave_map, SIGNAL(triggered()), this, SLOT(onActionSave()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(onActionExit()));
}

LabyrinthQt::~LabyrinthQt()
{
    delete ui;
}

bool LabyrinthQt::prepareGame()
{
    // Create dialog for entering settings for new game
    QDialog settings(this);
    QGridLayout * grid = new QGridLayout;
    settings.setLayout(grid);
    QGroupBox box1(&settings);
    grid->addWidget(&box1);
    box1.setTitle("Players");
    QFormLayout form1(&box1);

    // Add player's settings
    QList<QLineEdit *> players;
    for(int i = 0; i < MAX_PLAYERS; ++i)
    {
        QLineEdit *line = new QLineEdit(&settings);
        line->setPlaceholderText("Name");
        line->setToolTip("If not set, the default value is used");
        QString label = QString("Player %1:").arg(i + 1);
        form1.addRow(label, line);
        players << line;
    }

    // Game settings
    QGroupBox box2(&settings);
    grid->addWidget(&box2);
    box2.setTitle("Game Settings");
    QFormLayout form2(&box2);
    // Add Labyrinth size settings
    QSpinBox * size = new QSpinBox(&settings);
    size->setRange(BOARD_MIN, BOARD_MAX);
    size->setValue(BOARD_DEFAULT);
    form2.addRow(QString("Board size:"), size);

    // Add treasure count
    QComboBox * treasure = new QComboBox;
    treasure->addItem("12", QVariant(12));
    treasure->addItem("24", QVariant(24));
    form2.addRow(QString("Treasure count:"), treasure);
    // Add Cancel and OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &settings);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &settings, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &settings, SLOT(reject()));
    grid->addWidget(&buttonBox);


    // Parse data
    if (settings.exec() != QDialog::Accepted)
        return false;
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        if (i < MIN_PLAYERS && players[i]->text() == "")
            players[i]->setText(QString("Player%1").arg(i + 1));
        qDebug() << "Player name set to " << players[i]->text();
        // add players to Game
    }
    // setup the game
    qDebug() << "Board size set to " << size->value();
    qDebug() << "Treasure count is " << treasure->itemData(treasure->currentIndex()).toInt();
    return true;
}

void LabyrinthQt::startGame()
{
    QLabel * tile = new QLabel;
    for (int r=0; r<3; r++)
        for (int c=0; c<0; c++)
        {
            tile->setPixmap(QPixmap("../res/0110.png"));
            ui->gridLayout->addWidget(tile, r, c);
        }
    return;
}

void LabyrinthQt::onActionExit()
{
    this->close();
}

void LabyrinthQt::onActionNewGame()
{
    // Shows the pregame setting window
    bool ok = this->prepareGame();
    if (!ok)
        return;
    // removes the WelcomeText
    ui->gridLayout->removeWidget(ui->WelcomeText);
    delete ui->WelcomeText;

    // Starts game itself
    this->startGame();
}

void LabyrinthQt::onActionLoad()
{
    return;
}

void LabyrinthQt::onActionSave()
{
    return;
}
