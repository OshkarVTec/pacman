#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <random>
#include <iomanip>

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

void init()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(-300,300,-300,300);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glClearColor(0,0,0,0);
   srand(time(nullptr));
}

void display()
{
   //Cuadrado *aux;
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(0.5, 0.5, 0.5);

   glColor3f(1.0, 0.0, 0.0);
/*    for(i = 0; i < NObjetos; i++){
      aux = (Cuadrado *)objetos[i];
      aux->draw();
      aux->update();
   } */

   glFlush();
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