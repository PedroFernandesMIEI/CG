#include "Ponto.h"

Ponto::Ponto() {
    this->x=this->y=this->z=0.0;
}

Ponto::Ponto(float a, float b, float c){
    this->x=a;
    this->y=b;
    this->z=c;
}