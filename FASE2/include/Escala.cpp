#include "Escala.h"

Escala :: Escala (){
    this->x= this->y=this->z =0.0;
}

Escala:: Escala (float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void Escala::run() {
    glScalef(this->x, this->y, this->z);
}