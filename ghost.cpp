#include "ghost.h"

Ghost::Ghost(int dim, float velocity, int pos0, int pos1){
   DimBoard = dim;
    vel = velocity;
    int c;

    //Se inicializa una posicion aleatoria dentro del tablero
    Position[0] = pos0;
    Position[1] = pos1;
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

void Ghost::update(){
    float new_x = Position[0] + Direction[0];
    float new_y = Position[1] + Direction[1];

    //cout << "X=" << Position[0] << "; Y= " << Position[1] << endl;
    if(!available[currDir]){
        Direction[0] = 0;
        Direction[1] = 0;
    }
}