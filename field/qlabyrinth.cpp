#include "qlabyrinth.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

QLabyrinth::QLabyrinth(QWidget *parent) :
    QWidget(parent)
{
    // creating layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(25);
    layout->addWidget(this); // adding place
    parent->setLayout(layout); // setting layout for QBoardPlace
    readLabyrinth();
    positionCells();
    drawCells();
}

void QLabyrinth::readLabyrinth(){
    ifstream file;
    file.open("labyrinth.map", ios::in);
    int newx,newy;
    file >> newx >> newy;
    file >> newx >> newy;
    (*this).x=newx;
    (*this).y=newy;
    cout << x << '\n' << y << '\n';
    file.close();
}


void QLabyrinth::positionCells()
{
    QGridLayout *grid_layout = new QGridLayout(this);

        grid_layout->setSpacing(0);
        grid_layout->setMargin(0);
        Cells = new QCell *[y];
        for (int i = 0; i < y; i++) {
            Cells[i]= new QCell [x];
            for (int j = 0; j < x; j++) {
                Cells[i][j].setParent(this);
                Cells[i][j]._position.setX(j);
                Cells[i][j]._position.setY(i);
                grid_layout->addWidget(&Cells[i][j], j, i);
            }
        }

        setLayout(grid_layout);
        //Cells[10][0].setStyleSheet("background-color: #cccccc;");
}

void QLabyrinth::drawCells()
{
    vector<string> vec; //для строк из файла
    ifstream file;
    file.open("labyrinth.map", ios::in);

    int newx,newy,startx,starty;
    string temp;
    file >> startx >> starty;
    file >> newx >> newy;
    (*this).x=newx;
    (*this).y=newy;
    cout << x << '\n' << y << '\n';

    while (getline(file, temp))
        vec.push_back(temp);


    //positionCells();
    char curr;
    for (int i = 1; i < y+1; i++){
        //cout << vec[i] << '\n';
        for(int j=0; j < x; j++){
            string temp2(vec[i]);
            curr=temp2[j];
            if (curr=='0'){
                Cells[i-1][j].setStyleSheet("background-color: #cccccc;");
                Cells[i-1][j].wall=true;
            }
            else{
                Cells[i-1][j].setStyleSheet("background-color: #ffffff;");
                Cells[i-1][j].wall=false;
            }
        }
    }
    cout << endl;
}

QLabyrinth::~QLabyrinth(){
    for (int count = 0; count < y; count++)
            delete []Cells[count];
}
