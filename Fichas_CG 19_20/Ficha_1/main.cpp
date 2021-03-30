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

void renderScene(void) {

    int oldTimeSinceStart=0;
    int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
    int delta = timeSinceStart - oldTimeSinceStart;
    oldTimeSinceStart = timeSinceStart;

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(	0.0f, 0.0f, 10.0f,
                  0.0f, 0.0f,  0.0f,
                  0.0f, 1.0f,  0.0f);

    // PI rad por segundo (o delta é em milisegundos) e o +1 para os senos não serem negativos
    glScalef(sin(delta*0.00314)+1,sin(delta*0.00314)+1,sin(delta*0.00314)+1);
    glutWireTeapot(1.0);

    glutSwapBuffers();


}

int main(int argc, char **argv) {

// put GLUT init here
glutInit(&argc,argv);

glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(640,640);
glutCreateWindow("CG@DI");

// put callback registration here

glutIdleFunc(renderScene);
glutReshapeFunc(changeSize);


// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f,0.0f,0.0f,0.0f);

// enter GLUT's main loop
	glutMainLoop();
	
	return 1;
}

