#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "Ponto.h"
#include "Operacao.h"

#ifndef TRABALHO_DESENHAR_H
#define TRABALHO_DESENHAR_H


class Desenhar: public Operacao{

    std::vector<Ponto> vertexes;

public:
    Desenhar(std::vector<Ponto> vertexes){
        this->vertexes=vertexes;
    };

    void run();

};


#endif //TRABALHO_DESENHAR_H
