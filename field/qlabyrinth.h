#ifndef QBOARD_H
#define QBOARD_H
#include "qrobot.h"
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QGridLayout>

class QCell;
class QRobot;

class QLabyrinth : public QWidget
{
Q_OBJECT
public:
    QCell **Cells;
    QLabyrinth(QWidget *parent = 0);
    ~QLabyrinth();
    void drawCells();
    void readLabyrinth();
    int x,y;

private:
    void positionCells();
};

#include "qcell.h"

#endif // QBOARD_H
