#include "Cor.h"

Cor :: Cor (){
    this->r= this->g=this->b =0.0;
}

Cor:: Cor (float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

void Cor::run() {
    glColor3f(this->r, this->g, this->b);
}