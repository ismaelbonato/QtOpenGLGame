#-------------------------------------------------
#
# Project created by QtCreator 2012-05-04T22:53:05
#
#
#   sudo apt-get install freeglut3 freeglut3-dev
#
#
#
#
#
#
#-------------------------------------------------

QT += widgets opengl 3dcore 3drender 3dinput 3dquick

TARGET = jogo
TEMPLATE = app

#LIBS = -lglut -lGLU
LIBS = -lGLU

LIBS += -L/usr/lib/x86_64-linux-gnu/mesa/
LIBS += -L/usr/bin/assimp

SOURCES += main.cpp\
    glwidget.cpp \
    camera.cpp

HEADERS  += \
    glwidget.h \
    camera.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc

