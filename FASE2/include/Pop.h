#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef TRABALHO_POP_H
#define TRABALHO_POP_H

#include "Operacao.h"

class Pop: public Operacao {

public:
    Pop();
    void run();
};

#endif //TRABALHO_POP_H
