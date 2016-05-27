#include <QApplication>
#include <QDebug>


#include "glwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GLWidget Game;

    Game.resize(1280,720);
    Game.show();


    return a.exec();
}