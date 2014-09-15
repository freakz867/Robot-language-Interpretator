#ifndef QBOARDPLACE_H
#define QBOARDPLACE_H

#include <QWidget>
#include <QFrame>

class QBoardPlace : public QFrame
{
Q_OBJECT
public:
    QBoardPlace( QWidget *parent = 0 );
    virtual void resizeEvent( QResizeEvent *event );

};
#endif // QBOARDPLACE_H
