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
        currDir = -1;
    }

    if(currDir == -1 || cell_type == 10 && counter > 500){
        int newDir = (rand() % 4);
        changeDirection(newDir);
        counter = 0;
        //cout << currDir << endl;
    }
    if(cell_type == 10 || cell_type == 5 || cell_type == 6 || cell_type == 7 || cell_type == 4){
        flag = true;
        counter++;
    } 
    else{
        flag = false;
        counter = 0;
    } 
}

void Ghost::movementConstraints(vector<vector<int>> &matrix, int WIDTH, int  HEIGTH){ //x and y are grid position
	int x = (Position[1]*matrix.size()/HEIGTH);
	int y = (Position[0]*matrix[0].size()/WIDTH);
    //cout << "x: " << Position[1] << " y: " << Position[0] << endl;
    //cout << matrix[x][y] << endl;
	switch(matrix[x][y]){
		case 0: available[0] = true; available[1] = true; available[2] = false; available[3] = false; break;
        case 1: available[0] = false; available[1] = false; available[2] = true; available[3] = true; break;
        case 2: available[0] = false; available[1] = true; available[2] = true; available[3] = false; break;
        case 3: available[0] = true; available[1] = false; available[2] = false; available[3] = true; break;
        case 4: available[0] = false; available[1] = true; available[2] = true; available[3] = true; break;
        case 5: available[0] = true; available[1] = true; available[2] = false; available[3] = true; break;
        case 6: available[0] = true; available[1] = false; available[2] = true; available[3] = true; break;
        case 7: available[0] = true; available[1] = true; available[2] = true; available[3] = false; break;
        case 8: available[0] = false; available[1] = true; available[2] = false; available[3] = true; break;
        case 9: available[0] = true; available[1] = false; available[2] = true; available[3] = false; break;
        case 10: available[0] = true; available[1] = true; available[2] = true; available[3] = true; break;
        case 11: available[0] = false; available[1] = false; available[2] = false; available[3] = true; break;
        case 12: available[0] = false; available[1] = true; available[2] = false; available[3] = false; break;
	}
        switch(currDir){
        case 0: available[2] = false;break;
        case 1: available[3] = false;break;
        case 2: available[0] = false;break;
        case 3: available[1] = false;break;
    }
    cell_type = matrix[x][y];
}