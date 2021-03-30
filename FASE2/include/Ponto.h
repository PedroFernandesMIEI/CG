#ifndef TRABALHO_PONTO_H
#define TRABALHO_PONTO_H



class Ponto {
    float x;
    float y;
    float z;

public:
    Ponto();
    Ponto(float a, float b, float c);
    float getX() { return this->x; }
    float getY() { return this->y; }
    float getZ() { return this->z; }
    void setX( float b) { this->x = b; }
    void setY( float b) { this->y = b; }
    void setZ( float b) { this->z = b; }

};


#endif //TRABALHO_PONTO_H
