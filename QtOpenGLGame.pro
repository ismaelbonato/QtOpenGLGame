QT += widgets
QT += opengl


TARGET = QtOpenGLGame
TEMPLATE = app

LIBS = -lGLU
LIBS += -lassimp

#LIBS += -L/usr/lib/x86_64-linux-gnu/mesa/
#LIBS += -L/usr/bin/assimp


SOURCES += main.cpp \
    camera.cpp \
    MyGLWidget.cpp \
    ModelLoader.cpp

RESOURCES += \
    res.qrc

HEADERS += \
    camera.h \
    MyGLWidget.h \
    ModelLoader.h
