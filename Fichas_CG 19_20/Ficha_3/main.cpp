#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
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

int tipo=6912;
float alpha = 0;
float beta = 0.5;
float radius = 4;

void drawCylinder(float radius, float height, int slices) {

    float angle = 0.0f;
    float sizeSlice = (2*M_PI)/slices;

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


    glBegin(GL_TRIANGLES);

    for(int i = 0; i < slices;i++){
        glColor3f(0.0f,1.0f/slices*i,0.0f);

        glVertex3f(radius*sin (angle), 0.0f, radius*cos (angle));
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(radius*sin (angle+sizeSlice), 0.0f, radius*cos (angle+sizeSlice));
        glVertex3f(0.0f, height, 0.0f);
        glVertex3f(radius*sin (angle), height, radius*cos (angle));
        glVertex3f(radius*sin (angle+sizeSlice), height, radius*cos (angle+sizeSlice));


        glVertex3f(radius*sin (angle+sizeSlice), height, radius*cos (angle+sizeSlice));
        glVertex3f(radius*sin (angle), 0.0f, radius*cos (angle));
        glVertex3f(radius*sin (angle+sizeSlice), 0.0f, radius*cos (angle+sizeSlice));
        glVertex3f(radius*sin (angle), height, radius*cos (angle));
        glVertex3f(radius*sin (angle), 0.0f, radius*cos (angle));
        glVertex3f(radius*sin (angle+sizeSlice), height, radius*cos (angle+sizeSlice));

        angle+=sizeSlice;

    }

    glEnd();

}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(radius*cos(beta)*sin(alpha),radius*sin(beta),radius*cos(beta)*cos(alpha),
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

    glPolygonMode(GL_FRONT_AND_BACK,tipo);

	drawCylinder(1,1,50);

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {

    switch(c) {
          case ' ' :
            tipo++;
            if(tipo==6915)tipo=6912;// inteiros que correspodem ao GL_FILL, GL_LINE, GL_POINT
            glutPostRedisplay();
            break;

    }


}


void processSpecialKeys(int key, int xx, int yy) {

    switch(key) {

        case GLUT_KEY_LEFT :
            alpha-=0.1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT :
            alpha+=0.1;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP :
            beta-=0.1;
            if(beta<-1.5)beta=-1.5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN :
            beta+=0.1;
            if(beta>1.5)beta=1.5;
            glutPostRedisplay();
            break;

    }

}

void mouse (int button, int state, int x, int y){
    if(button==GLUT_LEFT_BUTTON){
        radius+=0.1f;
        glutPostRedisplay();
    }
    if(button==GLUT_RIGHT_BUTTON){
        radius-=0.1f;
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
	
// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(mouse);

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
// enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
