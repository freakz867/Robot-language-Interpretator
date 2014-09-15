#include "qrobot.h"
#include <QString>
#include <linux/sched.h>
#include <unistd.h>
#include <QTime>
#include <QEventLoop>
#include <QCoreApplication>
using namespace std;


QRobot::QRobot( QPoint position, QLabyrinth *board ):QSvgWidget(board),labyrinth(board){
    QString rname=":robot.svg";
    load(rname);
    setPosition(position);
    direction=2;
}

QPoint QRobot::position(){
    return currentPos;
}
void delay(int pauseTime)
{
    QTime dieTime= QTime::currentTime().addSecs(pauseTime);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool QRobot::moveRobot(){
    delay(1);
    cout<<"Moving in direction "<<direction<<endl;
    QPoint newPosition(currentPos.x(),currentPos.y());
    if(direction==2)
        newPosition.setY(currentPos.y()+1);
    if(direction==8)
        newPosition.setY(currentPos.y()-1);
    if(direction==4)
        newPosition.setX(currentPos.x()-1);
    if(direction==6)
        newPosition.setX(currentPos.x()+1);
    setPosition( newPosition );
}

Value *QRobot::getPan(int mood){
        cout<<"Current coordinates: "<<currentPos.x()<<" "<<currentPos.y()<<endl;

    QPoint leftEdge,rightEdge;
    if(mood==1){
        leftEdge.setX(currentPos.x()-1);
        leftEdge.setY(currentPos.y()-1);
        rightEdge.setX(currentPos.x()+1);
        rightEdge.setY(currentPos.y()+1);
    }
    int ndim=9;
    int *dim=new int [ndim];
    for(int i=0; i<ndim; ++i)
        dim[i]=3;
    Value *result=new Value(1,0,ndim,dim);
    int count_row=0,counter=0,x,y,wall;
    for (count_row; count_row < 3; count_row++){
        for (int count_column = 0; count_column < dim[count_row]; count_column++){
                if(labyrinth->Cells[ currentPos.x()+count_column-mood][ currentPos.y()-(mood-count_row)].wall==true)
                    wall=1;
                else
                    wall=2;
                result->data[counter][0] = count_column-mood;
                result->data[counter][1] = mood-count_row;
                result->data[counter][2] = wall;
                ++counter;
            //}
        }
    }
    return result;
}

QLabyrinth *QRobot::board(){
    return labyrinth;
}

void QRobot::setPosition( QPoint value ){

    if(labyrinth->Cells[ value.x() ][ value.y() ].wall==false){
    currentPos = value;
        QWidget* parentWidget =  &labyrinth->Cells[ value.x() ][ value.y() ];
    //parentWidget->setStyleSheet("background-color: #ca04cc;");
    if (parentWidget->layout()) {
        parentWidget->layout()->addWidget(this);
    }
    else {
        QVBoxLayout *layout = new QVBoxLayout(parentWidget);
        layout->setMargin(0);
        layout->addWidget(this);
        parentWidget->setLayout(layout);
    }

    this->setParent( &labyrinth->Cells[value.x()][value.y()] );
    }
    else{
        QWidget* parentWidget =  &labyrinth->Cells[ currentPos.x() ][ currentPos.y() ];
        parentWidget->setStyleSheet("background-color: #FF0000;");
        delay(3);
        exit(0);
    }
}
