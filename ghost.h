#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "pacman.h"
#pragma once

using namespace std;

class Ghost : public Pacman{
   private:
   int cell_type;
   public:
   using Pacman::Pacman;

   void update();
};