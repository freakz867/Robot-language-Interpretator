#include "qboardplace.h"

QBoardPlace::QBoardPlace(QWidget *parent) :
    QFrame(parent)
{
    this->setStyleSheet("background-color: #FFFFFF");
    this->setMinimumSize(800, 800);

}

void QBoardPlace::resizeEvent( QResizeEvent *event )
{
    int lesser = std::min( this->width(), this->height() );
    resize(lesser, lesser);
    int newX = ( static_cast<QWidget *>(parent())->width() - width() ) / 2;
    move( newX, y() );
}
