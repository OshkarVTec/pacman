#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#pragma once

using namespace std;

class Pacman
{
    public:
        Pacman(int, float);
        ~Pacman();
        void draw();
        void update();
        void changeDirection(int);
        void movementConstraints(vector<vector<int>>, int, int);
    protected:

    private:
        int vertices[4][2] = {
            1,1,
            0,1,
            0,0,
            1,0
        };

        bool available[4] = {true, true, true, true}; //false when there is a wall on that direction
        //

        //Vector de direccion
        float Position[2] = {0.0, 5.0};
        float Direction[2] = {0.0, 5.0};
        int currDir; //current direction
        int DimBoard;
        float radio;
        float Scale;
        float vel;
};