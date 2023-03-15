#include "ghost.h"


void Ghost::update(){
    float new_x = Position[0] + Direction[0];
    float new_y = Position[1] + Direction[1];

    //cout << "X=" << Position[0] << "; Y= " << Position[1] << endl;
    if(!available[currDir]){
        Direction[0] = 0;
        Direction[1] = 0;
    }
}