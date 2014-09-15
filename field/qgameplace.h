#ifndef QGAMEPLACE_H
#define QGAMEPLACE_H
#include "qboardplace.h"
#include "qlabyrinth.h"
#include "qrobot.h"
#include <QMainWindow>
class QLabyrinth;
namespace Ui {
class QGamePlace;
}

class QGamePlace : public QMainWindow {
    Q_OBJECT
public:
    QGamePlace( QWidget *parent = 0 );
    ~QGamePlace();
    QLabyrinth *labyrinth;

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QGamePlace *ui;
    QBoardPlace *_boardPlace;

};


#endif // QGAMEPLACE_H
