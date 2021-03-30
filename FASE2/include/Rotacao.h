#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef TRABALHO_ROTACAO_H
#define TRABALHO_ROTACAO_H

#include "Operacao.h"

class Rotacao: public Operacao{
    float angle, x, y, z;

public:
    Rotacao();
    Rotacao(float angle, float x, float y, float z);
    float getAngle(){return this->angle;}
    float getX() {return this->x;}
    float getY() {return this->y;}
    float getZ() {return this->z;}
    void setAngle(float angle){this->angle=angle;}
    void setX(float x){this->x=x;}
    void setY(float y){this->y=y;}
    void setZ(float z){this->z=z;}
    void run();
};



#endif //TRABALHO_ROTACAO_H
