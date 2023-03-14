//g++ main.cpp pacman.cpp RgbImage.cpp -lGL -lGLU -lglut -o output
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <random>
#include <iomanip>
#include <vector>
#include "RgbImage.h"
#include "pacman.h"
using namespace std;

#define NTextures 2
GLuint	texture[NTextures];

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  

char* filenames[NTextures] = {"img/tablero_recortado.bmp","img/kurbo.bmp"};

vector<vector<int>> matrix = {{10,10,10}, {10,10,10},{10,10,10}};

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

void keyOperations (void) {  
   if (keyStates['w']) player->changeDirection(0); 
   if (keyStates['d']) player->changeDirection(1); 
   if (keyStates['s']) player->changeDirection(2);
   if (keyStates['a']) player->changeDirection(3);
}  

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
   reverse(matrix.begin(), matrix.end()); //Map to the position
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,600,0,600);

   //Texture
   for (int i = 0; i < NTextures; i++){
      loadTextureFromFile( filenames[i] , i);
   }

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glClearColor(0,0,0,0);
   player = new Pacman(600, 0.05);
   srand(time(nullptr));
}

void display()
{
   keyOperations();  
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texture[1]);


   player->draw();
   player->update();
   player->movementConstraints(matrix,HEIGTH, WIDTH);

   glBindTexture(GL_TEXTURE_2D, texture[0]);
   glBegin(GL_QUADS);
   glColor3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(0.0, 0.0, 0.0);

   glTexCoord2f(0.0, 1.0);
   glVertex3f(0.0, 600.0, 0.0);

   glTexCoord2f(1.0, 1.0);
   glVertex3f(600.0, 600.0, 0.0);

   glTexCoord2f(1.0, 0.0);
   glVertex3f(600.0, 0.0, 0.0);

   glEnd();

   glDisable(GL_TEXTURE_2D);
   glFlush();
}

void idle()
{
   display();
}

void keyPressed (unsigned char key, int x, int y) {  
   keyStates[key] = true; // Set the state of the current key to pressed  
}  
  
void keyUp (unsigned char key, int x, int y) {  
   keyStates[key] = false; // Set the state of the current key to not pressed  
}  

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(WIDTH, HEIGTH);
   glutCreateWindow("Pacman");
   init();
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutKeyboardFunc(keyPressed); // Tell GLUT to use the method "keyPressed" for key presses  
   glutKeyboardUpFunc(keyUp); // Tell GLUT to use the method "keyUp" for key up events  
   glutMainLoop();
   return 0;
}