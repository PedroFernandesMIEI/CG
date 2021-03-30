#include "Rotacao.h"

Rotacao :: Rotacao (){
   this->angle= this->x= this->y=this->z =0.0;
}

Rotacao:: Rotacao (float angle, float x, float y, float z){
    this->angle=angle;
    this->x = x;
    this->y = y;
    this->z = z;
}

void Rotacao::run() {
    glRotatef(this->angle, this->x, this->y, this->z);
}