#ifndef QROBOT_H
#define QROBOT_H
#include <QSvgWidget>
#include "qlabyrinth.h"
#include <codecontext.h>
class QLabyrinth;
class Value;
class QRobot : public QSvgWidget
{
    Q_OBJECT
public:
    bool moveRobot();
    QPoint position();
    void setPosition( QPoint value );
    QLabyrinth *board();
    QRobot( QPoint position, QLabyrinth *board );
    int direction;                                  // like num keys: 2,4,8,6
    Value *getPan(int mood);
protected:
    QLabyrinth *labyrinth;
    QPoint currentPos;

};


#endif // QROBOT_H
