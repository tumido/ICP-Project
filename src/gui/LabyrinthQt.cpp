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
    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(onActionUndo()));

}

LabyrinthQt::~LabyrinthQt()
{
    delete ui;
}

/**
 * @brief Prepare game dialog
 * @return dialog closed correctly by OK button
 */
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


    QGraphicsScene * mainScene = ui->mainView->scene();
    this->clearVector(tiles, mainScene);
    this->clearVector(treasures, mainScene);
    this->clearVector(figures, mainScene);
    delete game;
    game = new GameManager;
    ui->rightPanelPlayers->layout()->removeWidget(ui->listWidget);
    delete ui->listWidget;
    ui->listWidget= new QListWidget;
    ui->listWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred );
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->rightPanelPlayers->layout()->addWidget(ui->listWidget);

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

void LabyrinthQt::finishedGame()
{
    // Create dialog for entering settings for new game
    QDialog done(this);
    QGridLayout * grid = new QGridLayout;
    done.setLayout(grid);
    QGroupBox box1(&done);
    QLabel header(&done);
    header.setText(QString("You've won, %1").arg(QString::fromStdString(game->getActive().getName())));
    header.setTextFormat(Qt::RichText);
    grid->addWidget(&header);
    grid->addWidget(&box1);
    box1.setTitle("Statistics");
    QGridLayout stat(&box1);

    // Add player's settings
    foreach(Player player, game->getAllPlayers())
    {
        QLabel * label = new QLabel(&box1);
        label->setText(QString("Player: %1\t%2").arg(QString::fromStdString(player.getName())).arg(player.getScore()));
        stat.addWidget(label);
    }

    // Add OK button
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok, Qt::Horizontal, &done);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &done, SLOT(accept()));
    grid->addWidget(&buttonBox);
    done.exec();
    return;
}

/**
 * @brief Helper funciton for cleaning interal vector
 * @param vect vector to be cleaned
 * @param scene where the items where drawn
 */
void LabyrinthQt::clearVector(vector<QGraphicsItem *> &vect, QGraphicsScene *&scene)
{
    foreach (QGraphicsItem * item, vect)
        scene->removeItem(item);
    vect.clear();
}

/**
 * @brief Function for board updating, destroys and recreates the scene (just tiles, treasures and figures)
 */
void LabyrinthQt::updateBoard()
{
    QGraphicsScene * mainScene = ui->mainView->scene();
    // Cleanup of our scene
    this->clearVector(tiles, mainScene);
    this->clearVector(treasures, mainScene);
    this->clearVector(figures, mainScene);

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
                QPixmap tile = QPixmap(QString(":/res/%1").arg(game->getTreasure(r,c)));
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
    // Draw players target
    ui->treasureScene->addPixmap(QPixmap(QString(":/res/%1").arg(1)));//game->getActive().getTreasure())));

    // Draw spare card
    QPixmap freeCard = QPixmap(QString(":/res/%1").arg(QString::fromStdString(game->getFreeCard())));
    QGraphicsPixmapItem * freeCardItem = ui->cardScene->addPixmap(freeCard);
    freeCardItem->setOffset(-(freeCard.width()/2), -(freeCard.height()/2));
    if (game->isFreeTreasure())
    {
        qDebug() << "Spare card has a treasure!";
        freeCard = QPixmap(QString(":/res/%1").arg(game->getFreeTreasure()));
        freeCardItem = ui->cardScene->addPixmap(freeCard);
        freeCardItem->setOffset(-(freeCard.width()/2), -(freeCard.height()/2));
    }
}

/**
 * @brief Simple funciton for toggling the arrows opacity (making them look disabled)
 */
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

/**
 * @brief Innitial board draw funciton, called only after new game start
 *
 * Builds arrows list
 */
void LabyrinthQt::drawBoard()
{
    QGraphicsScene * mainScene = ui->mainView->scene();
    this->clearVector(horizontalButtons, mainScene);
    this->clearVector(verticalButtons, mainScene);
    this->clearVector(tiles, mainScene);
    this->clearVector(treasures, mainScene);
    this->clearVector(figures, mainScene);
    delete mainScene;
    mainScene = new QGraphicsScene;
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

/**
 * @brief Innitiate placing of the spare card on main board
 * @param coord where the click was done in coordinates relative to mainScene
 */
void LabyrinthQt::placeCard(QPointF &coord)
{
    bool somethingHappened = false;
    int max = game->getSize();
    // determine which buttos were clicked
    for(unsigned i=0; i< horizontalButtons.size(); i++)
    {
        if (horizontalButtons[i]->contains(coord))
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
    for(unsigned i=0; i< verticalButtons.size(); i++)
    {
        if (verticalButtons[i]->contains(coord))
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
    // change was recorede, we need to reload board and hide arrows
    if (somethingHappened)
    {
        turnState = false;
        this->toggleArrows();
        ui->Hint->setText(QString("It's player <b>%1</b>'s turn<br><br>Please move your figure").arg(QString::fromStdString(game->getActive().getName())));
        this->updateBoard();
    }
}

/**
 * @brief Moves player after user's click action
 * @param coord where the click was done in coordinates relative to mainScene
 */
void LabyrinthQt::movePlayer(QPointF &coord)
{
    int max = game->getSize();
    // go through all tiles
    for (int r=0; r<max; r++ )
    {
        for (int c=0; c<max; c++)
        {
            // was tile clicked?
            if (tiles[r * max + c]->contains(coord))
            {
                int previousPlayer = game->getActiveIndex();
                qDebug() << "Clicked tile" << r << " " << c;
                // check if the player can move on this tile
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
                    return;
                }
            }
        }
    }
    if (game->isWon())
    {

    }
}


/**
 * @brief Users input -> mouse clicks
 *
 * Determines if the click was done in-game, on the rotate button of the spare card
 * or in the main game board and iniciates appropriate action
 * @param e the catched mouse event
 */
void LabyrinthQt::mousePressEvent(QMouseEvent *e)
{
    if (!game->isStarted() || game->isWon())
        return;
    qDebug() << "Mouse event";
    QPoint local_pt = ui->cardView->mapFromGlobal(e->globalPos());
    QPointF img_coord_pt = ui->cardView->mapToScene(local_pt);

    // If the click is for rotating the free card
    if (ui->rotateButton->contains(img_coord_pt))
    {
        qDebug() << "Rotating free card";
        game->turnFreeCard();
        this->updateBoard();
        return;
    }

    // else it's part of players's turn
    local_pt = ui->mainView->mapFromGlobal(e->globalPos());
    img_coord_pt = ui->mainView->mapToScene(local_pt);
    QString state = turnState ? "Place a card" : "Move player";
    qDebug() << "Current state of turn: " << state;

    if (turnState)
        this->placeCard(img_coord_pt);
    else
        this->movePlayer(img_coord_pt);
}

/**
 * @brief Start Game draws initial board and biulds players list (and sets first palyer as active)
 */
void LabyrinthQt::startGame()
{
    // Setup game Board
    this->setWindowState(Qt::WindowMaximized);
    this->drawBoard();
    this->turnState = true;

    // Build players List
    vector<std::string> players = game->getNames();
    for (unsigned i=0; i < players.size(); i++)
    {
        QListWidgetItem * entry = new QListWidgetItem(ui->listWidget);
        entry->setText(QString("Player%1: %2").arg(i + 1).arg(QString::fromStdString(players[i])));
        entry->setIcon(QIcon(QString(":/res/player%1").arg(i+1)));
        ui->listWidget->addItem(entry);
    }
    // Set Active Player
    ui->Hint->setText(QString("Game begun!<br>It's player <b>%1</b>'s turn<br><br>Please place the spare card").arg(QString::fromStdString(game->getActive().getName())));
    QFont font; font.setBold(true);
    ui->listWidget->item(game->getActiveIndex())->setFont(font);
}

/**
 * @brief Action Called after user's hit on Exit button in menu
 */
void LabyrinthQt::onActionExit()
{
    this->close();
}

/**
 * @brief Action Called after user's hit on New game button in menu
 *
 * Displays popup, prepares the layeot and starts the game
 */
void LabyrinthQt::onActionNewGame()
{
    // Shows the pregame setting window
    if (!this->prepareGame())
        return;
    // prepare UI
    this->prepareUI();

    // Starts game itself
    this->game->startGame();
    this->startGame();
}

void LabyrinthQt::prepareUI()
{
    ui->gridLayout->removeWidget(ui->WelcomeText);
    ui->gridLayout->addWidget(ui->mainView,0,0, 0, 1);
    ui->gridLayout->addWidget(ui->rightPanelPlayers, 0,1);
    ui->gridLayout->addWidget(ui->rightPanelCurrentTurn, 1, 1);
    ui->gridLayout->addWidget(ui->cardView,2,1);
}

/**
 * @brief Action Called after user's hit on Load button in menu, loads map
 */
void LabyrinthQt::onActionLoad()
{
    QString filter = "Game map (*.map)";
    QString filename = QFileDialog::getOpenFileName(this, "Load game", "", filter, &filter);
    if (filename == "")
        return;
    if (!game->load(filename.toStdString()))
        QMessageBox::critical(this, "Labyrint 2015", "Failed to load selected file");
    else
    {
        this->prepareUI();
        this->startGame();
    }
}

/**
 * @brief Action Called after user's hit on Save button in menu, saves map
 */
void LabyrinthQt::onActionSave()
{
    QString filter = "Game map (*.map)";
    QString filename = QFileDialog::getSaveFileName(this, "Save game", "", filter, &filter);
    if (!game->save(filename.toStdString()))
        QMessageBox::critical(this, "Labyrint 2015", "Failed to save to selected file");
}

void LabyrinthQt::onActionUndo()
{
    game->undo();
    this->updateBoard();
}
