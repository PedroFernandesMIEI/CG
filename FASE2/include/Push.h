#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef TRABALHO_PUSH_H
#define TRABALHO_PUSH_H

#include "Operacao.h"

class Push: public Operacao
{

public:
    Push();
    void run();
};


#endif //TRABALHO_PUSH_H
