#include "MyGLWidget.h"
#include <QMessageBox>
#include <QStatusBar>
#include <QMouseEvent>
#include <QApplication>
#include "GL/glu.h"

camera Camera;

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
      //qApp->installEventFilter(this);
        setWindowTitle("Jogo");
        time = QTime::currentTime();
        timer = new QTimer(this);
        timer->setSingleShot(true);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
}
// Destructor
GLWidget::~GLWidget() {
         glDeleteTextures(1, texture);
}
void GLWidget::initializeGL(){

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);


    //glClearColor(0.2,0.2,0.2,1);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations



    Camera.Position_Camera(0, 0.5f, 5,	0, 0.5f, 0,   0, 1, 0);

    QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));

    //Auto = new MilkshapeModel();									// Memory To Hold The Model
   //        if ( Auto->loadModelData( "Auto.ms3d" ) == false )		// Loads The Model And Checks For Errors
            {

                //int ret = QMessageBox::warning(this, tr(""),tr("erro ao carregar modelo"), QMessageBox::Cancel);
            }


         // Carregando textura do pizo.
         glShadeModel(GL_SMOOTH);
         QImage img = convertToGLFormat(QImage(":/img/Concreto2.jpg"));
         glGenTextures(1, &texture[0]);

         glBindTexture( GL_TEXTURE_2D, texture[0] );
        // Texture using mipmaps
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


          gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img.width(), img.height(), GL_RGBA, GL_UNSIGNED_BYTE, img.bits());


         QImage b;

         // carregando textura da caixa de madeira.

         if ( !b.load( ":/img/Crate.bmp"))
         {
               //qWarning( "Could not read image file, using single-color instead." );
               b = QImage( 16, 16, QImage::Format_RGB888 );
               b.fill( QColor(Qt::green).rgb() );
         }
         img = convertToGLFormat(b);
         glGenTextures(1, &texture[1]);
         glBindTexture( GL_TEXTURE_2D, texture[1] );

         glTexImage2D( GL_TEXTURE_2D, 0, 3, img.width(), img.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, img.bits() );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );


         //Luz avermelhada (sala com lava?)
         GLfloat ambientLight[] = {1.0f, 1.0f, 1.0f, 1.0f};

         //Habilitamos a capacidade de ilumina??o
         glEnable(GL_LIGHTING);

         //Configuramos a OpenGL para utilizar como luz ambiente global
         //a ilumina??o definida por ambientLight[]
         glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);


}
void GLWidget::resizeGL(int width,int height){

    glViewport( 0, 0, (GLint)width, (GLint)height );

                    glMatrixMode(GL_PROJECTION);
                    glLoadIdentity();
                    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();


}
void GLWidget::paintGL(){

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(Camera.mPos.x,  Camera.mPos.y,  Camera.mPos.z,
              Camera.mView.x, Camera.mView.y, Camera.mView.z,
              Camera.mUp.x,   Camera.mUp.y,   Camera.mUp.z);


     Camera.Mouse_Move();

     Keyboard_Operations();

     terra();
    glEnable(GL_LIGHTING);
     drawCube();
    glDisable(GL_LIGHTING);

     // Draw The Car
             glColor3f(1,1,1);
             glEnable(GL_LIGHTING);
             glPushMatrix();
             glTranslatef(20.0f,-3.0f,10.0f);

             glPopMatrix();
             glDisable(GL_LIGHTING);


     rot+=1;
       // Framerate control
        int delay = time.msecsTo(QTime::currentTime());
        if (delay == 0)
           delay = 1;
        time = QTime::currentTime();
        timer->start(qMax(0, 30 - delay));

}
void GLWidget::keyPressEvent(QKeyEvent *event){

    switch(event->key()){
        case Qt::Key_Escape:
            close();
        break;
    }
    if((event->key()>31) && (event->key()<132))
       keyStates[event->key()]=true;
}
void GLWidget::keyReleaseEvent(QKeyEvent *event){

    if((event->key()>31) && (event->key()<132))
        keyStates[event->key()]=false;
}
void GLWidget::Keyboard_Operations(){

    if(keyStates['W']==true)Camera.Move_Camera(CAMERASPEED);
    if(keyStates['S']==true)Camera.Move_Camera(-CAMERASPEED);
    if(keyStates['A']==true)Camera.Move_Lateral_Camera(-LATERALSPEED);
    if(keyStates['D']==true)Camera.Move_Lateral_Camera(LATERALSPEED);
}
void GLWidget::drawCube() {


    glEnable(GL_TEXTURE_2D);

    // para escolher a textura que vai ser usada

    glBindTexture( GL_TEXTURE_2D, texture[1]);

    glPushMatrix();

    glTranslatef(20.0f,-3.0f,25.0f);
   // glRotatef(rot, 0.0f, 1.0f, 0.0f);

    GLfloat branco[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, branco);

    glBegin(GL_QUADS);
                    // Front Face
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
                    // Back Face
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
                    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
                    // Top Face
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
                    // Bottom Face
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
                    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
                    // Right face
                    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
                    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
                    // Left Face
                    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
                    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
                    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
                    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
            glEnd();



        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

}
void GLWidget::terra()	// Draws the Ground
{


        float  x,z;
        glEnable(GL_TEXTURE_2D);
        glPushMatrix();

        // para escolher a textura que vai ser usada
        glBindTexture( GL_TEXTURE_2D, texture[0]);

        for(z=0;z<30-1;z++)
        {
                glPushMatrix();
                for(x=0;x<30-1;x++)
                {

                        glTranslatef(8.0f,0.0f,0.0f);
                        glBegin(GL_QUADS);
                        // Bottom Face
                        glNormal3f(0.0f, -1.0f, 0.0f);
                        glTexCoord2f(1.0f, 1.0f); glVertex3f(-4.0f, -4.0f, -4.0f);
                        glTexCoord2f(0.0f, 1.0f); glVertex3f( 4.0f, -4.0f, -4.0f);
                        glTexCoord2f(0.0f, 0.0f); glVertex3f( 4.0f, -4.0f, 4.0f);
                        glTexCoord2f(1.0f, 0.0f); glVertex3f(-4.0f, -4.0f, 4.0f);
                        glEnd();

                }
                glPopMatrix();
              glTranslatef(0.0f,0.0f,8.0f);
           }

        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}
void GLWidget::DefineLuzESPECULAR()
{
    int LuzAmbEhMax = 1;


    // Define cores para um objeto dourado
      GLfloat LuzAmbiente[]   = {0.24725f, 0.1995f, 0.07f } ;
      GLfloat LuzAmbienteMAX[]   = {1,1,1 } ;

      GLfloat LuzDifusa[]   = {0.75164f, 0.60648f, 0.22648f, 1.0f };
      GLfloat LuzEspecular[] = {0.626281f, 0.555802f, 0.366065f, 1.0f };
      //GLfloat LuzEspecular[] = {1,0,0, 1.0f };
      GLfloat PosicaoLuz0[]  = {3.0f, 3.0f, 0.0f, 1.0f };
      GLfloat PosicaoLuz1[]  = {-3.0f, -3.0f, 0.0f, 1.0f };
      GLfloat Especularidade[] = {1.0f, 1.0f, 1.0f, 1.0f };

       // ****************  Fonte de Luz 0

            glEnable ( GL_COLOR_MATERIAL );


       // Habilita o uso de ilumina??o
      glEnable(GL_LIGHTING);

      // Ativa o uso da luz ambiente
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
      // Define os parametros da Luz n?mero Zero
      if (LuzAmbEhMax)
              glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbienteMAX);
      else glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);

      glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
      glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
      glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
      glEnable(GL_LIGHT0);

      // Ativa o "Color Tracking"
      glEnable(GL_COLOR_MATERIAL);

      // Define a reflectancia do material
      glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

      // Define a concentra??o do brilho.
      // Quanto maior o valor do Segundo parametro, mais
      // concentrado ser? o brilho. (Valores v?lidos: de 0 a 128)
      glMateriali(GL_FRONT,GL_SHININESS,112);

      // ****************  Fonte de Luz 1

      // Ativa o uso da luz ambiente
      glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LuzAmbiente);
      // Define os parametros da Luz n?mero Zero
      if (LuzAmbEhMax)
              glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbienteMAX);
      else glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
      glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa  );
      glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular  );
      glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
      glEnable(GL_LIGHT1);

      // Ativa o "Color Tracking"
      glEnable(GL_COLOR_MATERIAL);

      // Define a reflectancia do material
      glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

      // Define a concentra??o do brilho.
      // Quanto maior o valor do Segundo parametro, mais
      // concentrado ser? o brilho. (Valores v?lidos: de 0 a 128)
      glMateriali(GL_FRONT,GL_SHININESS,11);
    //  glMateriali(GL_FRONT,GL_SHININESS,20);
}
void GLWidget::DefineLuzDIFUSA()
{
    int LuzAmbEhMax = 1;

    // Define cores para um objeto dourado
  GLfloat LuzAmbiente[]   = {0.24725f, 0.1995f, 0.07f } ;
  //GLfloat LuzAmbiente[]   = {0,0,0} ;
  GLfloat LuzAmbienteMAX[]   = {1,1,1 } ;
  GLfloat LuzDifusa[]   = {0.75164f, 0.60648f, 0.22648f, 1.0f };
  GLfloat LuzEspecular[] = {0,0,0, 1.0f };
  GLfloat PosicaoLuz0[]  = {3.0f, 3.0f, 0.0f, 1.0f };
  GLfloat PosicaoLuz1[]  = {-3.0f, -3.0f, 0.0f, 1.0f };
  GLfloat Especularidade[] = {0,0,0,1 };

   // ****************  Fonte de Luz 0

  glEnable ( GL_COLOR_MATERIAL );


   // Habilita o uso de ilumina??o
  glEnable(GL_LIGHTING);

  // Ativa o uso da luz ambiente
  if (LuzAmbEhMax)
          glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbienteMAX);
  else glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
  // Define os parametros da Luz n?mero Zero
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa  );
  glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular  );
  glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
  glEnable(GL_LIGHT0);

  // Ativa o "Color Tracking"
  glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  //glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentra??o do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado ser? o brilho. (Valores v?lidos: de 0 a 128)
  glMateriali(GL_FRONT,GL_SHININESS,51);

  // ****************  Fonte de Luz 1

  // Ativa o uso da luz ambiente
  if (LuzAmbEhMax)
          glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbienteMAX);
  else glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
  // Define os parametros da Luz n?mero Zero
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa  );
  glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular  );
  glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
  glEnable(GL_LIGHT1);

  // Ativa o "Color Tracking"
  glEnable(GL_COLOR_MATERIAL);

  // Define a reflectancia do material
  //glMaterialfv(GL_FRONT,GL_SPECULAR, Especularidade);

  // Define a concentra??o do brilho.
  // Quanto maior o valor do Segundo parametro, mais
  // concentrado ser? o brilho. (Valores v?lidos: de 0 a 128)
  //glMateriali(GL_FRONT,GL_SHININESS,20);

}
