#include "Desenhar.h"

void Desenhar::run() {

    glBegin(GL_TRIANGLES);
    for(int i=0; i< vertexes.size(); i+=3){

        glVertex3f(vertexes[i].getX(), vertexes[i].getY(), vertexes[i].getZ());
        glVertex3f(vertexes[i+1].getX(), vertexes[i+1].getY(), vertexes[i+1].getZ());
        glVertex3f(vertexes[i+2].getX(), vertexes[i+2].getY(), vertexes[i+2].getZ());
    }
    glEnd();
}
