#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "pacman.h"
#pragma once

using namespace std;

class Fantasma : public Pacman{
   private:
   int cell_type;
   public:
   void update();
};