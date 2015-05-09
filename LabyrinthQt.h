#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QMainWindow>

namespace Ui {
class clientGui;
}

class clientGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientGui(QWidget *parent = 0);
    ~clientGui();

private:
    Ui::clientGui *ui;
};

#endif // CLIENTGUI_H
