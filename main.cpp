//g++ main.cpp pacman.cpp ghost.cpp RgbImage.cpp -lGL -lGLU -lglut -o output
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
#include "ghost.h"
using namespace std;

#define NTextures 3
GLuint	texture[NTextures];

bool* keyStates = new bool[256]; // Create an array of boolean values of length 256 (0-255)  

char* filenames[NTextures] = {"img/tablero_recortado.bmp","img/kurbo.bmp","img/clyde.bmp"};

vector<vector<int>> matrix = {
{2,8,8,8,8,4,4,8,8,8,8,8,1,-1,2,8,8,8,8,8,4,4,8,8,8,8,1},
{9,10,8,8,8,10,10,8,8,8,8,10,9,-1,9,10,8,8,8,8,10,10,8,8,8,10,9},
{9,9,-1,-1,-1,9,9,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,9,9,-1,-1,-1,9,9},
{9,9,-1,-1,-1,9,9,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,9,9,-1,-1,-1,9,9},
{7,10,8,8,8,10,10,8,4,4,8,10,10,8,10,10,8,4,4,8,10,10,8,8,8,10,6},
{7,10,8,8,8,10,10,8,10,10,8,5,5,8,5,5,8,10,10,8,10,10,8,8,8,10,6},
{9,9,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,9,9},
{9,10,8,8,8,10,6,-1,9,10,8,8,1,-1,2,8,8,10,9,-1,7,10,8,8,8,10,9},
{0,8,8,8,8,8,6,-1,0,8,8,10,9,-1,9,10,8,8,3,-1,7,10,8,8,8,8,3},
{-1,-1,-1,-1,-1,9,9,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,9,9,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,9,9,-1,2,8,8,10,10,8,10,10,8,8,1,-1,9,9,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,9,9,-1,9,10,8,5,5,8,5,5,8,10,9,-1,9,9,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,-1},
{12,8,8,8,8,10,10,8,10,6,-1,-1,-1,-1,-1,-1,-1,7,10,8,10,10,8,8,8,8,11},
{12,8,8,8,8,10,10,8,10,6,-1,-1,-1,-1,-1,-1,-1,7,10,8,10,10,8,8,8,8,11},
{-1,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,9,9,-1,7,10,8,8,8,8,8,8,8,10,6,-1,9,9,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,9,9,-1,7,10,8,8,8,8,8,8,8,10,6,-1,9,9,-1,-1,-1,-1,-1},
{-1,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,-1},
{2,8,8,8,8,10,10,8,10,10,8,8,1,-1,2,8,8,10,10,8,10,10,8,8,8,8,1},
{9,10,8,8,8,10,10,8,5,5,8,10,9,-1,9,10,8,5,5,8,10,10,8,8,8,10,9},
{9,9,-1,-1,-1,9,9,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,9,9,-1,-1,-1,9,9},
{9,10,8,1,-1,7,10,8,4,4,8,10,10,8,10,10,8,4,4,8,10,6,-1,2,8,10,9},
{0,8,10,9,-1,7,10,8,10,10,8,5,5,8,5,5,8,10,10,8,10,6,-1,9,10,8,3},
{-1,-1,9,9,-1,9,9,-1,9,9,-1,-1,-1,-1,-1,-1,-1,9,9,-1,9,9,-1,9,9,-1,-1},
{2,8,10,10,8,10,9,-1,9,10,8,8,1,-1,2,8,8,10,9,-1,9,10,8,10,10,8,1},
{9,10,5,5,8,8,3,-1,0,8,8,10,9,-1,9,10,8,8,3,-1,0,8,8,5,5,10,9},
{9,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,9,-1,9,9,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,9},
{9,10,8,8,8,8,8,8,8,8,8,10,10,8,10,10,8,8,8,8,8,8,8,8,8,10,9},
{0,8,8,8,8,8,8,8,8,8,8,5,5,8,5,5,8,8,8,8,8,8,8,8,8,8,3}};


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
Ghost *ghosts[4];

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
   player = new Pacman(600, 0.05, 20, 22);
   for (int i = 0; i < 4; i++){
      ghosts[i] = new Ghost(600,0.05, 70 * (i+1), 200);
   }
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

   glBindTexture(GL_TEXTURE_2D, texture[2]);

   for (int i = 0; i < 4; i++){
      ghosts[i]->draw();
      ghosts[i]->update();
      ghosts[i]->movementConstraints(matrix,HEIGTH, WIDTH);
   }

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
   srand((unsigned) time(NULL));
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