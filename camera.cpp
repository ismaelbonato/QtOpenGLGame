#include "camera.h"


camera::camera()
{
}
 /////////////////////////////////////////////////////////////////////////////////////////////////
 //	THE CCAMERA POSITION CAMERA
 /////////////////////////////////////////////////////////////////////////////////////////////////}
void camera::Position_Camera(float pos_x,  float pos_y,  float pos_z,
                            float view_x, float view_y, float view_z,
                              float up_x,   float up_y,   float up_z)
{
        tVector3 vPos	= tVector3(pos_x,  pos_y,  pos_z);
        tVector3 vView	= tVector3(view_x, view_y, view_z);
        tVector3 vUp	= tVector3(up_x,   up_y,   up_z);

        mPos  = vPos;							// set the position
        mView = vView;							// set the view
        mUp   = vUp;							// set the up vector
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//	THE CCAMERA MOVE CAMERA lateral
/////////////////////////////////////////////////////////////////////////////////////////////////
void camera::Move_Lateral_Camera(float lateralspeed)
{
    tVector3 vVector = mView - mPos;	// Get the view vector
            tVector3 vOrthoVector;              // Orthogonal vector for the view vector

            vOrthoVector.x = -vVector.z;
            vOrthoVector.z =  vVector.x;

            // left positive cameraspeed and right negative -cameraspeed.
            mPos.x  = mPos.x  + vOrthoVector.x * lateralspeed;
            mPos.z  = mPos.z  + vOrthoVector.z * lateralspeed;
            mView.x = mView.x + vOrthoVector.x * lateralspeed;
            mView.z = mView.z + vOrthoVector.z * lateralspeed;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//	THE CCAMERA MOVE CAMERA
/////////////////////////////////////////////////////////////////////////////////////////////////
void camera::Move_Camera(float cameraspeed)
{
        tVector3 vVector = tVector3(0,0,0);		// init a new view vector
        vVector = mView - mPos;					// Get the view vector

         //forward positive cameraspeed and backward negative -cameraspeed.
        mPos.x  = mPos.x  + vVector.x * cameraspeed;
        mPos.y  = mPos.y  + vVector.y * cameraspeed;/////
        mPos.z  = mPos.z  + vVector.z * cameraspeed;

        mView.x = mView.x + vVector.x * cameraspeed;
        mView.y = mView.y + vVector.y * cameraspeed;/////
        mView.z = mView.z + vVector.z * cameraspeed;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//	THE CCAMERA ROTATE VIEW
/////////////////////////////////////////////////////////////////////////////////////////////////
void camera::Rotate_View(float x, float y, float z)
{
        tVector3 vVector = mView - mPos;

        if(x)
        {
                mView.z = (float)(mPos.z + sin(x)*vVector.y + cos(x)*vVector.z);
                mView.y = (float)(mPos.y + cos(x)*vVector.y - sin(x)*vVector.z);
        }
        if(y)
        {
                mView.z = (float)(mPos.z + sin(y)*vVector.x + cos(y)*vVector.z);
                mView.x = (float)(mPos.x + cos(y)*vVector.x - sin(y)*vVector.z);
        }
        if(z)
        {
                mView.x = (float)(mPos.x + sin(z)*vVector.y + cos(z)*vVector.x);
                mView.y = (float)(mPos.y + cos(z)*vVector.y - sin(z)*vVector.x);
        }
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//	THE CCAMERA MOUSE MOVE
/////////////////////////////////////////////////////////////////////////////////////////////////
int camera::Mouse_Move()
{

    QPoint mousePos = cursor.pos();
    int mid_x = 1920  >> 1;
    int mid_y = 1080  >> 1;
    float angle_y  = 0.0f;
    float angle_z  = 0.0f;

    //GetCursorPos(&mousePos);	// Get the 2D mouse cursor (x,y) position

    if( (mousePos.x() == mid_x) && (mousePos.y() == mid_y) ) return 0;

    //SetCursorPos(mid_x, mid_y);	// Set the mouse cursor in the middle of the window

    cursor.setPos( mid_x, mid_y );

    // Get the direction from the mouse, and bring the number down to a reasonable amount
    angle_y = (float)( (mid_x - mousePos.x()) ) / 1000;
    angle_z = (float)( (mid_y - mousePos.y()) ) / 1000;

    // The higher the number(acceleration) is the faster the camera looks around.
    mView.y += angle_z * 2;

    // limit the rotation around the x-axis
    if((mView.y - mPos.y) > 8)  mView.y = mPos.y + 8;
    if((mView.y - mPos.y) <-8)  mView.y = mPos.y - 8;

    Rotate_View(0, -angle_y, 0); // Rotate

    return 0;
}
