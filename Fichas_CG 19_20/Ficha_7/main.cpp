

#include<stdio.h>
#include<stdlib.h>
#include<vector>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#endif

#define NARVORES 500
#define EYEHEIGHT 2

float k =0, r =0;
float pX = 0, pZ = 0;

float alpha = 0.0f;

std::vector<float> p;
std::vector<float> xx;
std::vector<float> zz;

unsigned char *imageData;
int imageHeight;

int imageWidth;

GLuint buffers[1];
int tipo=GL_LINE; //polygon mode

//retorna a altura para aquele x e z
int h(int x, int z){

    return (int)imageData[(x+(imageWidth/2))+((z+(imageHeight/2))*imageWidth)];
}

float hf(float px, float pz){
    float x1,x2,z1,z2,fz,fx,h_x1_z,h_x2_z,height_xz;

    x1=floor(px);
    x2=x1+1;
    z1=floor(pz);
    z2=z1+1;

    fz=pz-z1;
    fx=px-x1;

    h_x1_z = h(x1,z1)*(1-fz)+h(x1,z2)*fz;
    h_x2_z = h(x2,z1)*(1-fz)+h(x2,z2)*fz;

    height_xz = h_x1_z*(1-fx) + h_x2_z*fx;

    return  height_xz;
}

void populaArvores(){
    srand (time(NULL));

    float x =0.0f;
    float z =0.0f;

    for(int i=0;i<NARVORES;) {
// inteiros de -128 a 127
        x = (rand() % 256) - 128;
        z = (rand() % 256) - 128;

        if (sqrt(x * x + z * z) > 50.0f) {
            xx.push_back(x);
            zz.push_back(z);
            i++;
        }
    }}

    

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45,ratio,1,1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void drawTerrain() {

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    for (int i = 0; i < imageHeight - 1 ; i++) {
        glDrawArrays(GL_TRIANGLE_STRIP, (imageWidth) * 2 * i, (imageWidth) * 2);
    }
}



void renderScene(void) {

	float pos[4] = {-1.0, 1.0, 1.0, 0.0};

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(pX, hf(pX,pZ)+EYEHEIGHT, pZ,
              pX + sin(alpha),hf(pX,pZ)+EYEHEIGHT,pZ + cos(alpha),
			  0.0f,1.0f,0.0f);

	glPolygonMode(GL_FRONT, tipo);

    drawTerrain();

    glColor3f(1.0f, 0.2f, 0.78f);
    glutSolidTorus(1.0, 2.0, 100, 100);

    //delta tempo entre renders para fazer as rotações
    int tempoVelho=0;
    int tempo = glutGet(GLUT_ELAPSED_TIME);
    int delta = tempo - tempoVelho;
    float percentSegundo = delta / 1000.0f;
    tempoVelho = tempo;


    //teapots a 15 a azul CW
    glColor3f(0.0f, 0.0f, 1.0f);
    for(int i = 0;i<8;i++){
        glPushMatrix();
        glRotatef(-9*percentSegundo, 0.0f, 1.0f, 0.0f);
        glRotatef((45.0f*i), 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, hf(0.0f,15.0f), 15.0f);
        glRotatef((-90.0f), 0.0f, 1.0f, 0.0f);
        glutSolidTeapot(2.0f);
        glPopMatrix();
    }

    //teapots a 35 a vermelho CCW
    glColor3f(1.0f, 0.0f, 0.0f);
    for(int i = 0;i<16;i++){
        glPushMatrix();
        glRotatef(9*percentSegundo, 0.0f, 1.0f, 0.0f);
        glRotatef((22.5f*i), 0.0f, 1.0f, 0.0f); // ang in degrees
        glTranslatef(0.0f, hf(0.0f,35.0f), 35.0f);
        glutSolidTeapot(2.0f);
        glPopMatrix();
    }

    //arvores
    for(int i=0;i<NARVORES;){

        glPushMatrix();
        glTranslatef(xx[i], hf(xx[i],zz[i]), zz[i]);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.3f, 0.18f, 0.18f);
        glutSolidCone(0.2,4, 14,14);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(xx[i], hf(xx[i],zz[i])+3.0f, zz[i]);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        glColor3f(0.0f, 0.2f, 0.1f);
        glutSolidCone(1,4, 14,14);
        glPopMatrix();

        i++;
    }

// End of frame
	glutSwapBuffers();
}



void processKeys(unsigned char key, int xx, int yy) {

    switch(key) {
        case ' ' :
            tipo++;
            if(tipo==6915)tipo=6912;// inteiros que correspodem ao GL_FILL, GL_LINE, GL_POINT
            break;
        //ROTACAO ESQUERDA
        case 'a' :
        case 'A' :
            alpha+=0.1;
            break;
        //ROTACAO DIREITA
        case 's' :
        case 'S' :
            alpha-=0.1;
            break;


    }
    glutPostRedisplay();
}

void processSpecialKeys(int key, int x , int y){
    switch(key){
        //FRENTE
        case GLUT_KEY_UP:
            pX += sin(alpha);
            pZ += cos(alpha);
            break;
            //TRÁS
        case GLUT_KEY_DOWN:
            pX -= sin(alpha);
            pZ -= cos(alpha);
            break;
            //ESQUERDA
        case GLUT_KEY_LEFT:
            pX += cos(alpha);
            pZ -= sin(alpha);
            break;
            //DIREITA
        case GLUT_KEY_RIGHT:
            pX -= cos(alpha);
            pZ += sin(alpha);
            break;
    }
    glutPostRedisplay();
}




void init() {

// 	Load the height map "terreno.jpg"
    unsigned int t, tw, th;
    ilGenImages(1,&t);
    ilBindImage(t);
// terreno.jpg is the image containing our height map
    ilLoadImage((ILstring)"terreno.jpg");
// convert the image to single channel per pixel
// with values ranging between 0 and 255
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
// important: check tw and th values
// both should be equal to 256
// if not there was an error loading the image
// most likely the image could not be found
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    std::cout << "A imagem tem " << th << " de altura e " << tw << " de comprimento.\n";

    imageHeight = th;
    imageWidth = tw;
    // imageData is a LINEAR array with the pixel values
    imageData = ilGetData();
// 	Build the vertex arrays
    float x = -((float)(tw-1)/2);
    float z = -((float)(th-1)/2);

    for (int i = 0; i < (th-1); ++i) {
        for (int j = 0; j < tw; ++j) {

            p.push_back(x + j);
            p.push_back((float)(imageData[j+(i*th)]));
            p.push_back(z + i);
            p.push_back(x + j);
            p.push_back((float)(imageData[j+((i+1)*th)]));
            p.push_back(z + i + 1.0);

        }
    }
    std::cout << p.size();

    glEnableClientState(GL_VERTEX_ARRAY);

    glGenBuffers(1, buffers);

// copiar o vector para a memória gráfica

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(
            GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
            sizeof(float) * p.size(), // tamanho do vector em bytes
            p.data(), // os dados do array associado ao vector
            GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)/


// 	OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glPolygonMode(GL_FRONT, tipo);
}


int main(int argc, char **argv) {

// init GLUT and the window
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(640,640);
glutCreateWindow("CG@DI-UM");


// Required callback registry
glutDisplayFunc(renderScene);
glutIdleFunc(renderScene);
glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
glutKeyboardFunc(processKeys);
glutSpecialFunc(processSpecialKeys);


populaArvores();
ilInit();
glewInit();
init();

// enter GLUT's main cycle
glutMainLoop();

return 0;
}

