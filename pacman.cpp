#include "pacman.h"
#include <vector>

Pacman::Pacman(int dim, float velocity)
{
    DimBoard = dim;
    vel = velocity;
    int c;

    //Se inicializa una posicion aleatoria dentro del tablero
    Position[0] = 0;
    Position[1] = 0;
    //Se inicializa el vector de direccion
    Direction[0] = 1;
    Direction[1] = 0;
    currDir = 1;
    //Se normaliza el vector de direccion
    float m = sqrt(Direction[0]*Direction[0] + Direction[1]*Direction[1]);
    Direction[0] /= m;
    Direction[1] /= m;
    //se multiplica el vector de direccion por la magnitud de la velocidad
    Direction[0] *= vel;
    Direction[1] *= vel;

    Scale = 1;

}

Pacman::~Pacman()
{
    //dtor
}

void Pacman::draw()
{
    glPushMatrix();
    glTranslatef(Position[0], Position[1], 0.0);
    glScaled(Scale,Scale,0);
    //Se dibuja el Pacman
    glBegin(GL_QUADS);
   glColor3f(1.0, 1.0, 1.0);
   glTexCoord2f(0.0, 0.0);
   glVertex3f(-15.0, -15.0, 0.0);

   glTexCoord2f(0.0, 1.0);
   glVertex3f(-15.0, 15.0, 0.0);

   glTexCoord2f(1.0, 1.0);
   glVertex3f(15.0, 15.0, 0.0);

   glTexCoord2f(1.0, 0.0);
   glVertex3f(15.0, -15.0, 0.0);

   glEnd();

    glPopMatrix();
}

void Pacman::update()
{
    float new_x = Position[0] + Direction[0];
    float new_y = Position[1] + Direction[1];

    //cout << "X=" << Position[0] << "; Y= " << Position[1] << endl;

    if (abs(new_x) <= DimBoard - Scale)
        Position[0] = new_x;
    else {
        Direction[0] *= -1.0;
        Position[0] += Direction[0];
    }

    if (abs(new_y) <= DimBoard - Scale)
        Position[1] = new_y;
    else {
        Direction[1] *= -1.0;
        Position[1] += Direction[1];
    }

    //cout << "X=" << Position[0] << "; Y= " << Position[1] << endl;
    if(!available[currDir]){
        Direction[0] = 0;
        Direction[1] = 0;
    }

}

void Pacman::changeDirection(int dir){
    if(available[dir]){
        switch(dir){
            case 0: Direction[0] = 0 * vel; Direction[1] = 1 * vel; break;
            case 1: Direction[0] = 1 * vel; Direction[1] = 0 * vel; break;
            case 2: Direction[0] = 0 * vel; Direction[1] = -1 * vel; break;
            case 3: Direction[0] = -1 * vel; Direction[1] = 0 * vel; break;
        }
        currDir = dir;
    }
}

void Pacman::movementConstraints(vector<vector<int>> &matrix, int WIDTH, int  HEIGTH){ //x and y are grid position
	int x = (Position[1]*matrix.size()/HEIGTH);
	int y = (Position[0]*matrix.size()/WIDTH);
    cout << "x: " << x << " y: " << y << endl;
	switch(matrix[x][y]){
		case 0: available[0] = true; available[1] = true; available[2] = false; available[4] = false; break;
        case 1: available[0] = false; available[1] = true; available[2] = false; available[4] = false; break;
        
	}
}