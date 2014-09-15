#include "qcell.h"
#include <QVBoxLayout>
QCell::QCell(){

}

QCell::QCell( QPoint position, QWidget *parent ):QLabel( parent )
{
    _position = position;
    /*QVBoxLayout *newLayout=new QVBoxLayout;
    (*this).setLayout(newLayout);*/
}
