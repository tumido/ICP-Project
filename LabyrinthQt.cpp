#include "clientgui.h"
#include "ui_clientgui.h"

clientGui::clientGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::clientGui)
{
    ui->setupUi(this);
}

clientGui::~clientGui()
{
    delete ui;
}
