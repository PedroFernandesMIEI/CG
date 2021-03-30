#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef TRABALHO_TRANSLACAO_H
#define TRABALHO_TRANSLACAO_H

#include "Operacao.h"

class Translacao: public Operacao{
    float x, y, z;

public:
    Translacao();
    Translacao(float x, float y, float z);
    float getX() {return this->x;}
    float getY() {return this->y;}
    float getZ() {return this->z;}
    void setX(float x){this->x=x;}
    void setY(float y){this->y=y;}
    void setZ(float z){this->z=z;}
    void run();
};


#endif //TRABALHO_TRANSLACAO_H
