#include "pacman.h"

Pacman::Pacman(int dim, float vel)
{
    DimBoard = dim;
    int c;

    //Se inicializa una posicion aleatoria dentro del tablero
    Position[0] = 0;
    Position[1] = 0;
    //Se inicializa el vector de direccion con un valor aleatorio
    Direction[0] = rand();
    Direction[1] = rand();
    //Se normaliza el vector de direccion
    float m = sqrt(Direction[0]*Direction[0] + Direction[1]*Direction[1]);
    Direction[0] /= m;
    Direction[1] /= m;
    //se multiplica el vector de direccion por la magnitud de la velocidad
    Direction[0] *= vel;
    Direction[1] *= vel;

    Scale = 20;

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
        for(int i=0; i< 4; i++){
            glVertex2iv(vertices[i]);
        }
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

}