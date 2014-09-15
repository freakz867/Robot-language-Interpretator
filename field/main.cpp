#include "qgameplace.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabyrinthPlace w;
    w.show();
    
    return a.exec();
}
