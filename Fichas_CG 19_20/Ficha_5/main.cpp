#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

#define NARVORES 5000

using namespace std;

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

vector<float> xx;
vector<float> zz;

// cria os vetores com pontos fora do circulo de raio 50 mas dentro do plano
void populaArvores(){
    srand (time(NULL));

    float x =0.0f;
    float z =0.0f;

    for(int i=0;i<NARVORES;) {

        x = (rand() % 201) - 100;
        z = (rand() % 201) - 100;

        if (sqrt(x * x + z * z) > 50.0f) {
            xx.push_back(x);
            zz.push_back(z);
            i++;
        }
    }}


void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);


	//plano
	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_TRIANGLES);
		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);

		glVertex3f(100.0f, 0, -100.0f);
		glVertex3f(-100.0f, 0, 100.0f);
		glVertex3f(100.0f, 0, 100.0f);
	glEnd();

	//torus
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
        glTranslatef(0.0f, 1.0f, 15.0f);
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
        glTranslatef(0.0f, 1.0f, 35.0f);
        glutSolidTeapot(2.0f);
        glPopMatrix();
    }

    //arvores
    for(int i=0;i<NARVORES;){

           glPushMatrix();
           glTranslatef(xx[i], 0.0f, zz[i]);
           glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
           glColor3f(0.3f, 0.18f, 0.18f);
           glutSolidCone(0.2,4, 14,14);
           glPopMatrix();

           glPushMatrix();
           glTranslatef(xx[i], 3.0f, zz[i]);
           glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
           glColor3f(0.0f, 0.2f, 0.1f);
           glutSolidCone(1,4, 14,14);
           glPopMatrix();

           i++;
    }

    // End of frame
    glutSwapBuffers();
    glutPostRedisplay();
}


void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}


void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}


void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));

	printf("\nUse Arrows to move the camera up/down and left/right\n");
	printf("Home and End control the distance from the camera to the origin");
}


int main(int argc, char **argv) {

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");
		
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	populaArvores();
	spherical2Cartesian();

	printInfo();

// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
