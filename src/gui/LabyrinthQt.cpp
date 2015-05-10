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
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
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

void LabyrinthQt::updateBoard()
{
    QGraphicsScene * mainScene = ui->mainView->scene();
    // Cleanup of our scene
    foreach (QGraphicsItem * tile, tiles)
        mainScene->removeItem(tile);
    tiles.clear();
    foreach (QGraphicsItem * tr, treasures)
        mainScene->removeItem(tr);
    treasures.clear();
    foreach (QGraphicsItem * fig, figures)
        mainScene->removeItem(fig);
    figures.clear();

    // Draw board again
    for (int r=0; r < game->getSize(); r++)
        for (int c=0; c < game->getSize(); c++)
        {
            QPixmap tile = QPixmap(QString(":/res/%1").arg(QString::fromStdString(game->getCardPath(r,c))));
            QGraphicsPixmapItem * tileItem = mainScene->addPixmap(tile);
            tileItem->setOffset(r * (tile.width() + SPACING),c * (tile.height() + SPACING));
            tiles.push_back(tileItem);
            if (game->isTreasure(r,c))
            {
                QPixmap tile = QPixmap(QString(":/res/treasure"));
                QGraphicsPixmapItem * tileItem = mainScene->addPixmap(tile);
                tileItem->setOffset(r * (tile.width() + SPACING),c * (tile.height() + SPACING));
                treasures.push_back(tileItem);
            }
        }

    // Draw players
    vector<Player> players = game->getAllPlayers();
    for (unsigned i=0; i < players.size(); i++)
    {
        QPixmap tile = QPixmap(QString(":/res/player%1").arg(i+1));
        QGraphicsPixmapItem * tileItem = mainScene->addPixmap(tile);
        tileItem->setOffset(players[i].row() * (tile.width() + SPACING), players[i].col() * (tile.height() + SPACING));
        qDebug() << "Player possition set " << players[i].row() << players[i].col();
        figures.push_back(tileItem);
    }
    QPixmap freeCard = QPixmap(QString(":/res/%1").arg(QString::fromStdString(game->getFreeCard())));
    ui->cardScene->addPixmap(freeCard);
}

void LabyrinthQt::toggleArrows()
{
    bool toggle = horizontalButtons[0]->opacity() == 1;
    foreach (QGraphicsItem *arrow, horizontalButtons) {
        arrow->setOpacity(toggle ? 0.5 : 1);
    }
    foreach (QGraphicsItem *arrow, verticalButtons) {
        arrow->setOpacity(toggle ? 0.5 : 1);
    }
}

void LabyrinthQt::drawBoard()
{
    QGraphicsScene * mainScene = new QGraphicsScene;
    ui->mainView->setScene(mainScene);
    this->updateBoard();
    int r,c = game->getSize();
    for (r=1; r < game->getSize(); r += 2)
    {
        QPixmap tile = QPixmap(QString(":/res/^"));
        QGraphicsPixmapItem * tileItem = mainScene->addPixmap(tile);
        tileItem->setOffset(r * (tile.width() + SPACING),c * (tile.height() + SPACING));
        tileItem->setToolTip(QString("index %1").arg(horizontalButtons.size()));
        horizontalButtons.push_back(tileItem);
        tile = QPixmap(QString(":/res/v"));
        tileItem = mainScene->addPixmap(tile);
        tileItem->setOffset(r * (tile.width() + SPACING), -(tile.width() + SPACING));
        tileItem->setToolTip(QString("index %1").arg(horizontalButtons.size()));
        horizontalButtons.push_back(tileItem);
    }
    for (c=1; c < game->getSize(); c += 2)
    {
        QPixmap tile = QPixmap(QString(":/res/<"));
        QGraphicsPixmapItem * tileItem = mainScene->addPixmap(tile);
        tileItem->setOffset(r * (tile.width() + SPACING),c * (tile.height() + SPACING));
        tileItem->setToolTip(QString("index %1").arg(verticalButtons.size()));
        verticalButtons.push_back(tileItem);
        tile = QPixmap(QString(":/res/>"));
        tileItem = mainScene->addPixmap(tile);
        tileItem->setOffset(-(tile.width() + SPACING), c * (tile.width() + SPACING));
        tileItem->setToolTip(QString("index %1").arg(verticalButtons.size()));
        verticalButtons.push_back(tileItem);
    }
    qDebug() << "Map shown " << QString("%1 x %2").arg(r).arg(c);

    return;
}

void LabyrinthQt::mousePressEvent(QMouseEvent *e)
{
    if (!game->isStarted())
        return;
    QPoint local_pt = ui->mainView->mapFromGlobal(e->globalPos());
    QPointF img_coord_pt = ui->mainView->mapToScene(local_pt);
    int max = game->getSize();
    QString state = turnState ? "Place a card" : "Move player";
    qDebug() << "Current state of turn: " << state;
    bool somethingHappened = false;
    if (turnState)
    {
        for(int i=0; i< horizontalButtons.size(); i++)
        {
            if (horizontalButtons[i]->contains(img_coord_pt))
            {
                qDebug() << "Button " << i << " for adding a card pressed";
                int r = i % 2 == 0 ? i + 1 : i;
                int c = i % 2 == 0 ? max-1 : 0;
                game->moveCard(r,c);
                qDebug() << "Card moved to into row " << r << " " << c;
                somethingHappened = true;
                break;
            }
        }
        for(int i=0; i< verticalButtons.size(); i++)
        {
            if (verticalButtons[i]->contains(img_coord_pt))
            {
                qDebug() << "Button " << i << " for adding a card pressed";
                int r = i % 2 == 0 ? max-1 : 0;
                int c = i % 2 == 0 ? i + 1 : i;
                game->moveCard(r,c);
                qDebug() << "Card moved to into column " << r << " " << c;
                somethingHappened = true;
                break;
            }
        }
        if (somethingHappened)
        {
            turnState = false;
            this->toggleArrows();
            ui->Hint->setText(QString("It's player <b>%1</b>'s turn<br><br>Please move your figure").arg(QString::fromStdString(game->getActive().getName())));
            this->updateBoard();
        }
    } else
    {
        for (int r=0; r<max; r++ )
        {
            if (turnState)
                break;
            for (int c=0; c<max; c++)
            {
                if (tiles[r * max + c]->contains(img_coord_pt))
                {
                    int previousPlayer = game->getActiveIndex();
                    qDebug() << "Clicked tile" << r << " " << c;
                    if (game->movePlayer(r,c))
                    {
                        turnState = true;
                        this->toggleArrows();
                        ui->Hint->setText(QString("It's player <b>%1</b>'s turn<br><br>Please place the spare card").arg(QString::fromStdString(game->getActive().getName())));
                        QFont font; font.setBold(true);
                        ui->listWidget->item(game->getActiveIndex())->setFont(font);
                        font.setBold(false);
                        ui->listWidget->item(previousPlayer)->setFont(font);
                        this->updateBoard();
                        break;
                    }
                }
            }
        }
    }
}


void LabyrinthQt::startGame()
{
    // Setup game Board
    this->game->startGame();
    this->setWindowState(Qt::WindowMaximized);
    this->drawBoard();
    this->turnState = true;

    // Buid players List
    vector<std::string> players = game->getNames();
    for (unsigned i=0; i < players.size(); i++)
    {
        QListWidgetItem * entry = new QListWidgetItem(ui->listWidget);
        entry->setText(QString("Player%1: %2").arg(i + 1).arg(QString::fromStdString(players[i])));
        entry->setIcon(QIcon(QString(":/res/player%1").arg(i+1)));
        ui->listWidget->addItem(entry);
    }
    // Set Active Player
    ui->Hint->setText(QString("Game began!<br>It's player <b>%1</b>'s turn<br><br>Please place the spare card").arg(QString::fromStdString(game->getActive().getName())));
    QFont font; font.setBold(true);
    ui->listWidget->item(game->getActiveIndex())->setFont(font);
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
    ui->gridLayout->addWidget(ui->mainView,0,0, 0, 1);
    ui->gridLayout->addWidget(ui->listWidget, 0,1);
    ui->gridLayout->addWidget(ui->Hint, 1, 1);
    ui->gridLayout->addWidget(ui->cardView,2,1);

    // Starts game itself
    this->startGame();
}

void LabyrinthQt::onActionLoad()
{
    QString filename = QFileDialog::getOpenFileName(this, "Load game");
    if (!game->load(filename.toStdString()))
        QMessageBox::critical(this, "Labyrint 2015", "Failed to load selected file");
}

void LabyrinthQt::onActionSave()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save game");
    if (!game->save(filename.toStdString()))
        QMessageBox::critical(this, "Labyrint 2015", "Failed to save to selected file");
}
