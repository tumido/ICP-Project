#include "../../include/LabyrinthQt.h"
#include "../../include/ui_LabyrinthQt.h"


LabyrinthQt::LabyrinthQt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LabyrinthQt)
{
    ui->setupUi(this);
    game = new GameManager();

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
    size->setSingleStep(2);
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

    delete game;
    game = new GameManager;
    delete ui->listWidget;
    ui->listWidget= new QListWidget;
    ui->listWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred );
    for(int i = 0; i < MAX_PLAYERS; i++)
    {
        if (i < MIN_PLAYERS && players[i]->text() == "")
            players[i]->setText(QString("Player%1").arg(i + 1));
        qDebug() << "Player name set to " << players[i]->text();
        // add players to Game
        if (players[i]->text() == "")
            continue;
        if (!game->addPlayer(players[i]->text().toStdString()))
        {
            QMessageBox::critical(this,"Labyrinth 2015","Failed to add player");
            return false;
        }
    }
    // setup the game
    game->setSize(size->value());
    qDebug() << "Board size: input: " << size->value() << " internal: " << game->getSize();
    game->setTreasureCount(treasure->itemData(treasure->currentIndex()).toInt());
    qDebug() << "Treasure count: input: " << treasure->itemData(treasure->currentIndex()).toInt();

    return true;
}

void LabyrinthQt::drawBoard()
{
    int r,c;
    for (r=0; r < game->getSize(); r++)
        for (c=0; c < game->getSize(); c++)
        {
            QPixmap * tile = new QPixmap(QString(":/res/%1").arg(QString::fromStdString(game->getCardPath(r,c))));
            QGraphicsPixmapItem * tileItem = ui->graphicsScene->addPixmap(*tile);
            tileItem->setPos(r * (tile->width() + 5),c * (tile->height() + 5));
        }
    qDebug() << "Map shown " << QString("%1 x %2").arg(r).arg(c);

    vector<Player> players = game->getAllPlayers();
    for (unsigned i=0; i< players.size(); i++)
    {
        QPixmap * tile = new QPixmap(QString(":/res/player%1").arg(i));
        QGraphicsPixmapItem * tileItem = ui->graphicsScene->addPixmap(*tile);
        tileItem->setPos(players[i].row() * tile->width(), players[i].col() * tile->height());
        qDebug() << players[i].row() << players[i].col();
    }

    return;
}


void LabyrinthQt::startGame()
{
    this->game->startGame();
    this->setWindowState(Qt::WindowMaximized);
    this->drawBoard();

    vector<std::string> players = game->getNames();
    for (unsigned i=0; i< players.size(); i++)
    {
        QListWidgetItem * entry = new QListWidgetItem(ui->listWidget);
        entry->setText(QString("Player%1: %2").arg(i + 1).arg(QString::fromStdString(players[i])));
        ui->listWidget->addItem(entry);
    }
}

void LabyrinthQt::onActionExit()
{
    this->close();
}

void LabyrinthQt::onActionNewGame()
{
    // Shows the pregame setting window
    if (!this->prepareGame())
        return;
    // removes the WelcomeText
    ui->gridLayout->removeWidget(ui->WelcomeText);
    delete ui->WelcomeText;
    ui->gridLayout->addWidget(ui->graphicsView, 0, 0);
    ui->gridLayout->addWidget(ui->listWidget, 0,1);

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
