#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
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
    protected:

    private:
        int vertices[4][2] = {
            1,1,
            0,1,
            0,0,
            1,0
        };

        //Vector de direccion
        float Position[2] = {0.0, 5.0};
        float Direction[2] = {0.0, 5.0};
        int DimBoard;
        float radio;
        float Scale;
};