#include "Translacao.h"

Translacao :: Translacao (){
        this->x= this->y=this->z =0.0;
    }

Translacao:: Translacao (float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z = z;
    };

void Translacao::run() {
    glTranslatef(this->x, this->y, this->z);
}