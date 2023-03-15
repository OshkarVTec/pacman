#include "ghost.h"


void Ghost::update(){
    float new_x = Position[0] + Direction[0];
    float new_y = Position[1] + Direction[1];

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
        //currDir = -1;
    }

}