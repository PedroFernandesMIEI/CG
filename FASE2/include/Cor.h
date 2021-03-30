#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef TRABALHO_COR_H
#define TRABALHO_COR_H

#include "Operacao.h"

class Cor: public Operacao {
    float r, g, b;
public:
    Cor();
    Cor(float r, float g, float b);
    float getR() {return this->r;}
    float getG() {return this->g;}
    float getB() {return this->b;}
    void setR(float x){this->r=r;}
    void setG(float y){this->g=g;}
    void setB(float z){this->b=b;}
    void run();
};




#endif //TRABALHO_COR_H
