#include "qgameplace.h"
#include "ui_qgameplace.h"

QGamePlace::QGamePlace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QGamePlace)
{
    ui->setupUi(this);
    _boardPlace = new QBoardPlace(this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_boardPlace);
    ui->centralWidget->setLayout(layout);

    labyrinth = new QLabyrinth(_boardPlace);
}

void QGamePlace::changeEvent(QEvent *e){

}

QGamePlace::~QGamePlace()
{
    delete ui;
}
