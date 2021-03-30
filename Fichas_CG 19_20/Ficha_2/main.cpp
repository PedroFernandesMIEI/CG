#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <math.h>

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


float angle = 0.0f;
float movX = 0.0f;
float movZ = 0.0f;
float escala = 1.0f;
int tipo=6912;

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0,
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

    glPolygonMode(GL_FRONT_AND_BACK,tipo);

// put the geometric transformations here

// put drawing instructions here

    glBegin(GL_LINES);
// X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
// Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
// Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    glTranslatef(movX,0.0f,movZ);
    glRotatef(angle,0.0f,1.0f,0.0f);
    glScalef(escala,escala,escala);

    glBegin(GL_TRIANGLES);
    //primeiro de baixo
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    //segundo de baixo
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    //face lateral 1
    glColor3f(1.0f, 0.6f, 0.2f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    //face lateral vermelha
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    //face lateral verde
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 0.0f, -1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    //face lateral azul
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events

void teclado(unsigned char key, int x, int y) {

    switch(key) {
        case 'z' :
            angle+=1.0f;
            glutPostRedisplay();
            break;
        case 'x' :
            angle-=1.0f;
            glutPostRedisplay();
            break;
        case ' ' :
            tipo++;
            if(tipo==6915)tipo=6912;// inteiros que correspodem ao GL_FILL, GL_LINE, GL_POINT
            glutPostRedisplay();
            break;

    }
}

void tecladoEspecial(int key, int x, int y) {

    switch(key) {

        case GLUT_KEY_LEFT :
            movX-=1.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT :
            movX+=1.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP :
            movZ-=1.0f;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN :
            movZ+=1.0f;
            glutPostRedisplay();
            break;

    }
}

void rato (int button, int state, int x, int y){
    if(button==GLUT_LEFT_BUTTON){
        escala+=0.1f;
        glutPostRedisplay();
    }
    if(button==GLUT_RIGHT_BUTTON){
        escala-=0.1f;
        glutPostRedisplay();
    }

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

	
// put here the registration of the keyboard callbacks

    glutKeyboardFunc(teclado);
    glutSpecialFunc(tecladoEspecial);
    glutMouseFunc(rato);


//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
