#ifndef CAMERA_H
#define CAMERA_H

#include "glwidget.h"
#include "math.h"
//#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library
#include <QCursor>


#define CAMERASPEED	0.03f				// The Camera Speed
#define LATERALSPEED    0.02f



typedef struct tVector3					// expanded 3D vector struct
{
        tVector3() {}	// constructor
        tVector3 (float new_x, float new_y, float new_z) // initialize constructor
        {x = new_x; y = new_y; z = new_z;}
        // overload + operator so that we easier can add vectors
        tVector3 operator+(tVector3 vVector) {return tVector3(vVector.x+x, vVector.y+y, vVector.z+z);}
        // overload - operator that we easier can subtract vectors
        tVector3 operator-(tVector3 vVector) {return tVector3(x-vVector.x, y-vVector.y, z-vVector.z);}
        // overload * operator that we easier can multiply by scalars
        tVector3 operator*(float number)	 {return tVector3(x*number, y*number, z*number);}
        // overload / operator that we easier can divide by a scalar
        tVector3 operator/(float number)	 {return tVector3(x/number, y/number, z/number);}

        float x, y, z;						// 3D vector coordinates
}tVector3;

class camera
{
public:

    camera();
    QCursor cursor;
    tVector3 mPos;
    tVector3 mView;
    tVector3 mUp;


//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////
    int mWindowWidth;
    int mWindowHeight;


                // This function let you control the camera with the mouse
    int Mouse_Move();

//NEW//////////////////NEW//////////////////NEW//////////////////NEW////////////////

    void Move_Lateral_Camera(float lateralspeed);
    void Rotate_View(float x, float y, float z);
     void Move_Camera(float cameraspeed);
     void Position_Camera(float pos_x, float pos_y,float pos_z,
                                                         float view_x, float view_y, float view_z,
                                                         float up_x,   float up_y,   float up_z);

};

#endif // CAMERA_H
