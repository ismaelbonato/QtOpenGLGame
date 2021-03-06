#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLTexture>

#include <QGLWidget>
#include <QtOpenGL>
#include <QTime>

#include <camera.h>

#include <QHash>
#include <QKeyEvent>

class QTimer;

typedef struct
{
        double x;
        double y;
        double z;
} Vector;

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:


    Vector Buf[64][64];
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();
protected:
    void DefineLuzDIFUSA();
    void DefineLuzESPECULAR();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    //void mouseMoveEvent(QMouseEvent* event);
    void initializeGL();
    void paintGL();
    void resizeGL(int width,int height);
    void Keyboard_Operations();
    //bool eventFilter(QObject *obj, QEvent *event);

private:
    void drawCube();
    void terra();
    QTimer *timer;
    QTime time;
    GLuint texture[3];
    char rot;

    bool lightChanged, filterChanged;
    int changeAmount;

    QHash<GLuint, QString> filterName;

};

#endif // GLWIDGET_Hww
