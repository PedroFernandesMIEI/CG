#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef TRABALHO_ESCALA_H
#define TRABALHO_ESCALA_H

#include "Operacao.h"

class Escala: public Operacao{
    float x, y, z;

public:
    Escala();
    Escala(float x, float y, float z);
    float getX() {return this->x;}
    float getY() {return this->y;}
    float getZ() {return this->z;}
    void setX(float x){this->x=x;}
    void setY(float y){this->y=y;}
    void setZ(float z){this->z=z;}
    void run();
};

#endif //TRABALHO_ESCALA_H
