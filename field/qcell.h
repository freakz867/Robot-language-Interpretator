#ifndef QCELL_H
#define QCELL_H

#include <QLabel>
//#include <QGraphicsView>

class QCell : public QLabel
{
    Q_OBJECT
public:
    QCell( QPoint position, QWidget *parent = 0 );
    QCell();
    QPoint _position;
    bool wall;
};

#endif // QCELL_H
