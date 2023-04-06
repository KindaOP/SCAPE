#include <Windows.h>
#include <GL/glut.h>
#include <time.h>
#include "geometry.h"
#include "camera.h"
#include "drawing.h"


static Vector BG_COLOR(0, 0, 0);
static Vector GND_COLOR(1, 1, 1);
static Camera* const CAMERA = &Camera::Get();


void transformToCenterViewport(int& x, int& y) {
	x = x - Camera::W / 2;
	y = Camera::H / 2 - y;
}


void displayFunc() {
	// Time display loop
	static const int FPS = 30;
	static const double SPF = 1. / FPS;
	double startTime = clock();

	// Refresh buffer and screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BG_COLOR.z, BG_COLOR.y, BG_COLOR.z, 0);

	// Draw elements
	glColor4f(GND_COLOR.x, GND_COLOR.y, GND_COLOR.z, 0);
	drawGround(100, 100);

	// Update camera
	CAMERA->drawAxes();
	CAMERA->step();
	CAMERA->look();

	glutSwapBuffers();

	// Delay roughly according to FPS
	while (clock() - startTime < SPF) {}
}


void keyboardToggleFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		CAMERA->wasdStates ^= 0b1000;
		break;
	case 'a':
		CAMERA->wasdStates ^= 0b0100;
		break;
	case 's':
		CAMERA->wasdStates ^= 0b0010;
		break;
	case 'd':
		CAMERA->wasdStates ^= 0b0001;
		break;
	default:
		return;
	}
}


int main(int argc, char** argv) {
	// Do initial GLUT setup
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(Camera::W, Camera::H);
	const int SW = glutGet(GLUT_SCREEN_WIDTH);
	const int SH = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition(
		(SW - Camera::W) / 2, 
		(SH - Camera::H) / 2
	);

	// Create window and register functions
	glutCreateWindow("SCAPE");
	glutIdleFunc(displayFunc);
	glutDisplayFunc(displayFunc);
	glutKeyboardFunc(keyboardToggleFunc);
	glutKeyboardUpFunc(keyboardToggleFunc);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	// Intial OpenGL setup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(
		-Camera::W / 2, -Camera::H / 2,
		 Camera::W / 2,  Camera::H / 2
	);
	const double ratio = static_cast<double>(Camera::W) / Camera::H;
	gluPerspective(45, ratio, Camera::R_NEAR, Camera::R_FAR);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// Run main loop
	glutMainLoop();
	return 0;
}


