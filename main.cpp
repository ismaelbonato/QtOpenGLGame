#include <QApplication>
#include <QDebug>


#include "MyGLWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyGLWidget Game;

    Game.resize(1280,720);
    Game.show();


    return a.exec();
}
