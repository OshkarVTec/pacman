#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <unistd.h>
#include <random>
#include <iomanip>
#include "RgbImage.h"
#include "pacman.h"

#define NTextures 1
GLuint	texture[NTextures];

char* filename = "img/tablero_pacman.bmp";

//Variables dimensiones de la pantalla
int WIDTH=600;
int HEIGTH=600;
//Variables para establecer los valores de gluPerspective
float FOVY=60.0;
float ZNEAR=0.01;
float ZFAR=900.0;
//Variables para definir la posicion del observador
//gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z)
float EYE_X=300.0;
float EYE_Y=200.0;
float EYE_Z=300.0;
float CENTER_X=0;
float CENTER_Y=0;
float CENTER_Z=0;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;

Pacman *player;

void loadTextureFromFile(char *filename, int id)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap( filename );

    //generate an OpenGL texture ID for this texture
    glGenTextures(1, &texture[id]);
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, texture[id]);


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0,
                     GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
    theTexMap.Reset();
}

void init()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-300,300,-300,300);

   //Texture
   loadTextureFromFile( filename , 0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glClearColor(0,0,0,0);
   player = new Pacman(300, 0.1);
   srand(time(nullptr));
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   //activa la textura
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture[0]);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //activa la textura
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture[0]);


   glBegin(GL_QUADS);
	float a = 1.0f;
   glColor3f(0.0, 0.0, 0.0);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-300.0, -300.0, 0.0);

   glTexCoord2f(0.0, 1.0);
   glVertex3f(-300.0, 300.0, 0.0);

   glTexCoord2f(1.0, 1.0);
   glVertex3f(300.0, 300.0, 0.0);

   glTexCoord2f(1.0, 0.0);
   glVertex3f(300.0, -300.0, 0.0);

   glEnd();

   glColor3f(1.0, 0.0, 0.0);
   player->draw();
   player->update();

   glFlush();
	usleep(1000);
}

void idle()
{
   display();
}

void keyboard(unsigned char key, int x, int y)
{
   switch(key)
   {//SOLID
   case 's':
   case 'S':
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glShadeModel(GL_FLAT);
   break;
   //INTERPOL
   case 'i':
   case 'I':
      glShadeModel(GL_SMOOTH);
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   break;

   case 'w':
   case 'W':
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   break;

   case 27:   // escape
   exit(0);
   break;
   }
   glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(WIDTH, HEIGTH);
   glutCreateWindow("Pacman");
   init();
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}